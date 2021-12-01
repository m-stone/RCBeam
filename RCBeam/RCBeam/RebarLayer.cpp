#include "RebarLayer.h"

/*
RebarLayer::RebarLayer(int n_bars, Rebar* pRebar, double depth)
{
	setNumBars(n_bars);
	setRebar(pRebar);
	setDepth(depth);
	setAreaSteel();
}
*/

RebarLayer::RebarLayer(int n_bars, std::shared_ptr<Rebar>& pRebar, double depth)
{
	setNumBars(n_bars);
	setRebar(pRebar);
	setDepth(depth);
	setAreaSteel();
}

void RebarLayer::setAreaSteel()
{
	m_AreaSteel = m_n_bars * m_pRebar->getArea();
}
