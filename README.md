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

<!--
F_{drag} = \frac{1}{2} \rho V^2 S C_D
-->



<a href="https://www.codecogs.com/eqnedit.php?latex=F_{drag}&space;=&space;\frac{1}{2}&space;\rho&space;V^2&space;S&space;C_D" target="_blank"><img src="https://latex.codecogs.com/png.latex?F_{drag}&space;=&space;\frac{1}{2}&space;\rho&space;V^2&space;S&space;C_D" title="F_{drag} = \frac{1}{2} \rho V^2 S C_D" /></a>

### Proximity Caution Force

It is a basic model to provide a collision prevention system to the drones. The basic mathematical model that hands out this ability can be observed below:
<!--

$$

F_{proximity} = \hat{\vec{r}} \eta \frac{\zeta}{\left| \vec{r} \right|}

$$
-->

<a href="https://www.codecogs.com/eqnedit.php?latex=F_{proximity}&space;=&space;\hat{\vec{r}}&space;\eta&space;\frac{\zeta}{\left|&space;\vec{r}&space;\right|}" target="_blank"><img src="https://latex.codecogs.com/png.latex?F_{proximity}&space;=&space;\hat{\vec{r}}&space;\eta&space;\frac{\zeta}{\left|&space;\vec{r}&space;\right|}" title="F_{proximity} = \hat{\vec{r}} \eta \frac{\zeta}{\left| \vec{r} \right|}" /></a>

In this formulation, <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\vec{r}" target="_blank"><img src="https://latex.codecogs.com/png.latex?\inline&space;\vec{r}" title="\vec{r}" /></a> symbolizes a distance vector composed between two drones, and <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\hat{\vec{r}}" target="_blank"><img src="https://latex.codecogs.com/png.latex?\inline&space;\hat{\vec{r}}" title="\hat{\vec{r}}" /></a> represents the unit vector in this direction. While <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\eta" target="_blank"><img src="https://latex.codecogs.com/png.latex?\inline&space;\eta" title="\eta" /></a> represents a scalar coeffienct whose optimal value can be found via *fine-tuning*, <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\zeta" target="_blank"><img src="https://latex.codecogs.com/png.latex?\inline&space;\zeta" title="\zeta" /></a> represents the *threshold distance* in which the force model will work. If the current distance between two drone is greater than <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\zeta" target="_blank"><img src="https://latex.codecogs.com/png.latex?\inline&space;\zeta" title="\zeta" /></a>, then the <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;F_{proximity}&space;=&space;0" target="_blank"><img src="https://latex.codecogs.com/png.latex?\inline&space;F_{proximity}&space;=&space;0" title="F_{proximity} = 0" /></a>, in opposite situation, <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;F_{proximity}" target="_blank"><img src="https://latex.codecogs.com/png.latex?\inline&space;F_{proximity}" title="F_{proximity}" /></a> will read as the above equation.

### External Force

It is a user-specified external force model that one can add any force which is desired. It is not a derivation or result of any force model that is implemented here.


### Target Chase Force

It is a force model that represents the situation where there is a target which the subject drone should be followed/aimed. It is contructed by consering a simple *spring-mass-damper* system. Therefore, it can be formulated as the following:

<!--

$$

F_{target} = \vec{r} k   + \vec{v} d

$$
-->

<a href="https://www.codecogs.com/eqnedit.php?latex=F_{target}&space;=&space;\vec{r}&space;k&space;&plus;&space;\vec{v}&space;d" target="_blank"><img src="https://latex.codecogs.com/png.latex?F_{target}&space;=&space;\vec{r}&space;k&space;&plus;&space;\vec{v}&space;d" title="F_{target} = \vec{r} k + \vec{v} d" /></a>

where *k* and *d* represent the spring and damping coefficient, respectively.

## Sim

It is the main class which is responsible for the general management of the simulation. It can handle the initial drone orientation, and the propagation of the whole simulation.

