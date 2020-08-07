#include "Steel.h"

Steel::Steel()
{
	// default constructor - Gr60 steel
	m_Modulus = 30.0e6;
	m_YieldStrength = 60.0e3;
	m_YieldStrain = 0.002;
	SteelModel = SteelModelType::Elastic;
}

Steel::Steel(double yield_strength, double modulus)
{
	// typical constructor given strength and modulus
	m_YieldStrength = yield_strength;
	m_Modulus = modulus;
	SteelModel = SteelModelType::Elastic;
	UpdateStrain();
}

void Steel::UpdateStrain()
{
	m_YieldStrain = m_YieldStrength / m_Modulus;
}
