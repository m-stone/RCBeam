#pragma once
#include "pch.h"

class Material
{
protected:
	// Basic Properties
	double m_Modulus, m_Density;

	std::vector<double> m_Epsilon, m_Sigma;

	// Derived Properties
	
public:
	// Any virtual functions should go here.

	// Sets
	virtual void AddStrainValue(double strain);
	virtual void AddStressValue(double stress);

	// Gets
	double GetModulus() { return m_Modulus; }
	double GetDensity() { return m_Density; }
};

