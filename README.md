# README #

Lab of Applied Robotics course project, University of Trento, 2015 - 2016.

### Content ###

This lab project consists of three phrases
* Get the valocity of the NXT motor and send the data back to computer through bluetooth
* Build second order system model for nxt motor; Design digital controller and simulate closed loop
system; Generate software implementation of controller for LEGO NXT motor
* Generate software implementation of controller for the LEGO robot which has two motor, so you need to make a balance of the two wheels

The software code is in ./sources fold, and the ./scicos fold contains files used to get the parameters of second order system of the motor, and the design of the controller. We used root locus method to get the parameters of the controller. Finally we make the motor settling time less than 400 ms to reach steady state which we considered to be 95% of the final value.

