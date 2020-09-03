#include "Rebar.h"

Rebar::Rebar(Steel* pSteeltype, int barsize)
{
	// Set Steel Type
	m_pSteel = pSteeltype;
	// Set Barsize
	SetBarSize(barsize);
}

void Rebar::SetGeometry()
{
	double diameter = (double)m_BarSize / 8.0;
	SetDiameter(diameter);
	SetArea(diameter);
}

void Rebar::SetBarSize(int barsize)
{
	m_BarSize = barsize;
	SetGeometry();
}
