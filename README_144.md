=====================================================================
The computer simulation of hamsters aims to model the behaviour of a hamster in a laboratory. The behaviour is characterised by different states, such as wandering, idle, targeting food and feeding. 
Further the organ of the hamster is visualized by an internal view. An organ is a superposition of ECM, blood, and organ cells. Additionally, it is possible to set tumoral cells. This is manually done during the simulation.
A hamster has a healthy and a sick state before he then eventually dies due to his sickness. The cancer can be treated with feeding cheese to the hamster or by increasing the inhibitor Bromopyruvate manually in the internal view.

COMPILATION AND EXECUTION:
This project uses Cmake to compile.

Command line:
in the build folder: cmake ../src
take app.json as configuration file

In QTCreator:
setting up the project: open the src/CMakeLists.txt file
choose the target to execute

MAIN TARGETS:
application -> corresponds to the final application, all features can be seen in this target.
bloodSystem -> autonomous drawing of capillaries. With key 6, a capillary grows to the right, and with key 5, it 	       grows to the left. In between, key 0 must be pressed each time.
diffusionTest -> perfect to see the diffusion of Substance.

CONFIGURATION FILES
The configuration file to use for the application is app.json. It shows the complete application. If the simulation is not running smoothly, it is possible to use appSmall.json.
The configuration file for bloodSystem is the default file given.
The configuration file for diffusionTest is appDiff.json.

COMMANDS
The commands for using a particular feature are given in a help panel on the right side of the simulation window.
Most important commands:
-	H for placing a hamster
-	F for placing food
-	C for placing cheese (extension)
-	X for placing a tumoral cell

DESIGN MODIFICATION
The project coding has been done in accordance with the specifications (no personal modifications of suggested design elements).

EXTENSIONS
In our project, we implemented the following extensions:
-	At a given number of cancer cells our hamster is considered sick. The state sick implies following 	changes: walking slower, different appearance
-	If the cancer is not treated and the number of cancer cells keeps increasing (we are taking track of them 	with a counter in the organ class) the hamster dies due to his sickness
-	For treating the cancer it is possible to simply feed cheese to the hamster (key “c”) which does then 	increase the inhibitor Bromopyruvate.
