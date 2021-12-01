#pragma once
#include "pch.h"

class BeamShape
{
protected:
	double m_Area_gross, m_Ixx, m_Iyy;
	double m_Length;
	//Concrete* m_pConcrete;
	std::shared_ptr<Concrete> m_pConcrete;

public:

	// Sets
	virtual void setAreaGross() = 0;
	virtual void setInertia() = 0;
	virtual void setLength(double length) { this->m_Length = length; }
	//virtual void setMaterial(Concrete* pConcrete) { this->m_pConcrete = pConcrete; }
	virtual void setMaterial(std::shared_ptr<Concrete>& pConcrete) { this->m_pConcrete = pConcrete; }

	// Gets
	double getAreaGross() { return m_Area_gross; }
	double getIxx() { return m_Ixx; }
	double getIyy() { return m_Iyy; }
	double getLength() { return m_Length; }

};

