#pragma once
#include "Rebar.h"

class RebarLayer
{
protected:
	double m_depth, m_AreaSteel;
	std::shared_ptr<Rebar> m_pRebar;
	//Rebar* m_pRebar;
	int m_n_bars;
public:
	//RebarLayer(int n_bars, Rebar* pRebar, double depth);
	RebarLayer(int n_bars, std::shared_ptr<Rebar>& pRebar, double depth);

	//void setRebar(Rebar* pRebar) { this->m_pRebar = pRebar; }
	void setRebar(std::shared_ptr<Rebar>& pRebar) { this->m_pRebar = pRebar; }
	void setNumBars(int n_bars) { this->m_n_bars = n_bars; }
	void setDepth(double depth) { this->m_depth = depth; }
	void setAreaSteel();

	double getAreaSteel() { return m_AreaSteel; }
	double getDepth() { return m_depth; }

	//rebar getters
	double getStress(double strain) { return m_pRebar->getStress(strain); }
	double getYieldStress() { return m_pRebar->getYieldStress(); }
};

