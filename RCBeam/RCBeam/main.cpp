// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "geometry.h"
#include "RCBeam.h"
#include "MomentAnalysis.h"
#include "StructAnalysis.h"

int main()
{
    // SAM35 35MPa concrete
    //Concrete* pSAM35 = createHognestadConcrete(5300.0);
    std::shared_ptr<Concrete> pSAM35(createHognestadConcrete(5076.33));

    // Gr60, Gr70 Steel
    std::shared_ptr<Steel> pGr60(createEPPSteel(69.0e3, 30.0e6));
    std::shared_ptr<Steel> pGr70(createEPPSteel(72519.0, 30382139.0));

    // Create Rebar
    std::shared_ptr<Rebar> pNo6(new Rebar(pGr60, 6));   // number 6
    std::shared_ptr<Rebar> pNo7(new Rebar(pGr60, 7));   // number 7
    std::shared_ptr<Rebar> pNo8(new Rebar(pGr60, 8));   //number 8
    std::shared_ptr<Rebar> pM10(new Rebar(pGr70, 3.1496));   // Metric 10

    /*
    Ideally would want a program that accepts input and then runs calculations.
    But that would take some major restructuring (possible, but time consuming. More concerned with business logic here ATM.
    So lets comment out the parts about inputs, and just run the case that we are interested in.

    Running with Feldman-Seiss / Koch-Stone beams series B1.
    */

    // create a beam with clear span length 9ft
    double beam_length = 9.0;
    double beam_width = 6.0;
    double beam_height = 12.0;

    
    //std::cout << "Enter Beam Width (inches): ";
    //std::cin >> beam_width;

    //std::cout << "Enter Beam Height (inches): ";
    //std::cin >> beam_height;

    //std::cout << "Enter Beam Length (feet): ";
    //std::cin >> beam_length;

    // Create beam cross section:
    std::shared_ptr<RectangularBeam> pBeamSection(new RectangularBeam(beam_width, beam_height, pSAM35, beam_length * 12.0));
    // Create Beam:
    std::shared_ptr<RCBeam> TestRCBeam(new RCBeam(pBeamSection,beam_length*12.0));

    // Add Rebars (2#6 Compression, 2#7 Tension)
    TestRCBeam->AddRebarLayer(2, pNo6, 1.5);
    TestRCBeam->AddRebarLayer(2, pNo7, 10.5);
    TestRCBeam->Refresh();

    std::cout << "Gross Beam Properties:\n";
    //std::cout << "Area:\t" << TestBeam.getAreaGross() << std::endl;
    //std::cout << "width\t" << TestBeam.getWidth() << std::endl;
    //std::cout << "height\t" << TestBeam.getHeight() << std::endl;
    //std::cout << "Ixx:\t" << TestBeam.getIxx() << std::endl;
    std::cout << "Length:\t" << TestRCBeam->getBeamLength() << std::endl;

    std::cout << "Concrete Propreties:" << std::endl;
    std::cout << "Strength:\t" << pSAM35->getStrength() << std::endl;

    std::cout << "RC Beam Properties:" << std::endl;
    std::cout << "Rebar layers:\t" << TestRCBeam->getNumRebarLayers() << std::endl;
    std::cout << "A_s gross:\t" << TestRCBeam->getAsteel_gross() << std::endl;
    for (int i = 0; i < TestRCBeam->getNumRebarLayers(); i++)
    {
        std::cout << "Rebar depth:\t" << TestRCBeam->getSteelLayerDepth(i) << std::endl;
        std::cout << "Rebar area:\t" << TestRCBeam->getAsteel(i) << std::endl;
        std::cout << "Rebar strength:\t" << pNo7->getYieldStress() << std::endl;
    }

    // Moment phi calculations
    // Create vector of maximum concrete strain
    std::vector<double> eps_cm;
    eps_cm.push_back(0.0);
    // create vector of neutral axis depth
    std::vector<double> c_na;
    c_na.push_back(TestRCBeam->getBeamHeight() / 2);
    // create vector of curvature
    std::vector<double> phi;
    phi.push_back(0.0);
    // create vector of moment
    std::vector<double> M;
    M.push_back(0.0);

    // Create vector of concrete stress
    std::vector<double> sigma_concrete;
    sigma_concrete.push_back(0.0);

    // use ultimate concrete strain as eps max
    double eps_cm_max = 10*1.5 * pSAM35->getEpsCu();
    // number of steps and strain step-size
    int n_steps = 1001;
    double delta_eps_cm = (eps_cm_max / n_steps);

    // report data:
    std::cout << "Performing Moment-Curvature Analysis to maximum compression strain of " << eps_cm_max << ". . ."<< std::endl;


    // loop through and calculate epsilon, moment, phi
    for (int i = 1; i <= n_steps; i++)
    {
        // increment eps_cm
        eps_cm.push_back(i * delta_eps_cm);
        // store concrete stress
        sigma_concrete.push_back(pSAM35->getStress(eps_cm.back()));
        // Run Moment function to calculate c,M
        M.push_back(MomentEpscm(eps_cm.back(), TestRCBeam, pSAM35, pGr60, c_na));
        // Calculate phi
        phi.push_back(eps_cm.back() / c_na.back());
        //std::cout << eps_cm.back() << "\t" << c_na.back() << "\t" << phi.back() << "\t" << M.back() << std::endl;
    }


    // TODO: Sort M,phi before running p-delta analysis.
    std::sort(phi.begin(), phi.end());

    // Load-displacement calculations -- need full moment-curvature relationship
    // create vector of loads:
    std::vector<double>P;

    // choose load location:
    double xp = TestRCBeam->getBeamLength() * 0.5;  //central point load

    // Choose deflection location:
    double x0 = xp; //location of deflection

    std::cout << "Performing Load-Deflection calculation using calculated moments. . ." << std::endl;
    
    // calculate deflection for each curvature value:
    std::vector<double>displacement;
    for (int i = 0; i <=n_steps; i++)
    {
        // Calculate load
        P.push_back(4 * M.at(i) / TestRCBeam->getBeamLength());
        // calculate displacement
        displacement.push_back(Deflection_PointLoad(TestRCBeam, P.at(i), M, phi, xp, x0));
    }

    // Print results:
    // Set format
    /*
    std::cout.unsetf(std::ios::floatfield);                // floatfield not set
    std::cout.setf(std::ios::scientific, std::ios::floatfield);
    std::cout.precision(4);
    std::cout << "Moment phi calculations\n";
    std::cout << "EPS\t\tC\t\tPHI\t\tM\t\tDelta\t\tLoad" << std::endl;;
    //std::cout << "Deflection\tLoad" << std::endl;
    for (int i = 0; i <= n_steps; i++)
    {
        std::cout << eps_cm.at(i) << "\t" << c_na.at(i) << "\t" << phi.at(i) << "\t" << M.at(i)<<"\t";
        std::cout << displacement.at(i) << "\t" << P.at(i) << std::endl;
    }
    */
    
    // Output data to csv.
    // create file pointer
    std::ofstream outputfile;

    std::cout << "Writing data to file. . ." << std::endl;

    // open file in output truncate
    outputfile.open("c:\\RCBeam\\m-phi.csv", std::ios::out | std::ios::trunc);
    // check to make sure file opened correctly
    if (outputfile.is_open())
    {
        // write the header line
        outputfile << "phi,M,eps_cm,c,sigma_c\n";
        // write the data lines
        for (auto i = 0; i <= n_steps; i++)
        {
            outputfile << phi.at(i) << "," << M.at(i) << "," << eps_cm.at(i) <<","<<c_na.at(i)<<","<< sigma_concrete.at(i) << "\n";
        }
        outputfile.close();
    }
    else
    {
        std::cout << "Could not open m-phi file for writing.\n";
    }
    // Close the file
    outputfile.close();

    // Open file for p-delta
    outputfile.open("c:\\RCBeam\\p-delta.csv", std::ios::out | std::ios::trunc);
    // check to make sure file opened correctly
    if (outputfile.is_open())
    {
        // write the header line
        outputfile << "delta,load\n";
        // write the data lines
        for (auto i = 0; i <= n_steps; i++)
        {
            outputfile << displacement.at(i)<<","<<P.at(i) << "\n";
        }
        outputfile.close();
    }
    else
    {
        std::cout << "Could not open file for writing.\n";
    }
    // Close the file
    outputfile.close();
        
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

