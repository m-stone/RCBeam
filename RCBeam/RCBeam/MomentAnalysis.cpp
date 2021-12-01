#include "pch.h"
#include "geometry.h"
#include "RCBeam.h"
#include "MomentAnalysis.h"

double NominalMoment(std::shared_ptr<RCBeam>& pRCBeam, std::shared_ptr<Concrete>& pConcrete, std::shared_ptr<Steel>& pSteel)
{
	/*
	Start with basic ACI single layer moment analysis.
	*/
	// Calculate beta1
	double beta_1 = Beta1(pConcrete);

	double epsilon_cu = pConcrete->getEpsCu();

	// Assume steel yields.
	// Calculate effective stress block depth.
	double a = (pRCBeam->getAsteel_gross() * pSteel->getYieldStress()) / (0.85 * pConcrete->getStrength() * pRCBeam->getBeamWidth());
	std::cout << "calculating a\n";
	std::cout << (pRCBeam->getAsteel_gross() * pSteel->getYieldStress()) << "\n" << (0.85 * pConcrete->getStrength() * pRCBeam->getBeamWidth()) << "\n";
	// Calculate neutral axis depth
	double c = a / beta_1;

	//Calculate compressive forces
	double F_c = 0.85 * beta_1 * pConcrete->getStrength() * pRCBeam->getBeamWidth() * a;

	std::cout << "compression block output" << std::endl;
	std::cout << "a: " << a << "\tc: " << c << "\tF_c: " << F_c << std::endl;

	// Calculate steel forces
	double F_t = pRCBeam->getAsteel_gross() * pSteel->getYieldStress();

	std::cout << "tension output\n";
	std::cout << "F_t: " << F_t << std::endl;

	// Check that steel yields
	double epsilon_s = (pRCBeam->getSteelLayerDepth(0) - c) * epsilon_cu / c;
	std::cout << "Steel epsilon is " << epsilon_s << std::endl;

	// Calculate Mn
	double M_n = F_t * (pRCBeam->getSteelLayerDepth(0) - a / 2);

	return M_n;
}

/// <summary>
/// Calculates the sectional moment capacity for a given maximum compressive strain. 
/// </summary>
/// <param name="eps_cm">maximum compressive strain</param>
/// <param name="pRCBeam">RC beam reference</param>
/// <param name="pConcrete">Concrete Material</param>
/// <param name="pSteel">Steel Material</param>
/// <param name="pc_na">reference Vector of neutral axis values</param>
/// <returns></returns>
double MomentEpscm(double eps_cm,
	std::shared_ptr<RCBeam>& pRCBeam,
	std::shared_ptr<Concrete>& pConcrete,
	std::shared_ptr<Steel>& pSteel,
	std::vector<double>& pc_na)
{
	// Note that Compression is positive, tension negative. 

	// First Calculate the location of the neutral axis using bisection method.
	// Solver Parameters
	double c_min, c_max, c_guess;	// a,b,p
	double TOL = 0.1;	// tolerance in inches
	int max_iteration = 1000;	// max iterations
	c_min = pRCBeam->getBeamHeight() * 1e-6;	// starting interval a
	c_max = pRCBeam->getBeamHeight();	// ending interval b
	double delta_c = (c_max - c_min) * 0.5;	// starting guess

	int num_xsxn_layers = 100;	// number of layers to divide the section into
	double FA = 0.0, FB = 0.0, FP = 0.0;
	
	// Stress values
	std::vector<double> f_cc;
	std::vector<double> f_ct;

	// special case for 1st iteration
	int iteration = 1;

	// Calculate the sum of all forces using the range values a, b
	FA = EquilibriumForces(c_min, eps_cm, pRCBeam, pConcrete, pSteel, f_cc, f_ct, num_xsxn_layers);
	FB = EquilibriumForces(c_max, eps_cm, pRCBeam, pConcrete, pSteel, f_cc, f_ct, num_xsxn_layers);

	// FA and FB are same sign -- can't use bisection method
	if (FA * FB > 0)
	{
		std::cout << "Equilibrium forces cannot be solved using bisection method\n";
		std::cout << "FA and FB are the same sign\n";
		return 1.0;
	}

	// iterate and calculate FP. 
	while (iteration <= max_iteration)
	{
		// update delta_c
		delta_c = (c_max - c_min) * 0.5;
		// update midpoint guess value
		c_guess = c_min + delta_c;
		// calculate sum of all forces at midpoint
		FP = EquilibriumForces(c_guess, eps_cm, pRCBeam, pConcrete, pSteel, f_cc, f_ct, num_xsxn_layers);
		// if found equilibrium or inside of tolerance then done
		if ((FP == 0.0) || (delta_c < TOL))
		{
			// Add c_na to the vector of neutral axis
			pc_na.push_back(c_guess);
			// break out of while loop
			break;
		}
		iteration++;
		// if FA and FP are same sign, then make a = p, FA = FP
		if (FA*FP > 0)
		{
			c_min = c_guess;
			FA = FP;
		}
		// FA and FP are opposite, set b = p
		else
		{
			c_max = c_guess;
		}
		// hit maximum number of iterations
		if (iteration > max_iteration)
		{
			std::cout << "Equilibrium was not found after " << iteration << " iterations." << std::endl;
			return -1.0;
		}
	}

	// Now need to calculate the moment. initialize vars = 0
	double Mcc = 0.0, Ms = 0.0, Mct = 0.0;
	
	// Calculate the steel moment
	double eps_si = 0.0;
	// for each rebar layer, calculate the strain at that layer and the corresponding stress and moment
	for (int i = 0; i < pRCBeam->getNumRebarLayers(); i++)
	{
		// calculate the strain 
		eps_si = epsilon_steel(c_guess, pRCBeam->getSteelLayerDepth(i), eps_cm);
		// calculate the moment due to steel forces about neutral axis
		Ms += (pSteel->getStress(eps_si) - pConcrete->getStress(eps_si)) * pRCBeam->getAsteel(i) * (c_guess - pRCBeam->getSteelLayerDepth(i));
	}

	// Calculate the concrete moment
	double delta_h = c_guess / num_xsxn_layers;
	double delta_h_t = (c_guess - pRCBeam->getBeamHeight()) / num_xsxn_layers;
	for (int i = 1; i <= num_xsxn_layers; i++)
	{
		// Compressive moment
		Mcc += (delta_h * pRCBeam->getBeamWidth() * 0.5 * (f_cc.at(i) + f_cc.at(i - 1))) * delta_h * 0.5 * (2 * i - 1);
		// Tensile moment
		Mct += (-1*delta_h_t * pRCBeam->getBeamWidth() * 0.5 * (f_ct.at(i) + f_ct.at(i - 1))) * delta_h_t * 0.5 * (2 * i - 1);
	}
	// Return the total moment
	return (Mcc + Ms + Mct);
}

