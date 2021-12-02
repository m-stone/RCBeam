# RCBeam
Reinforced Concrete Beam Analysis

This is an application to solve the moment-curvature and 3-point load deflection relationship for a reinforced concrete beam. The method uses a modified Hognestad material model for the concrete, and a EPP steel model. Inputs are defined in main.cpp, and the full moment-curvature relationship is calculated. The beam is then divided up into sections, and for a given applied load the curvature along the length of the beam is calculated. Using the moment-area theorem, the total deflection is then calculated. 

Results are then written to two CSV files located at c:\RCBeam\ with columns for curvature, moment; and columns for displacement, load. 

Units are in US standard -- usually inches, lbs. 

The test beam is from tests performed on RC Beams based on work done by me during my MS at UF. The beam is a 10' long (9' clear span) simply supported beam reinforced with Gr60 rebar -- 2#6 for compression and 2#7 for tension. The beam is shear reinforced with closed #3 stirrups at 5" o/c. The concrete material is SAM-35 from ERDC, with a target 28-day compressive strength of 35 MPa. Shear is not taken into account. Steel model is EPP with yield strength of 60ksi, and the concrete model is shown below. Concrete tension stiffening is taken into account.

### Material Properties
![image](https://user-images.githubusercontent.com/1676839/144453511-91a11a54-0284-4326-aef5-d7cf7a5b8c2e.png)

### Moment-Curvature
![image](https://user-images.githubusercontent.com/1676839/144312309-6447cc2c-f77b-45f7-8dc7-168e853ef5ad.png)

### 3-point Load-deflection graph
![image](https://user-images.githubusercontent.com/1676839/144312335-7f2a03a3-4c42-4858-998e-f29907001105.png)

#### Initial run:
![image](https://user-images.githubusercontent.com/1676839/144454647-f4877067-ab1c-4fb8-8962-71242df86df3.png)
