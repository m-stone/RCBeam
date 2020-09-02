#pragma once
#include "Material.h"
class Concrete :
    public Material
{
protected:
    // typical given properties are strength, density
    // derived properties are modulus
    // strain is material model dependent -- can be given or derived
    // protected elements here
    double m_CompressiveStrength;

    // Model Type
    enum class ConcreteModelType {
        ACI = 1,
        Hognestad,
        Power
    } m_ConcreteModel;

    //ConcreteModelType m_ConcreteModel;

public:
    // public elements here
	// Any virtual functions should go here.
    Concrete();
    Concrete(double strength);

	// Sets
    void SetStrength(double strength) { m_CompressiveStrength = strength; }
    void UpdateProperties();
    void SetMaterialModel(ConcreteModelType materialmodel);

	// Gets
    double GetStrength() { return m_CompressiveStrength; }
};

