#include "RebarLayer.h"

RebarLayer::RebarLayer(int n_bars, Rebar* pRebar, double depth)
{
	SetNumBars(n_bars);
	SetRebar(pRebar);
	SetDepth(depth);
	SetAreaSteel();
}

void RebarLayer::SetAreaSteel()
{
	m_AreaSteel = m_n_bars * m_pRebar->GetArea();
}
