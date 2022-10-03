#include <SPI.h>
#include <RF24.h>
#include <nRF24l01.h>

RF24 radio (14, 15);

const byte address [6] = "00001";
int readData [3];
byte sensorDataValue [6];

byte stepMove, stepStop;

void setup()
{
  Serial.begin (9600);

  radio.begin ();
  radio.openReadingPipe (0, address);
  radio.setPALevel (RF24_PA_MIN);
  radio.startListening ();

  stepMove = 0;
  stepStop = 0;
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
      Serial.println ("==================== PLC 1 ====================");
      Serial.print ("Address              : ");
      Serial.println (sensorDataValue [0]);
      Serial.print ("Photoelectric Sensor : ");
      Serial.println (sensorDataValue [1]);
      Serial.print ("Robot Sensor         : ");
      Serial.println (sensorDataValue [2]);
    }

    else if (readData [0] == 321)
    {
      sensorDataValue [3] = readData [0];
      sensorDataValue [4] = readData [1];
      sensorDataValue [5] = readData [2];
      Serial.println ("==================== PLC 2 ====================");
      Serial.print ("Address              : ");
      Serial.println (sensorDataValue [3]);
      Serial.print ("Photoelectric Sensor : ");
      Serial.println (sensorDataValue [4]);
      Serial.print ("Robot Sensor         : ");
      Serial.println (sensorDataValue [5]);
    }
  }
}
