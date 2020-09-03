#include "Steel.h"

Steel::Steel()
{
	// default constructor - Gr60 steel
	SetYieldStress(60.0e3);
	SetModulus(30.0e6);
	SetMaterialModel(SteelModelType::Elastic);
	UpdateProperties();
	// Add Strain values
	AddStrainValue(0.0);
	AddStrainValue(m_YieldStrain);
	// Add Stress Values
	AddStressValue(0.0);
	AddStressValue(m_YieldStress);
}

Steel::Steel(double yield_strength, double modulus)
{
	// typical constructor given strength and modulus
	SetYieldStress(yield_strength);
	SetModulus(modulus);
	m_YieldStress = yield_strength;
	m_Modulus = modulus;
	SetMaterialModel(SteelModelType::Elastic);
	UpdateProperties();
	// Add Strain values
	AddStrainValue(0.0);
	AddStrainValue(m_YieldStrain);
	// Add Stress Values
	AddStressValue(0.0);
	AddStressValue(m_YieldStress);
}

void Steel::UpdateProperties()
{
	// update the yield strain
	m_YieldStrain = m_YieldStress / m_Modulus;
}

void Steel::SetMaterialModel(SteelModelType steelmodel)
{
	m_SteelModel = steelmodel;
}
