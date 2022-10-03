#include <SPI.h>
#include <RF24.h>
#include <nRF24l01.h>

RF24 radio (9, 10);

/*
 Pin 9 = CE "CHIP ENABLE"
 Pin 10 = CSN "CHIP SELECT NOT"
 Pin 11 = MOSI "MASTER OUT SLAVE IN"
 Pin 12 = MISO "MASTER IN SLAVE OUT"
 Pin 13 = SCK  "SERIAL CLOCK"
*/

const byte address [6] = "00001";
int sensorOptoValue [4];

void setup() 
{
    Serial.begin (9600);
    
    radio.begin ();
    radio.openReadingPipe (0, address);
    radio.setPALevel (RF24_PA_LOW);
    radio.startListening ();

}

void loop() 
{
    if (radio.available ())
    {
        radio.read (sensorOptoValue, sizeof (sensorOptoValue));
        int PE1Value = sensorOptoValue [0];
        int IPValue = sensorOptoValue [1];
        int PE2Value = sensorOptoValue [2];
        int PE3Value = sensorOptoValue [3];

        Serial.print ("Sensor 1 : ");
        Serial.print (PE1Value);
        Serial.print ("\t");
        Serial.print ("Sensor 2 : ");
        Serial.print (IPValue);
        Serial.print ("\t");
        Serial.print ("Sensor 3 : ");
        Serial.print (PE2Value);
        Serial.print ("\t");
        Serial.print ("Sensor 4 : ");
        Serial.println (PE3Value);
    }

    else
    {
      Serial.println ("OUT OF RANGE");
    }

    delay(1000);
}
