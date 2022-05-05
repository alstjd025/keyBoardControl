keyBoardControl
==============
# About

This repository contains keyBoardControl node for Testing ICHTHUS CONTROLLER

# How To Use

How To Build Package 
     
'git clone ~'    
'colcon build --packages-select keyboardcontrol'    

In terminal A    
'. install/setup.bash'    
'ros2 run keyboardcontrol getKeyBoard'

In terminal B   
'. install/setup.bash'    
'ros2 run keyboardcontrol testKeyBoard'

# Requirements
ROS2 - Galactic    
curses (generally gnu contains this library for default)

#Author
Minsung Kim (alstjd025@naver.com)