/// <summary>
/// Calculates sum of equilibrium forces based on given input parameters.
/// </summary>
/// <param name="c_na"></param>
/// <param name="eps_cm"></param>
/// <param name="pRCBeam"></param>
/// <param name="pConcrete"></param>
/// <param name="pSteel"></param>
/// <param name="pfcc"></param>
/// <param name="pfct"></param>
/// <param name="num_sxn_layers"></param>
/// <returns></returns>
double EquilibriumForces(double c_na,
	double eps_cm,
	std::shared_ptr<RCBeam>& pRCBeam,
	std::shared_ptr<Concrete>& pConcrete,
	std::shared_ptr<Steel>& pSteel,
	std::vector<double>& pfcc,	//vector of concrete stress values
	std::vector<double>& pfct,	//vector of concrete tensile stress values
	int num_sxn_layers)
{
	// pfcc & pfct are declared outside of scope, but this function is where values are created. so clear them here:
	pfcc.clear();
	pfct.clear();

	// calculate the height of each layer in the section:
	double delta_h = c_na / num_sxn_layers;
	double eps_ci = 0.0;
	double Fcc = 0.0, Fct = 0.0;
	double Fts = 0.0;
#pragma region ConcreteCompressiveForces
	// Concrete Compressive Forces
	// Develop the vector of concrete stress at the midpoints of the layers.
	pfcc.push_back(0.0);
	for (int i = 1; i <= num_sxn_layers; i++)
	{
		// loop through layers and calculate the strain and resultant stress
		eps_ci = ((double)i / (double)num_sxn_layers) * eps_cm;
		// calculate stress at each layer
		pfcc.push_back(pConcrete->getStress(eps_ci));
	}
	// Calculate total Fcc using trapezoidal integration and spacing delta_h
	Fcc = pRCBeam->getBeamWidth() * trapz(pfcc, delta_h);
#pragma endregion

#pragma region Concrete Tensile Forces
	// Concrete Tensile Forces
	// calculate the tensile stress vector
	pfct.push_back(0.0);
	// re-evaluate delta_h for tensile side
	delta_h = (pRCBeam->getBeamHeight() - c_na) / num_sxn_layers;
	for (int i = 1; i <= num_sxn_layers; i++) 
	{
		// loop through sections and calculate strain, then stress
		// calculate the strain at the endpoints
		eps_ci = (eps_cm * i * (c_na - pRCBeam->getBeamHeight())) / (c_na * num_sxn_layers);
		// calculate the stress and add to the stack
		pfct.push_back(pConcrete->getStress(eps_ci));
	}
	// Calculate tensile force using trapz
	Fct = pRCBeam->getBeamWidth() * trapz(pfct, delta_h);
#pragma endregion

#pragma region Steel Forces
	// Steel Forces
	double eps_si = 0.0, Fs = 0.0;
	// Loop through rebar layers and calculate strain and stress
	for (int i = 0; i < pRCBeam->getNumRebarLayers(); i++)
	{
		eps_si = epsilon_steel(c_na, pRCBeam->getSteelLayerDepth(i), eps_cm);
		Fs += (pSteel->getStress(eps_si) - pConcrete->getStress(eps_si)) * pRCBeam->getAsteel(i);
	}
#pragma endregion

	// Calculate total forces and return
	double Fc = Fcc + Fs + Fct;
	return Fc;
}

/// <summary>
/// Calculates concrete Beta 1 factor from ACI
/// </summary>
/// <param name="pConcrete"></param>
/// <returns></returns>
double Beta1(std::shared_ptr<Concrete>& pConcrete)
{
	double beta_1;
	if (pConcrete->getStrength() <= 4000.0)
		beta_1 = 0.85;
	else if (pConcrete->getStrength() >= 8000.0)
		beta_1 = 0.65;
	else
		beta_1 = 0.85 - 0.05 * (pConcrete->getStrength() / 1000 - 4);
	return beta_1;
}

double epsilon_steel(double c_na, double depth, double eps_cm)
{
	return (eps_cm * (c_na - depth) / c_na);
}

