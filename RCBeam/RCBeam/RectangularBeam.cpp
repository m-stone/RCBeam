#include "RectangularBeam.h"

RectangularBeam::RectangularBeam(double width, double height, std::shared_ptr<Concrete>& pConcrete)
{
	//usual constructor
	// Setup geometry
	setWidth(width);
	setHeight(height);
	setAreaGross();
	setInertia();
	// set material
	setMaterial(pConcrete);
}

RectangularBeam::RectangularBeam(double width, double height, std::shared_ptr<Concrete>& pConcrete, double length)
{
	//usual constructor
	// Setup geometry
	setWidth(width);
	setHeight(height);
	// set length
	this->setLength(length);
	setAreaGross();
	setInertia();
	// set material
	setMaterial(pConcrete);
}

void RectangularBeam::setWidth(double width)
{
	this->m_Width = width;
}

void RectangularBeam::setHeight(double height)
{
	this->m_Height = height;
}

void RectangularBeam::setAreaGross()
{
	m_Area_gross = m_Width * m_Height;
}

void RectangularBeam::setInertia()
{
	m_Ixx = m_Width * pow(m_Height, 3) / 12.0;
	m_Iyy = pow(m_Width, 3) * m_Height / 12; 
}
