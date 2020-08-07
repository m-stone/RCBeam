#include "Material.h"

void Material::AddStrainValue(double strain)
{
	m_Epsilon.push_back(strain);
}

void Material::AddStressValue(double stress)
{
	m_Sigma.push_back(stress);
}
