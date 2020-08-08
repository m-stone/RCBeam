// RCBeam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Material.h"
#include "Concrete.h"
#include "Steel.h"
#include "RectangularBeam.h"

int main()
{
    std::cout << "Hello World!\n";

    // Create SAM-35 Test concrete
    Concrete SAM35;
    // Create Gr 60 Steel for rebar
    Steel Gr60;

    // Set up Geometry and Boundary Conditions
    // Gross Beam
    RectangularBeam TestBeam(6.0, 12.0);
    // Steel Geometry


    std::cout << "Beam Properties:\n";
    std::cout << "Area:\t" << TestBeam.GetArea() << std::endl;
    std::cout << "width\t" << TestBeam.GetWidth() << std::endl;
    std::cout << "height\t" << TestBeam.GetHeight() << std::endl;
    std::cout << "Ixx:\t" << TestBeam.GetIxx() << std::endl;

    //
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
