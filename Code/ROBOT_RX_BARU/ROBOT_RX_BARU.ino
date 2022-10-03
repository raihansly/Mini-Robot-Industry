// D2     
// D3     
// D4     
// D5     SERVO BASE PWM
// D6     SERVO GRIPPER PWM
// D7     IR RIGHT
// D8     IR LEFT
// D9     DRIVER PWM (ENA)
// D10    DRIVER PWM (ENB)
// D11    MOSI NRF
// D12    MISO NRF
// D13    SCK NRF
// A0     CE NRF
// A1     CSN NRF
// A2     DRIVER IN1
// A3     DRIVER IN2
// A4     DRIVER IN3
// A5     DRIVER IN4
// A6       
// A7

#include <SPI.h>
#include <RF24.h>
#include <nRF24l01.h>
#include <Servo.h>


#define driverInput1 A2 
#define driverInput2 A3 
#define driverInput3 A4
#define driverInput4 A5   

//motor kanan
int ENA = 9; //ENA connected to D9

//motor kiri
int ENB = 10; //ENB connected to D10

//ir sensor
int RIGHT = 7; // RIGHT sensor connected to analog pin D7
int LEFT = 8; // LEFT sensor connected to analog pin D8

//opto
RF24 radio (14, 15);
const byte address [6] = "00001";
int readData [5];
byte sensorDataValue [10];

//stepcounter
int stepCounter = 0;

//servo
Servo myservo;
int pos = 0;
int servogripper  = 6;

void setup() {
  
    Serial.begin (9600);

    //nrf
    radio.begin ();
    radio.openReadingPipe (0, address);
    radio.setPALevel (RF24_PA_MIN);
    radio.startListening ();

    //motor driver
    pinMode(ENA, OUTPUT); // initialize ENA pin as an output
    pinMode(ENB, OUTPUT); // initialize ENB pin as an output
    pinMode(driverInput1, OUTPUT); 
    pinMode(driverInput2, OUTPUT); 
    pinMode(driverInput3, OUTPUT); 
    pinMode(driverInput4, OUTPUT); 

    //ir sensor
    pinMode(RIGHT, INPUT); // initialize RIGHT pin as an input
    pinMode(LEFT, INPUT); // initialize ENA pin as an input

    //servo
    myservo.attach(6);

}

