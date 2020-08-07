#include "Concrete.h"

Concrete::Concrete()
{
	// Default constructor
	// 5000 psi
	m_CompressiveStrength = 5000.0;
}

Concrete::Concrete(double strength)
{
	// Set Strength in psi
	m_CompressiveStrength = strength;
	// assume 150 pcf
	m_Density = 150.0;
	// Update modulus
	UpdateProperties();
}

void Concrete::UpdateProperties()
{
	// Calculate E_c
	m_Modulus = 57000 * sqrt(m_CompressiveStrength);
}
