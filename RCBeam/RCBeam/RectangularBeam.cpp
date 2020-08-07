#include "RectangularBeam.h"

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
