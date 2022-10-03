#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <elapsedMillis.h>

#define photoElectric2  4
#define robotIR         6

RF24 radio (9, 10);
elapsedMillis readTime;
elapsedMillis sendTime;

unsigned long readInterval = 500;
unsigned long sendInterval = 750;

/*
 Pin 9 = CE "CHIP ENABLE"
 Pin 10 = CSN "CHIP SELECT NOT"
 Pin 11 = MOSI "MASTER OUT SLAVE IN"
 Pin 12 = MISO "MASTER IN SLAVE OUT"
 Pin 13 = SCK  "SERIAL CLOCK"
*/

const byte address [6] = "00001";
int sensorDataValue [3];

void setup() 
{
    Serial.begin (9600);

    pinMode (photoElectric2, INPUT_PULLUP);
    pinMode (robotIR, INPUT);

    radio.begin ();
    radio.openWritingPipe (address);
    radio.setPALevel (RF24_PA_MIN);
    radio.stopListening ();
}

void loop() 
{
    if (readTime >= readInterval)
    {
        int PE2Value = digitalRead (photoElectric2);
        int IRValue = digitalRead (robotIR);

        sensorDataValue [0] = 321;        //ADDRESS
        sensorDataValue [1] = PE2Value;
        sensorDataValue [2] = IRValue;

        Serial.print ("Address  : ");
        Serial.print (sensorDataValue [0]);
        Serial.print ("\t");
        Serial.print ("Photoelectric Sensor : ");
        Serial.print (sensorDataValue [1]);
        Serial.print ("\t");
        Serial.print ("Robot IR Sensor      : ");
        Serial.println (sensorDataValue [2]);

        readTime = 0;
    }

    if (sendTime >= sendInterval)
    {
        radio.write (sensorDataValue, sizeof (sensorDataValue));
        sendTime = 0;
    }
}
