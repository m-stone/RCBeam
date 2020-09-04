#pragma once
#include "materials.h"
#include "geometry.h"

class RCBeam
{
protected:
	// Gross beam section
	RectangularBeam* m_pBeam;
	// Rebar (size)
	Rebar* m_pRebar;
	// Rebar number and depth
	int m_n_bars;
	double m_d_bar;

	// Derived Properties
	double A_steel;

public:
	RCBeam(RectangularBeam* pBeam, Rebar* pRebar, int n_bars, double d_bar);

	// Sets
	void SetNumBars(int n_bars) { m_n_bars = n_bars; }
	double SetBarDepth(double d_bar) { m_d_bar = d_bar; }
	void SetASteel();

	// Gets
	double GetASteel() { return A_steel; }
};

