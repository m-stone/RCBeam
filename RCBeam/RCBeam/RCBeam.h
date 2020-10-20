#pragma once
#include "materials.h"
#include "geometry.h"

class RCBeam
{
protected:
	// Gross beam section
	RectangularBeam * m_pBeam;
	// Rebar (size)
	//Rebar * m_pRebar;
	// Vector of Rebar Layers
	std::vector<RebarLayer *> m_pRebarLayers;
	// Vector of Rebar 
	std::vector<Rebar*> m_pRebar;
	
	// Rebar number and depth
	int m_num_rebarlayers = 0;

	// Derived Properties
	double A_steel = 0.0;

public:
	RCBeam(RectangularBeam* pBeam);
	~RCBeam();

	// Sets
	void AddRebarLayer(int num_bars, Rebar * pRebar, double depth);
	void SetA_steel();
	void Refresh();

	// Steel Gets
	int GetNumRebarLayers() { return m_num_rebarlayers; }
	double GetA_steel() { return A_steel; }
	double getYieldStress(int steel_layer) { return m_pRebarLayers[steel_layer]->getYieldStress(); }
	double getSteelStress(int steel_layer, double strain) { return m_pRebarLayers[steel_layer]->getStress(strain); }

	// Concrete Gets
	double getBeamWidth() { return m_pBeam->GetWidth(); }
	double getBeamHeight() { return m_pBeam->GetHeight(); }
};

