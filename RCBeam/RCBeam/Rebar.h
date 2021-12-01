#pragma once
#include "pch.h"

class Rebar
{
protected:
	double m_Diameter, m_Area;
	int m_BarSize;

	// Steel type
	Steel* m_pSteel1;
	std::shared_ptr<Steel> m_pSteel;

public:
	// Constructors
	Rebar(Steel* pSteeltype, int barsize);
	Rebar(std::shared_ptr<Steel> & pSteeltype, int barsize);

	// sets
	void setDiameter(double diameter) { this->m_Diameter = diameter; }
	void setArea(double area) { this->m_Area = area; }
	void setBarSize(int barsize);
	void setGeometry();
	void setMaterial(Steel* pSteelType) { this->m_pSteel1 = pSteelType; }

	// gets
	double getDiameter() { return this->m_Diameter; }
	double getArea() { return this->m_Area; }
	double getBarSize() { return this->m_BarSize; }
	
	// Steel Getters 
	double getStress(double strain) { return m_pSteel->getStress(strain); }
	double getYieldStress() { return m_pSteel->getYieldStress(); }
};

