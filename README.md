# HomeRobot
Project to develop an Autonomous Robot with 2 DC motors, including Hall Encoders,sensors for indoor navigation 
The robot can communicate via WLAN link

## Short Specification

Power Supply
- The robot carries a rechargeable battery with 9.6V and 750mAh
- Motor driver is directly supplied by the battery voltage (VBAT)
- The Arduino microcontroller board is supplied by its onboard +5V LDO
- 

Motor Control
- Controlled by Arduino Mega Board
- Each DC Motor includes HALL sensors to feedback the actual speed by a PWM duty
- The motor currents for both motors are provided by an L293D motor driver
- The motor driver IC is controlled by the Arduino board

Motor Encoder / Speed Feedback 
- The encoder outputs of both DC motors are directly routed to the Arduino to evaluate speed and direction (CW/CCW)
- The used pins are assigned to port interrupts
- Timing information for the speed evaluation is derived by the Timer Unit of the Atmel IC on the Arduino

## Speed Control
- 
