#pragma once
#include "Rebar.h"

class RebarLayer
{
protected:
	double m_depth, m_AreaSteel;
	Rebar* m_pRebar;
	int m_n_bars;
public:
	RebarLayer(int n_bars, Rebar* pRebar, double depth);

	void SetRebar(Rebar* pRebar) { m_pRebar = pRebar; }
	void SetNumBars(int n_bars) { m_n_bars = n_bars; }
	void SetDepth(double depth) { m_depth = depth; }
	void SetAreaSteel();

	double GetAreaSteel() { return m_AreaSteel; }
	double GetDepth() { return m_depth; }

	//rebar getters
	double getStress(double strain) { return m_pRebar->getStress(strain); }
	double getYieldStress() { return m_pRebar->getYieldStress(); }
};

