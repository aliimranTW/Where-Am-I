# Where Am I?

This project is a part of the Udacity's "Robotics Software Nano-degree" program. The goal of this project is to learn and implement the Adaptive Monte Carlo Localization filter. ROS AMCL (Adaptive Monte Carlo Localization) package has been used and the parameters have been fine tuned best suited for the application.

To run the simluation, execute the following lines of code:

```
cd catkin_ws
source devel/setup.bash
roslaunch my_robot amcl.launch
```
This should open a custom gazebo world with a robot deployed in it. The robot is a 2-wheel differential drive robot. It should also open an RVIZ window where the proper operation can be visualzied with all the parameters shown. 
