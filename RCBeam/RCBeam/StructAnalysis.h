#pragma once

// Structural Analysis Functions

// Function to calculate the moment at a given location on the beam due to point load at given point on beam
double Moment_PointLoad(std::shared_ptr<RCBeam>& RCBeam, double P_0, double x_p, double x);

// Function to calculate the deflection at a given location on the beam due a point load at a given point on the beam
double Deflection_PointLoad(std::shared_ptr<RCBeam>& RCBeam, double P_0, std::vector<double>& Moment, std::vector<double>& Phi, double x_p, double x);

// Function to Calculate Theta_a
double Theta_PointLoad(std::shared_ptr<RCBeam>& RCBeam, double P_0, std::vector<double>& Moment, std::vector<double>& Phi, double x_p, double x);

double Resistance(std::shared_ptr<RCBeam>& RCBeam, std::vector<double>&Moment,std::vector<double>&Phi,double x_l);