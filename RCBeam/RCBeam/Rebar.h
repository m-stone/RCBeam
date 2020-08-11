#pragma once
#include "pch.h"
#include "Steel.h"

class Rebar
{
protected:
	double m_Diameter, m_Area;

	enum class USRebarSize {
		No3 = 3,
		No4,
		No5,
		No6,
		No7,
		No8,
		No9
	};

	USRebarSize m_BarSize;

	// Steel type
	Steel* m_pSteel;

public:
	// Constructors
	Rebar(Steel& steeltype, USRebarSize barsize);

	// sets
	void SetDiameter(double diameter) { m_Diameter = diameter; }
	void SetArea(double diameter) { m_Area = 3.14159 * pow(diameter, 2) / 4; }
	void SetGeometry(USRebarSize barsize);

	// gets
	double GetDiameter() { return m_Diameter; }
	double GetArea() { return m_Area; }
};

