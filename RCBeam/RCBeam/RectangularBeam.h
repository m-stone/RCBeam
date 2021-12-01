#pragma once
#include "BeamShape.h"
class RectangularBeam :
    public BeamShape
{
protected:
    double m_Width, m_Height;

public:
    RectangularBeam(double width, double height, std::shared_ptr<Concrete>& pConcrete);
    RectangularBeam(double width, double height, std::shared_ptr<Concrete>& pConcrete, double length);
    
    // Sets
    void setWidth(double width);
    void setHeight(double height);
    void setAreaGross();
    void setInertia();

    // Gets
    double getWidth() { return m_Width; }
    double getHeight() { return m_Height; }
};

