# robot-car

A a mobile robot system using Raspberry Pi 2 as MPU(Main Processing Unit), Raspberry Pi pico as Slave motion controller, MPU6050 for motion tracking and PCA9685 for PWM motor control.

https://user-images.githubusercontent.com/18543570/194754095-052a0ec9-075b-41be-82cb-38d5c968d773.mov

The Raspberry PI(MPU) communicates with the Rp2040(Slave) over SPI using the following 4 Byte Protocol where each message and response is made up of the following data:

Command | Direction | Speed | Runetime

The rp2040 will echo back each message coming from the MPU which is used as confirmation.

The main controller task on the raspberry pi exposes an cli interface which allows the user to control the robot by sending direction, speed and runetime(how long to move) parameters. These commands are send to the rp2040 over spi interface. The rp2040 in turn sends the neccary commands to the motors via PWM controller.


Below is a system overview of all the different components and how they interact.

![alt text](https://github.com/Fabrice-Beya/robot-car/blob/0dfa4a569ecc2751b2ae9f7f828b8e67c82686ea/System%20Overview.png)

![alt text](https://github.com/Fabrice-Beya/robot-car/blob/main/docs/image_3.jpg)

![alt text](https://github.com/Fabrice-Beya/robot-car/blob/main/docs/image_4.jpg)

TODO:

1. Update the MPU6050 IMU drivers 
2. Add localisation functionalities leverage the IMU.
3. Integration time of flight sensors to detect obstacles
4. Integration a camera.
5. Implement autonomous driving system that avoids collision and detects objects of interest.

