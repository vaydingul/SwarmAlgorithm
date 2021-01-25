# Swarm Algorithm

This is a very basic approach to *Swarm Algorithm*.
There are two main classes in this project, namely, **Drone** and **Sim**.

## Drone

It is the main class that is responsible for the motion propagation of the **Drone** entity. It governs all the equations of motion in **2D** space. There are several defined *Force Models* in the project, which can be exemplified as:

- Drag force
- Proximity Caution force
- External force
- Target Chase force

### Drag Force

It is the **2D** representation of the aerodynamic drag force, which can be formulated as the following:

$$
F_{drag} = \frac{1}{2} \rho V^2 S C_D
$$

### Proximity Caution Force

It is a basic model to provide a collision prevention system to the drones. The basic mathematical model that hands out this ability can be observed below:

$$

F_{proximity} = \hat{\vec{r}} \eta \frac{\zeta}{\left| \vec{r} \right|}

$$

In this formulation, $\vec{r}$ symbolizes a distance vector composed between two drones, and $\hat{\vec{r}}$ represents the unit vector in this direction. While $\eta$ represents a scalar coeffienct whose optimal value can be found via *fine-tuning*, $\zeta$ represents the *threshold distance* in which the force model will work. If the current distance between two drone is greater than $\zeta$, then the $F_{prozimity} = 0$, in opposite situation, $F_{proximity}$ will read as the above equation.

### External Force

It is a user-specified external force model that one can add any force which is desired. It is not a derivation or result of any force model that is implemented here.


### Target Chase Force

It is a force model that represents the situation where there is a target which the subject drone should be followed/aimed. It is contructed by consering a simple *spring-mass-damper* system. Therefore, it can be formulated as the following:

$$

F_{target} = \vec{r} k   + \vec{v} d

$$

where $k$ and $d$ represent the spring and damping coefficient, respectively.

## Sim

It is the main class which is responsible for the general management of the simulation. It can handle the initial drone orientation, and the propagation of the whole simulation.

