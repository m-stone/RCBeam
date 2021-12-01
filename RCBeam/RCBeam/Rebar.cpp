#include "Rebar.h"

Rebar::Rebar(std::shared_ptr<Steel>& pSteeltype, int barsize)
{
	m_pSteel = pSteeltype;
	setBarSize(barsize);
}

Rebar::Rebar(std::shared_ptr<Steel>& pSteeltype, double barsize)
{
	m_pSteel = pSteeltype;
	setBarSize(barsize);
}

void Rebar::setGeometry()
{
	double diameter = 0.375;
	double area = 0.11;
	switch (m_BarSize)
	{
	case 3:
		diameter = 0.375;
		area = 0.11;
		break;
	case 4:
		diameter = 0.500;
		area = 0.20;
		break;
	case 5:
		diameter = 0.625;
		area = 0.31;
		break;
	case 6:
		diameter = 0.750;
		area = 0.44;
		break;
	case 7:
		diameter = 0.875;
		area = 0.60;
		break;
	case 8:
		diameter = 1.000;
		area = 0.79;
		break;
	case 9:
		diameter = 1.128;
		area = 1.00;
		break;
	case 10:
		diameter = 1.270;
		area = 1.27;
		break;
	case 11:
		diameter = 1.410;
		area = 1.56;
		break;
	case 14:
		diameter = 1.693;
		area = 2.25;
		break;
	case 18:
		diameter = 2.257;
		area = 4.00;
		break;
	default:
		diameter = (double)m_BarSize / 8.0;
		area = 3.14159 * pow(diameter, 2) / 4;
		setDiameter(diameter);
		setArea(diameter);
	}
	setDiameter(diameter);
	setArea(area);
}

void Rebar::setBarSize(int barsize)
{
	this->m_BarSize = barsize;
	setGeometry();
}

void Rebar::setBarSize(double barsize)
{
	this->m_BarSize = (int)barsize;
	double diameter = m_BarSize / 8.0;
	double area = 3.14159 * pow(diameter, 2) / 4;
	setDiameter(diameter);
	setArea(diameter);	
}


