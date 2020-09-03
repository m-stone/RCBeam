#pragma once
#include "pch.h"
#include "Concrete.h"

class BeamShape
{
protected:
	double m_Area_gross, m_Ixx, m_Iyy;
	double m_Length;
	Concrete* m_pConcrete;

public:

	// Sets
	virtual void SetAreaGross() = 0;
	virtual void SetInertia() = 0;
	virtual void SetLength(double length) { m_Length = length; }
	virtual void SetMaterial(Concrete* pConcrete) { m_pConcrete = pConcrete; }

	// Gets
	double GetAreaGross() { return m_Area_gross; }
	double GetIxx() { return m_Ixx; }
	double GetIyy() { return m_Iyy; }
	double GetLength() { return m_Length; }

};

