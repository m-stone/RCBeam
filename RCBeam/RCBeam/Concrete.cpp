#include "Concrete.h"

Concrete::Concrete()
{
	// Default constructor
	// 5000 psi
	m_CompressiveStrength = 5000.0;
	// 150 pcf
	m_Density = 150.0;
	// Update modulus
	UpdateProperties();
	// ACI Model 
	SetMaterialModel(ConcreteModelType::ACI);
	// eps_cm 0.002
	AddStrainValue(0.0);
	AddStrainValue(2000.0e-6);
	// eps_cu 0.0038
	AddStrainValue(3800.0e-6);
}

Concrete::Concrete(double strength)
{
	// Set Strength in psi
	m_CompressiveStrength = strength;
	// assume 150 pcf
	m_Density = 150.0;
	// Update modulus
	UpdateProperties();
	SetMaterialModel(ConcreteModelType::ACI);
}

void Concrete::UpdateProperties()
{
	// Calculate E_c
	m_Modulus = 57000 * sqrt(m_CompressiveStrength);
}

void Concrete::SetMaterialModel(ConcreteModelType materialmodel)
{
	m_ConcreteModel = materialmodel;
}

