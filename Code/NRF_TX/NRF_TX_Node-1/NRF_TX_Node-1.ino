#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <elapsedMillis.h>

#define photoElectric1 2
#define inductiveProximity 3
#define photoElectric2 4
#define photoElectric3 5

RF24 radio (9, 10);
elapsedMillis readTime;
elapsedMillis sendTime;

unsigned long readInterval = 500;
unsigned long sendInterval = 1000;

/*
 Pin 9 = CE "CHIP ENABLE"
 Pin 10 = CSN "CHIP SELECT NOT"
 Pin 11 = MOSI "MASTER OUT SLAVE IN"
 Pin 12 = MISO "MASTER IN SLAVE OUT"
 Pin 13 = SCK  "SERIAL CLOCK"
*/

const byte address [6] = "00001";
int sensorDataValue [5];

void setup() 
{
    Serial.begin (9600);

    pinMode (photoElectric1, INPUT_PULLUP);
    pinMode (inductiveProximity, INPUT_PULLUP);
    pinMode (photoElectric2, INPUT_PULLUP);
    pinMode (photoElectric3, INPUT_PULLUP);

    radio.begin ();
    radio.openWritingPipe (address);
    radio.setPALevel (RF24_PA_MIN);
    radio.stopListening ();
}

void loop() 
{
    if (readTime >= readInterval)
    {
        int PE1Value = digitalRead (photoElectric1);
        int IPValue = digitalRead (inductiveProximity);
        int PE2Value = digitalRead (photoElectric2);
        int PE3Value = digitalRead (photoElectric3);

        sensorDataValue [0] = 123;        //ADDRESS
        sensorDataValue [1] = PE1Value;
        sensorDataValue [2] = IPValue;
        sensorDataValue [3] = PE2Value;
        sensorDataValue [4] = PE3Value;

        Serial.print ("Address  : ");
        Serial.print (sensorDataValue [0]);
        Serial.print ("\t");
        Serial.print ("Sensor 1 : ");
        Serial.print (sensorDataValue [1]);
        Serial.print ("\t");
        Serial.print ("Sensor 2 : ");
        Serial.print (sensorDataValue [2]);
        Serial.print ("\t");
        Serial.print ("Sensor 3 : ");
        Serial.print (sensorDataValue [3]);
        Serial.print ("\t");
        Serial.print ("Sensor 4 : ");
        Serial.print (sensorDataValue [4]);

        readTime = 0;
    }

    if (sendTime >= sendInterval)
    {
        radio.write (sensorDataValue, sizeof (sensorDataValue));
        sendTime = 0;
    }
}    
