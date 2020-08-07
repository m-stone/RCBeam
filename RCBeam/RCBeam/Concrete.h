#pragma once
#include "Material.h"
class Concrete :
    public Material
{
protected:
    // protected elements here
    double m_CompressiveStrength;

    // Strain Properties
    std::vector<double> m_epsilon;

public:
    // public elements here
	// Any virtual functions should go here.
    Concrete();
    Concrete(double strength);

	// Sets
    void UpdateProperties();

	// Gets
};

