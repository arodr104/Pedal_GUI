# Pedal_GUI
## Setup
Copy both GUIslice and XPT2046_Touchscreen-master folders to your Arduino libraries folder (usually found in Documents\Arduino\libraries, if unsure, open the Arduino IDE and go to File > Preferences and look at Sketchbook location for the correct path). Once both folders are in the Arduino library, open the file GUI.ino from the GUI folder and compile as normal.

## Pinout

ILI9341 Pin | Teensy 4.1 |
--- | --- |
VCC | VIN |
GND | GND |
CS | 10 |
RESET | +3.3V |
D/C | 9 |
SDI (MOSI) | 11 (DOUT) |
SCK	| 13 (SCK)	|
LED | VIN |
SDO (MISO)	| 12 (DIN)	|
T_CLK | 13 (SCK)	|
T_CS | 33 |
T_DIN | 11 (DOUT)	|
T_DO | 12 (DIN)	|
