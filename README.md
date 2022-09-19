# robot-car

Developed a driver for the PCA9685 driver by NXP which can driver to H-Bridges to control a 4WD robot car. This is based on the 4WD motor control shield by
by waveshare: https://www.waveshare.com/pico-motor-driver.htm

The motors are attached to the following LED channels:
MA - LED2
MB - LED4
MC - LED8
MD - LED10

This driver can also be used for other use cases besides driving the LED channels above, using the two API functions below:

void SetPwnFrequency(uint32_t freq):

Sets the PWM signal frequency

void SetDutyCycle(uint8_t led, uint16_t percentage):

Set the duty cycle for an led. The channels range from LED0 - LED15.