void loop() {
  //nrf
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

    //ir sensor
    int rightIRReading, leftIRReading;
    rightIRReading = digitalRead (RIGHT);
    leftIRReading = digitalRead (LEFT);

//kondisi logam
if (sensorDataValue [7] == 0 && stepCounter == 0)
  {   
  stepCounter = 1;
  }  
  if (stepCounter == 1)
  {
    if (rightIRReading == 0 && leftIRReading == 0) //compare the both sensor to decide the direction
   {
    //MAJU//
    analogWrite(ENA, 150); // set right motors speed
    analogWrite(ENB, 150); // set left motors speed

    //motor kanan CW
    digitalWrite(driverInput1, LOW);
    digitalWrite(driverInput2, HIGH);
    //motor kiri CW
    digitalWrite(driverInput3, HIGH);
    digitalWrite(driverInput4, LOW);
    }
  }
   stepCounter = 1;
    {
      if (rightIRReading == 1 && leftIRReading == 1) 
     { 
     //BERHENTI
     analogWrite(ENA, 0); //set right motors speed
     analogWrite(ENB, 0); //set left motors speed
    
     digitalWrite(driverInput1, LOW);
     digitalWrite(driverInput2, LOW);
     digitalWrite(driverInput3, LOW);
     digitalWrite(driverInput4, LOW);

     stepCounter = 2;
     }
    }

    if (stepCounter == 2)
    {
      //SERVO AMBIL
      for (pos = 180; pos >= 0; pos -= 10)
      {
        myservo.write(pos);
        delay(15);

        stepCounter = 3;
      }
    }

    if (stepCounter == 3)
     {
      //BELOK KIRI
     analogWrite(ENA, 125); //set right motors speed
     analogWrite(ENB, 0); //set left motors speed

     //motor kanan CW
     digitalWrite(driverInput1, HIGH);
     digitalWrite(driverInput2, LOW);
     //motor kiri stop
     digitalWrite(driverInput3, LOW);
     digitalWrite(driverInput4, LOW);
     delay (1000);

     stepCounter = 4;
     }

    if (stepCounter == 4)
     {
      if (rightIRReading == 0 && leftIRReading == 0)
      {
      //MAJU//
      analogWrite(ENA, 150); // set right motors speed
      analogWrite(ENB, 150); // set left motors speed
  
      //motor kanan CW
      digitalWrite(driverInput1, LOW);
      digitalWrite(driverInput2, HIGH);
      //motor kiri CW
      digitalWrite(driverInput3, HIGH);
      digitalWrite(driverInput4, LOW);

      stepCounter = 5;
      }
     }

    if (stepCounter == 5)
     {
      if (rightIRReading == 1 && leftIRReading == 1) 
      { 
     //BERHENTI
     analogWrite(ENA, 0); //set right motors speed
     analogWrite(ENB, 0); //set left motors speed
    
     digitalWrite(driverInput1, LOW);
     digitalWrite(driverInput2, LOW);
     digitalWrite(driverInput3, LOW);
     digitalWrite(driverInput4, LOW);

     stepCounter = 6;
      }
     }

    if (stepCounter == 6)
     {
      //SERVO NARO
      for (pos = 180; pos <= 0; pos += 10)
       {
        myservo.write(pos);
        delay(15);

        stepCounter = 7;
       }
     }

    if (stepCounter == 7)
     {
       //BELOK KIRI
       analogWrite(ENA, 125); //set right motors speed
       analogWrite(ENB, 0); //set left motors speed
  
       //motor kanan CW
       digitalWrite(driverInput1, HIGH);
       digitalWrite(driverInput2, LOW);
       //motor kiri stop
       digitalWrite(driverInput3, HIGH);
       digitalWrite(driverInput4, LOW);
       delay (1000);
  
       stepCounter = 8;
     }

    if (stepCounter == 8)
     {
      if (rightIRReading == 0 && leftIRReading == 0) //compare the both sensor to decide the direction
      {
      //MAJU//
      analogWrite(ENA, 150); // set right motors speed
      analogWrite(ENB, 150); // set left motors speed
  
      //motor kanan CW
      digitalWrite(driverInput1, LOW);
      digitalWrite(driverInput2, HIGH);
      //motor kiri CW
      digitalWrite(driverInput3, HIGH);
      digitalWrite(driverInput4, LOW);

      stepCounter = 9;
      }
     }

    if (stepCounter == 9)
     {
      if (rightIRReading == 1 && leftIRReading == 1) 
      { 
     //BERHENTI
     analogWrite(ENA, 0); //set right motors speed
     analogWrite(ENB, 0); //set left motors speed
    
     digitalWrite(driverInput1, LOW);
     digitalWrite(driverInput2, LOW);
     digitalWrite(driverInput3, LOW);
     digitalWrite(driverInput4, LOW);
      }
     }
     
//kondisi plastik
/*if (IPValue == 0 && stepCounter == 0)
{   
  stepCounter = 2;
  }
  if (stepCounter == 2)
  {
    if (rightIRReading == 0 && leftIRReading == 0) //compare the both sensor to decide the direction
   {
    //MAJU//
    analogWrite(ENA, 125); // set right motors speed
    analogWrite(ENB, 125); // set left motors speed
    
    digitalWrite(driverInput1, LOW);
    digitalWrite(driverInput2, HIGH);
    digitalWrite(driverInput3, HIGH);
    digitalWrite(driverInput4, LOW);
    }
    else if (rightIRReading == 1 && leftIRReading == 0 ) //compare the both sensor to decide the direction
    {
    //MAJU KANAN
    analogWrite(ENA, 125); //set right motors speed
    analogWrite(ENB, 125); //set left motors speed
    
    digitalWrite(driverInput1, LOW);
    digitalWrite(driverInput2, HIGH);
    digitalWrite(driverInput3, LOW);
    digitalWrite(driverInput4, HIGH);
    }
    else if (rightIRReading == 0 && leftIRReading == 1 ) //compare the both sensor to decide the direction
    { 
     //MAJU KIRI
     analogWrite(ENA, 125); //set right motors speed
     analogWrite(ENB, 125); //set left motors speed
    
     digitalWrite(driverInput1, HIGH);
     digitalWrite(driverInput2, LOW);
     digitalWrite(driverInput3, HIGH);
     digitalWrite(driverInput4, LOW); 
    }
    
    else if (rightIRReading == 1 && leftIRReading == 1) //compare the both sensor to decide the direction
    { 
     //BERHENTI
     analogWrite(ENA, 0); //set right motors speed
     analogWrite(ENB, 0); //set left motors speed
    
     digitalWrite(driverInput1, LOW);
     digitalWrite(driverInput2, LOW);
     digitalWrite(driverInput3, LOW);
     digitalWrite(driverInput4, LOW);
     }
   }
   */
} 

 
