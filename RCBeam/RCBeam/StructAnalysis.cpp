#include "pch.h"
#include "geometry.h"
#include "RCBeam.h"
#include "MomentAnalysis.h"
#include "StructAnalysis.h"

/// <summary>
/// Calculate the moment at a given point on the beam given a load P_0.
/// </summary>
/// <param name="RCBeam"></param>
/// <param name="P_0"></param>
/// <param name="x_p"></param>
/// <param name="x"></param>
/// <returns></returns>
double Moment_PointLoad(std::shared_ptr<RCBeam>& RCBeam, double P_0, double x_p, double x)
{
	// Assume x_p = L/2.
	double length = RCBeam->getBeamLength();
	double x_load = x_p;
	double x_b = length - x_p;
	double Moment = 0.0;

	// error checking
	if ((x < 0) || (x > RCBeam->getBeamLength()))
	{
		return 0.0;
	}

	// Triangular Moment distribution
	if (x <= x_p)
	{
		Moment = P_0 * (x_b/length) * x;
	}
	else
	{
		Moment = P_0 * x_p + P_0 * x * (x_b / length - 1);
		//Moment = (P_0 * 0.5) * (length - x);
	}
	return Moment;
}

/// <summary>
/// Calculates the Deflection at a point given the load using a moment-curvature relationship.
/// </summary>
/// <param name="RCBeam"></param>
/// <param name="Moment"></param>
/// <param name="Phi"></param>
/// <param name="x_p"></param>
/// <param name="x"></param>
/// <returns></returns>
double Deflection_PointLoad(std::shared_ptr<RCBeam>& RCBeam, double P_0, std::vector<double>& Moment, std::vector<double>& Phi, double x_p, double x)
{
	// Assume x_p = L/2, x = L/2
	double beam_length = RCBeam->getBeamLength();
	double x_load = x_p;	// also called x_a
	double x_b = beam_length - x_p;
	double x_disp = x;
	double delta = 0.0;
	double delta_b_a = 0.0;
	double delta_c_a = 0.0;

	// divide the beam up into sections. For each section, calculate the moment and resultant curvature. Then, moment-area curvature to calculate deflection.
	// number of divisions
	int num_beam_divs = 1000;
	// length of each sub-section
	double delta_L = beam_length / num_beam_divs;

	// Create a vector to store location
	std::vector<double>location;
	// Create a vector to store curvature as a function of X:
	std::vector<double>curvature;

	double moment = 0.0;

	// loop through beam divisions and store the location and local curvature.
	for (int i = 0; i < num_beam_divs; i++)
	{
		location.push_back(i * delta_L);
		// Calculate the moment at the current location
		moment = Moment_PointLoad(RCBeam, P_0, x_load, i*delta_L);
		// calculate the curvature given this moment
		curvature.push_back(linterp_double(Moment, Phi, moment));		
	}

	// now use moment-area of curvature vs location to calculate displacement
	delta_b_a = moment_area(location, curvature, beam_length);
	delta_c_a = moment_area(location, curvature, x_disp);
	delta = 0.5 * delta_b_a - delta_c_a;

	return delta; // return the displacement
}

/// <summary>
/// </summary>
/// <param name="RCBeam"></param>
/// <param name="Moment"></param>
/// <param name="Phi"></param>
/// <param name="x_l"></param>
/// <returns></returns>
double Resistance(std::shared_ptr<RCBeam>& RCBeam, std::vector<double>& Moment, std::vector<double>& Phi, double x_l)
{
	return 0.0;
}
