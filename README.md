# GPS_detach
Case file #002: GPS sensor reading &amp; balloon detach based on condition @NTUAS

## Description
Locate position (longitude & latitude) of weather observation module. </br>
Detach balloon when module reaches certain position or region.</br>

## Materials
![alt text](./src/materials.jpg)
### Arduino UNO
### Seeed grove GPS module
- Communication protocol UART. </br>
### Relay & detaching device 
- Relay: given high voltage with digital signal from Arduino. </br>
- Detach device: Temporarily respresented with fuse on the wiring diagram. </br>

## Wiring
![alt text](./src/wiring.JPG)

## Demo
Represent detach device with LED. </br>
Give off high voltage signal when reaching certain displacement. </br>
![alt text](./src/log.jpg)
![alt text](./src/demo.jpg)
