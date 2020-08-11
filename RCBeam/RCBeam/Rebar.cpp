#include "Rebar.h"

Rebar::Rebar()
{

}

void Rebar::SetGeometry(USRebarSize barsize)
{
	double diameter = 0.375;
	switch (barsize)
	{
		case (USRebarSize::No3):
			double diameter = 0.375;
			break;
		case USRebarSize::No4:
			diameter = 0.500;
			break;
		case USRebarSize::No5:
			diameter = 0.625;
			break;
		case USRebarSize::No6:
			diameter = 0.750;
			break;
		case USRebarSize::No7:
			diameter = 0.875;
			break;
		case USRebarSize::No8:
			diameter = 1.00;
			break;
		default:
			break;
	}
	SetDiameter(diameter);
	SetArea(diameter);
}
