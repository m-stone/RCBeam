#include "RCBeam.h"

RCBeam::RCBeam(RectangularBeam* pBeam)
{
	// Set up gross beam geometry
	m_pBeam = pBeam;
}

RCBeam::~RCBeam()
{
	// Have to remember to clean up our vector of pointers.
	for (RebarLayer* obj : m_pRebarLayers)
		delete obj;
	m_pRebarLayers.clear();
}

void RCBeam::AddRebarLayer(int num_bars, Rebar* pRebar, double depth)
{
	// Adds a new rebar layer to the beam class. 
	m_pRebarLayers.push_back(new RebarLayer(num_bars, pRebar, depth));
	//m_pRebar.push_back(pRebar);
	m_num_rebarlayers++;
	std::cout << "current rebar layers: " << m_num_rebarlayers << std::endl;
}

void RCBeam::SetA_steel()
{
	for (int i = 0; i < m_num_rebarlayers; i++)
	{
		A_steel += m_pRebarLayers[i]->GetAreaSteel();
	}
}

void RCBeam::Refresh()
{
	SetA_steel();
}
