#pragma once
class Rebar
{
protected:
	double m_Diameter, m_Area;

	enum class USRebarSize {
		No3 = 3,
		No4,
		No5,
		No6,
		No7,
		No8,
		No9
	};

	USRebarSize m_BarSize;

public:

	// sets
	void SetArea();

	// gets
	double GetArea() { return m_Area; }
};

