# Arduino-Smart-Car

Sono presenti tre diversi file al momento tutti in versione beta:

- car_esp: il file da flashare sulla memoria del microcontrollore ESP32 che controlla direttamente i motori atraverso l'uso di due moduli L298N module
- sensor_helper_board1: il file da flashare sulla memoria del microcontrollore Arduino [dispositivo 1] che si occupa di processare il sensore di distanza ad ultrasuoni HC-SR04
- sensor_helper_board2: il file da flashare sulla memoria del microcontrollore Arduino [dispositivo 2] che si occupa di processare il sensore di rilevamento ostruzione 
                        [questo sensore si trova sotto il nome di speed measuring L393 arduino ]
