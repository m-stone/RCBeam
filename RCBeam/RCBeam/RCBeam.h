#pragma once
#include "geometry.h"

class RCBeam
{
protected:
	// Gross beam section
	//RectangularBeam * m_pBeam;
	std::shared_ptr<RectangularBeam> m_pBeam;
	// Rebar (size)
	//Rebar * m_pRebar;
	// Vector of Rebar Layers
	//std::vector<RebarLayer *> m_pRebarLayers;
	std::vector<std::shared_ptr<RebarLayer>> m_pRebarLayers;
	// Vector of Rebar 
	//std::vector<Rebar*> m_pRebar;
	std::vector<std::shared_ptr<Rebar>> m_pRebar;
	
	// Length is a BEAM property, not a cross sectional property
	double m_length = 0.0;
	
	// Rebar number and depth
	int m_num_rebarlayers = 0;

	// Derived Properties
	double A_steel = 0.0;

public:
	RCBeam(std::shared_ptr<RectangularBeam>& pBeam);
	RCBeam(std::shared_ptr<RectangularBeam>& pBeam, double length);
	~RCBeam();

	// Sets
	void AddRebarLayer(int num_bars, std::shared_ptr<Rebar>& pRebar, double depth);
	void setA_steel();
	void Refresh();
	void setLength(double length) { this->m_length = length; }

	// Steel Gets
	int getNumRebarLayers() { return m_num_rebarlayers; }
	double getAsteel_gross() { return A_steel; }
	double getAsteel(int steel_layer) { return m_pRebarLayers[steel_layer]->getAreaSteel(); }
	double getYieldStress(int steel_layer) { return m_pRebarLayers[steel_layer]->getYieldStress(); }
	double getSteelStress(int steel_layer, double strain) { return m_pRebarLayers[steel_layer]->getStress(strain); }
	double getSteelLayerDepth(int steel_layer) { return m_pRebarLayers[steel_layer]->getDepth(); }

	// Concrete Gets
	double getBeamWidth() { return m_pBeam->getWidth(); }
	double getBeamHeight() { return m_pBeam->getHeight(); }

	// Geometry gets?
	double getBeamLength() { return this->m_length; }

};

