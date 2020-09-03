#pragma once
#include "BeamShape.h"
class RectangularBeam :
    public BeamShape
{
protected:
    double m_Width, m_Height;

public:
    RectangularBeam(double width, double height, Concrete* pConcrete);
    
    // Sets
    void SetWidth(double width);
    void SetHeight(double height);
    void SetAreaGross();
    void SetInertia();

    // Gets
    double GetWidth() { return m_Width; }
    double GetHeight() { return m_Height; }
};

