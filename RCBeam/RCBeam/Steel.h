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
    double m_YieldStress;
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
    void SetYieldStress(double yield_stress) { m_YieldStress = yield_stress; }
    void SetYieldStrain() { m_YieldStrain = m_YieldStress / m_Modulus; }
    void SetYieldStrain(double yield_strain) { m_YieldStrain = yield_strain; }
    void UpdateProperties();
    void SetMaterialModel(SteelModelType steelmodel);

    // gets
    double GetYieldStress() { return m_YieldStress; }
    double GetYieldStrain() { return m_YieldStrain; }
};

