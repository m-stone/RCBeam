#pragma once
#include "Material.h"
class Steel :
    public Material
{
protected:
    // protected elements
    double m_YieldStrength;
    double m_YieldStrain;

    enum class SteelModelType {
        Elastic = 1,
        EPP = 2
    };

    SteelModelType SteelModel;

public:
    // public elements
    Steel();
    Steel(double yield_strength, double modulus);

    // sets
    void UpdateStrain();

    // gets
};

