#include "RectangularBeam.h"

RectangularBeam::RectangularBeam(double width, double height)
{
	SetWidth(width);
	SetHeight(height);
	SetArea();
	SetInertia();
}

void RectangularBeam::SetWidth(double width)
{
	m_Width = width;
}

void RectangularBeam::SetHeight(double height)
{
	m_Height = height;
}

void RectangularBeam::SetArea()
{
	m_Area_gross = m_Width * m_Height;
}

void RectangularBeam::SetInertia()
{
	m_Ixx = m_Width * pow(m_Height, 3) / 12.0;
	m_Iyy = pow(m_Width, 3) * m_Height / 12; 
}
