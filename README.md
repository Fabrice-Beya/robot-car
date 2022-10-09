# robot-car

A a mobile robot system using Raspberry Pi 2 as MPU(Main Processing Unit), Raspberry Pi pico as Slave motion controller, MPU6050 for motion tracking and PCA9685 for PWM motor control.

The Raspberry PI(MPU) communicates with the Rp2040(Slave) over SPI using the following 4 Byte Protocol:

Command | Direction | Speed | Runetime

The Rp2040 receives these messages and executes accordings, returns the message back to the MPU as confirmation.

Below is a system overview of all the different components and how they interact.

![alt text](https://github.com/Fabrice-Beya/robot-car/blob/0dfa4a569ecc2751b2ae9f7f828b8e67c82686ea/System%20Overview.png)

![alt text](https://github.com/Fabrice-Beya/robot-car/docs/image_3.jpg)

![alt text](https://github.com/Fabrice-Beya/robot-car/docs/image_4.jpg)

