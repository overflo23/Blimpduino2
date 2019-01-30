This repository contains a small WEBSERVER for the ESP8266 on the Blimpduino board.

Originally an ESP8266 modules was used eith the standard AT interface.

Since the Android App does not work for me (it fails to send UDP data to the board, but it receives the data from the blimp), I tought i might as well use the ESP to host a webserver with the controls to amke it platform independant.



This code is based on a led control example found here:
https://github.com/tttapa/ESP8266/tree/master/Examples/14.%20WebSocket/A-WebSocket_LED_control



Depends on:
https://github.com/Links2004/arduinoWebSockets
