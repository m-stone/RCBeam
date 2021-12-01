# RCBeam
Reinforced Concrete Beam Analysis

This is an application to solve the moment-curvature and 3-point load deflection relationship for a reinforced concrete beam. The method uses a modified Hognestad material model for the concrete, and a EPP steel model. Inputs are defined in main.cpp, and the full moment-curvature relationship is calculated. The beam is then divided up into sections, and for a given applied load the curvature along the length of the beam is calculated. Using the moment-area theorem, the total deflection is then calculated. 

Results are then written to two CSV files located at c:\RCBeam\ with columns for curvature, moment; and columns for displacement, load. 

Units are in US standard -- usually inches, lbs. 
