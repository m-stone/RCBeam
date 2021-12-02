# RCBeam
Reinforced Concrete Beam Analysis

This is an application to solve the moment-curvature and 3-point load deflection relationship for a reinforced concrete beam. Material models are handled in a separate, non-provided DLL. Similarly, some of the back-end numerical analysis is done in a separate non-provided library, but these are currently limited to basic root-finding and derivative/integration algorithms; code for these can be found in many books or other libraries such as Boost.

Inputs are defined in main.cpp, and the full moment-curvature relationship is calculated to a defined maximum compressive strain. The corresponding load for each moment is then calculated using statics, and the deflection is calculated based on the Moment-Area theorem; the applied load required to generate that moment is then used to generate a resistance function for the beam.

The demonstrated method uses a Hognestad material model for the concrete, and a EPP steel model. Other material models developed include linear elastic (steel and concrete), Todeschini/Power (concrete), User-defined (concrete), and Hsu tension-stiffening (steel). Tension of concrete is modeled using tension stiffening models based on DP tests of reinforced prismatic specimens.

Results are then written to two CSV files located at c:\RCBeam\ with columns for curvature, moment; and columns for displacement, load. 

Units are US standard -- usually inches, lbs. 

The test beam is from tests performed on RC Beams by me during my MS at UF. The beam is a 10' long (9' clear span), 6"x12" simply supported beam reinforced with nominal Grade 60 rebar -- 2#6 @ 1.5" for compression and 2#7 @ 10.5" for tension. The beam is shear reinforced with closed #3 stirrups at 5" o/c. The concrete material is SAM-35 from ERDC, with a target 28-day compressive strength of 35 MPa. Shear is not taken into account. Steel model is EPP with yield strength of 60ksi, and the concrete model is shown below.

### Material Properties
![image](https://user-images.githubusercontent.com/1676839/144453511-91a11a54-0284-4326-aef5-d7cf7a5b8c2e.png)

### Moment-Curvature
![image](https://user-images.githubusercontent.com/1676839/144312309-6447cc2c-f77b-45f7-8dc7-168e853ef5ad.png)

### 3-point Load-deflection graph
![image](https://user-images.githubusercontent.com/1676839/144312335-7f2a03a3-4c42-4858-998e-f29907001105.png)

#### Initial run:
![image](https://user-images.githubusercontent.com/1676839/144454647-f4877067-ab1c-4fb8-8962-71242df86df3.png)
