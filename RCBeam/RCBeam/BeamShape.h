#pragma once
#include "pch.h"

class BeamShape
{
protected:
	double m_Area_gross, m_Ixx, m_Iyy;

public:

	// Sets
	virtual void SetArea() = 0;
	virtual void SetInertia() = 0;

	// Gets
	double GetArea() { return m_Area_gross; }
	double GetIxx() { return m_Ixx; }
	double GetIyy() { return m_Iyy; }

};

