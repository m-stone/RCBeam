#pragma once
#include "BeamShape.h"
class RectangularBeam :
    public BeamShape
{
protected:
    float m_Width, m_Height;

public:
    
    // Sets
    void SetWidth(double width);
    void SetHeight(double height);
    void SetArea();

    // Gets
    double GetWidth() { return m_Width; }
    double GetHeight() { return m_Height; }
    double GetAGross() { return m_Area_gross; }
};

