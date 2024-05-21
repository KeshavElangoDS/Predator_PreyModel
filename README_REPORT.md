# Predator-Prey Project Report

This project simulates the behavior of a predator and multiple preys. We specifically modeled the predator to consume preys in regions where movement is slowed down (slow terrain), while ensuring the prey attempts to avoid the predator.

# Structure
We used four classes in managing the simulation used in the project. These include:
- **Model**:  The model class is responsible for setting up the simulation with defined number of preys, predator speed, prey speed, seed, and region limits, based on a configuration file. Also, it updates the state of the entities in the model.
- **Environment**: It is used for handling boundaries within the simulation, ensuring that the predator and prey do not go out of the defined regions. This class makes sure the direction of the entities reflects when it reach certain region limit.  We added the slow and fast terrains so the preys are restricted within certain areas of the environment.
- **Predator**: We used this class to ensure the predator chases the prey, then eats the prey when the distance is less than 1. It also adjusts the predators position and speed based on the current direction of prey
- **Prey**: The flee function in this class allow preys to move away from the predator. The movement and speed of preys depend on whether the prey is in a speed or slow terrain. Finally, we implement a deplete function to reduce the number of preys when  they are eaten by the predator.

# Complexities
- Some complexities were the compilation issues due to initialization missed for some variables in the class body under header file along with the initialization of variables in Model constructor.
- Selecting an apt value for the limits of the slow and speed terrain to be visible in the dashboard along with the condition tweaking to make sure prey moves away from the predator were also some of the complications.
 

# Issues

- There was an issue wherein the make dashboard opens the pop-up window of the dashboard however when clicking "Play", there was no change in the dashboard.
- This issue was resolved by adding "initialize()" function call in the Model constructor as it was missing in the dependency code between Python and C++.
- There was an issue with the include file declaration leading to files imported in a circular fashion between various classes. Removed by declaring an empty Predator class under Prey file.
 

# Improvements

- The shapes of the terrains could be changed for both the slow and fast terrains.
- Walls could be added to restrict the movement and reflect within the region.
