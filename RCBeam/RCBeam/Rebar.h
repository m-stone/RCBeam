#pragma once
#include "pch.h"
#include "Steel.h"

class Rebar
{
protected:
	double m_Diameter, m_Area;
	int m_BarSize;

	// Steel type
	Steel* m_pSteel;

public:
	// Constructors
	Rebar(Steel* pSteeltype, int barsize);

	// sets
	void SetDiameter(double diameter) { m_Diameter = diameter; }
	void SetArea(double diameter) { m_Area = 3.14159 * pow(diameter, 2) / 4; }
	void SetBarSize(int barsize);
	void SetGeometry();
	void SetMaterial(Steel* pSteelType) { m_pSteel = pSteelType; }

	// gets
	double GetDiameter() { return m_Diameter; }
	double GetArea() { return m_Area; }
	
	// Steel Getters 
	double getStress(double strain) { return m_pSteel->GetStress(strain); }
	double getYieldStress() { return m_pSteel->GetYieldStress(); }
};

