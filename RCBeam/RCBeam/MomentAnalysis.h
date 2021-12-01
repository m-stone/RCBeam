#pragma once

double NominalMoment(std::shared_ptr<RCBeam>& pRCBeam, 
	std::shared_ptr<Concrete>& pConcrete, 
	std::shared_ptr<Steel>& pSteel);

double MomentEpscm(double eps_cm, 
	std::shared_ptr<RCBeam>& pRCBeam, 
	std::shared_ptr<Concrete>& pConcrete, 
	std::shared_ptr<Steel>& pSteel,
	std::vector<double>& pc_na);

double EquilibriumForces(double c_na,
	double eps_cm,
	std::shared_ptr<RCBeam>& pRCBeam,
	std::shared_ptr<Concrete>& pConcrete,
	std::shared_ptr<Steel>& pSteel,
	std::vector<double>& pfcc,
	std::vector<double>& pfct,
	int num_sxn_layers);

double Beta1(std::shared_ptr<Concrete>& pConcrete);

double epsilon_steel(double c_na, double depth, double eps_cm);
