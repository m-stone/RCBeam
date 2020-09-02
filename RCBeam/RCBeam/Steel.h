#pragma once
#include "Material.h"
class Steel :
    public Material
{
protected:
    // typical given properties are yield strength, elasticity
    // derived properties are strain
    // but strain can be a given depending on material model type
    // protected elements
    double m_YieldStrength;
    double m_YieldStrain;

    enum class SteelModelType {
        Elastic = 1,
        EPP = 2
    } m_SteelModel;

    //SteelModelType m_SteelModel;

public:
    // public elements
    Steel();
    Steel(double yield_strength, double modulus);

    // sets
    void SetYieldStrength(double yield_strength) { m_YieldStrength = yield_strength; }
    void SetYieldStrain() { m_YieldStrain = m_YieldStrength / m_Modulus; }
    void SetYieldStrain(double yield_strain) { m_YieldStrain = yield_strain; }
    void UpdateProperties();
    void SetMaterialModel(SteelModelType steelmodel);

    // gets
    double GetYieldStrength() { return m_YieldStrength; }
    double GetYieldStrain() { return m_YieldStrain; }
};

