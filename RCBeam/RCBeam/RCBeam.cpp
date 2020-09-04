#include "RCBeam.h"

RCBeam::RCBeam(RectangularBeam* pBeam, Rebar* pRebar, int n_bars, double d_bar)
{
	m_pBeam = pBeam;
	m_pRebar = pRebar;

	SetNumBars(n_bars);
	SetBarDepth(d_bar);
}

void RCBeam::SetASteel()
{
	// Calculate total A_s
	A_steel = m_n_bars * m_pRebar->GetArea();
}
