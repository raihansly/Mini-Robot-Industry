#include <SPI.h>
#include <RF24.h>
#include <nRF24l01.h>

RF24 radio (14, 15);

const byte address [6] = "00001";
int readData [5];
byte sensorDataValue [10];

void setup()
{
  Serial.begin (9600);

  radio.begin ();
  radio.openReadingPipe (0, address);
  radio.setPALevel (RF24_PA_MIN);
  radio.startListening ();
}

void loop()
{
  if (radio.available ())
  {
    radio.read (readData, sizeof (readData));

    if (readData [0] == 123)
    {
      sensorDataValue [0] = readData [0];
      sensorDataValue [1] = readData [1];
      sensorDataValue [2] = readData [2];
      sensorDataValue [3] = readData [3];
      sensorDataValue [4] = readData [4];
      Serial.println ("==================== PLC 1 ====================");
      Serial.print ("Address : ");
      Serial.println (sensorDataValue [0]);
      Serial.print ("Sensor 1 : ");
      Serial.println (sensorDataValue [1]);
      Serial.print ("Sensor 2 : ");
      Serial.println (sensorDataValue [2]);
      Serial.print ("Sensor 3 : ");
      Serial.println (sensorDataValue [3]);
      Serial.print ("Sensor 4 : ");
      Serial.println (sensorDataValue [4]);
    }
    
    else if (readData [0] == 321)
    {
      sensorDataValue [5] = readData [0];
      sensorDataValue [6] = readData [1];
      sensorDataValue [7] = readData [2];
      sensorDataValue [8] = readData [3];
      sensorDataValue [9] = readData [4];
      Serial.println ("==================== PLC 2 ====================");
      Serial.print ("Address : ");
      Serial.println (sensorDataValue [5]);
      Serial.print ("Sensor 1 : ");
      Serial.println (sensorDataValue [6]);
      Serial.print ("Sensor 2 : ");
      Serial.println (sensorDataValue [7]);
      Serial.print ("Sensor 3 : ");
      Serial.println (sensorDataValue [8]);
      Serial.print ("Sensor 4 : ");
      Serial.println (sensorDataValue [9]);
    }
  }
}
