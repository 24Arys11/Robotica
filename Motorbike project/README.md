Video:
https://drive.google.com/open?id=12x-1VLpoKgxB6xsT153YVjlRkCbq5Epa

# Motorbike-project

## Description:

It's a very cool, 3D printed, self ballancing motorbike controlled via radio-commands.

## Features:

Self ballancing: It uses a servo motor and a weight to keep it's ballance - (well it's not perfect, yet..)

Directions (8 possible): right, right-forward, forward, left-forward, left, left-backward, backward, right-backward.

* When you use right or left, with or without movement (forward or backward) the turning signals on the appropriate side are going to blink automatically.

All the stops are active by default, but when you move forward (with or without steering) the 4 small LEDs on the back are turned off.

Horn - triggerd by the button of the controller
Lights (toggleable) - SW joy button. (powerfull 10 LEDs light)

# Documentation:

About PID control:
https://www.youtube.com/watch?v=0vqWyramGy8
https://www.youtube.com/watch?v=crw0Hcc67RY
https://www.youtube.com/watch?v=wkfEZmsQqiA&list=PLn8PRpmsu08pQBgjxYFXSsODEF3Jqmm-y&index=1

About Radio control:
https://www.youtube.com/watch?v=7rcVeFFHcFM

About GY-521 (Gyroscope and Accelerometer sensor):
https://www.youtube.com/watch?v=wTfSfhjhAU0

About dc motors (with driver) and servo motors:
(see "Laboratory no. 8 (TAs).pdf")

# Components:
2x arduino nano (one for the radio control, and one inside the motorbike)
2x power suply HW-131
1x push button circuit (resistor included).
1x joystick
2x radio module HW-237
1x GY-521 (Gyroscope and Accelerometer sensor)
2x MG995 Servo motor (see datasheet: "MG995-ETC.pdf")
2x F09195-Z dc motors
1x L293D motor driver
2x Pololu Wheel 80×10mm (https://www.optimusdigital.ro/en/wheels/11081-pololu-wheel-8010mm-pair-black.html)
1x switch button
10x white LEDs
1x red LED
4x yellow LEDs
2x yellow LEDs (mini)
4x red LEDs (mini)
1x active buzzer
2x 1000mAh 45C LIPO batteries
1x AC/DC adaptor LJS-19B (output 9V 1000mA) or 1x 450mAh 30C LIPO battery or 1x 9V battery (your choice - for radio control device)
1x weight (about 600g) - I used a stepper motor (temporary).
other materials: PCB's, wires, black hobby glass, plexyglass..

(!) Everything beside the weels was 3D printed (designed by Irina Chitu) inspired from Honda Gold Wing 2019 !

# Pinouts:

## Radio controller pinout:

Button................5
Joy X axis............A1
Joy Y axis............A2
Joy SW button.........4
CSN...................8
CE....................7
MOSI..................11
SCK...................13
MISO..................12

## Motorbike pinout:

Big STOP LED..........2
Buzzer................4
Servo direction.......5
Servo ballance........6
CSN...................8
CE....................7
MOSI..................11
SCK...................13
MISO..................12
DC motors.............9 and 10 (they are connected as 1 single DC, for more power)
Lights................14/A0 (used as digital)
Right turning signal..15/A1 (used as digital)
Left turning signal...16/A2 (used as digital)
Small STOP LEDs.......17/A3 (used as digital)
GY-521................18/A4 (SCL)
GY-521................19/A5 (SDA)
