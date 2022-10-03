// D2     IR INPUT 1 (LEFT)
// D3     IR INPUT 2 (MIDDLE LEFT)
// D4
// D5     SERVO BASE PWM
// D6     SERVO GRIPPER PWM
// D7     IR INPUT 3 (MIDDLE RIGHT)
// D8     IR INPUT 4 (RIGHT)
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


//nrf
RF24 radio (14, 15);
const byte address [6] = "00001";
int readData [3];
byte sensorDataValue [6];

//StepCounter
byte stepMove, stepStop;

//ir sensor
const byte irLeft   = 2;
const byte irMiddleLeft   = 3;
const byte irMiddleRight   = 7;
const byte irRight   = 8;

int readLeft, readMiddleLeft, readMiddleRight, readRight;



//servo1
Servo myservo1;
int servobawah  = 5;
//servo 2
Servo myservo2;
int pos2 = 0;
int servoAtas  = 6;


//motor kanan
int ENA = 9; //ENA connected to D9
//motor kiri
int ENB = 10; //ENB connected to D10



void setup()
{
  Serial.begin (9600);
  //nrf
  radio.begin ();
  radio.openReadingPipe (0, address);
  radio.setPALevel (RF24_PA_MIN);
  radio.startListening ();

  //stepCounter
  stepMove = 0;
  stepStop = 0;


  //motor driver
  pinMode(ENA, OUTPUT); // initialize ENA pin as an output
  pinMode(ENB, OUTPUT); // initialize ENB pin as an output
  analogWrite(ENA, 100); //set right motors speed
  analogWrite(ENB, 100); //set left motors speed
  pinMode(driverInput1, OUTPUT);
  pinMode(driverInput2, OUTPUT);
  pinMode(driverInput3, OUTPUT);
  pinMode(driverInput4, OUTPUT);

  //ir sensor
  pinMode(irLeft, INPUT); 
  pinMode(irMiddleLeft, INPUT); 
  pinMode(irMiddleRight, INPUT); 
  pinMode(irRight, INPUT); 

    //ir sensor
  readLeft = digitalRead         (irLeft);
  readMiddleLeft = digitalRead   (irMiddleLeft);
  readMiddleRight = digitalRead  (irMiddleRight);
  readRight = digitalRead        (irRight);

  //servo atas
  myservo2.attach(6);
  //servo bawah
  myservo1.attach(5);
  myservo1.write(45);



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

  if (sensorDataValue [1] == 2 && stepMove == 0)
  {
    stepMove = 1;
  }

  if (stepMove = 1);
  {
    move();
    if (sensorDataValue [2] = 0)
    {
      stepStop = 1;
      stepMove = 9;
    }
  }

  if (stepMove = 2)
  {
    move();
    if (sensorDataValue [5] = 0)
    {
      stepStop = 2;
      stepMove = 9;
    }
  }

  if (stepStop = 1)
  {
    stop();
    AtasClose();
    turnAround();
    stepStop = 0;
    stepMove = 2;
  }

  if (stepStop = 2)
  {
    stop();
    AtasOpen();
    turnAround();
    stepStop = 0;
    stepMove = 0;
  }
}

void move()
{
  if (readMiddleRight == 1 && readMiddleLeft == 1)
  {
    forward();
  }
  else if (readMiddleRight == 1 && readMiddleLeft == 0)
  {
    left();
  }
  else if (readMiddleRight == 0 && readMiddleLeft == 1)
  {
    right();
  }
  else if (readMiddleRight == 0 && readMiddleLeft == 0 && readRight == 1 && readLeft == 0)
  {
    left();
  }
  else if (readMiddleRight == 0 && readMiddleLeft == 0 && readRight == 0 && readLeft == 1)
  {
    right();
  }
  else if (readMiddleRight == 0 && readMiddleLeft == 0 && readRight == 0 && readLeft == 0)
  {
    stop();
  }
}

void forward()
{
  digitalWrite(driverInput1, HIGH);
  digitalWrite(driverInput2, LOW);
  digitalWrite(driverInput3, LOW);
  digitalWrite(driverInput4, HIGH);
}
void left()
{
  digitalWrite(driverInput1, LOW);
  digitalWrite(driverInput2, LOW);
  digitalWrite(driverInput3, LOW);
  digitalWrite(driverInput4, HIGH);
}

void right()
{
  digitalWrite(driverInput1, HIGH);
  digitalWrite(driverInput2, LOW);
  digitalWrite(driverInput3, LOW);
  digitalWrite(driverInput4, LOW);
}
void turnAround()
{
  digitalWrite(driverInput1, LOW);
  digitalWrite(driverInput2, LOW);
  digitalWrite(driverInput3, LOW);
  digitalWrite(driverInput4, HIGH);
  delay (2000);
}

void stop()
{
  //Robot Stop

  digitalWrite(driverInput1, LOW);
  digitalWrite(driverInput2, LOW);
  digitalWrite(driverInput3, LOW);
  digitalWrite(driverInput4, LOW);
}


void AtasClose()
{
  //Robot Gripper Closed
  for (pos2 = 180; pos2 <= 0; pos2 -= 10)
  {
    myservo2.write(pos2);
    delay(15);
  }
}

void AtasOpen()
{
  //Robot Gripper Opened
  for (pos2 = 0; pos2 <= 180; pos2 += 10)
  {
    myservo2.write(pos2);
    delay(15);
  }

}
