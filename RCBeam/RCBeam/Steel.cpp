#include "Steel.h"

Steel::Steel()
{
	// default constructor - Gr60 steel
	m_Modulus = 30.0e6;
	m_YieldStrength = 60.0e3;
	SetMaterialModel(SteelModelType::Elastic);
	UpdateProperties();
	AddStrainValue(0.0);
	AddStrainValue(m_YieldStrain);
	AddStressValue(0.0);
	AddStressValue(m_YieldStrength);
}

Steel::Steel(double yield_strength, double modulus)
{
	// typical constructor given strength and modulus
	m_YieldStrength = yield_strength;
	m_Modulus = modulus;
	SetMaterialModel(SteelModelType::Elastic);
	UpdateProperties();
}

void Steel::UpdateProperties()
{
	// update the yield strain
	m_YieldStrain = m_YieldStrength / m_Modulus;
}

void Steel::SetMaterialModel(SteelModelType steelmodel)
{
	m_SteelModel = steelmodel;
}
