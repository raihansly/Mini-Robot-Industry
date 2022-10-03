#include<SoftwareSerial.h>
#include<Servo.h>
#define M11 6
#define M12 5
#define M21 11
#define M22 10
char bdata = '0';
SoftwareSerial blue(12, 13);
Servo myservo;
Servo myservo1;
int x = 45;
int y = 120;

void setup() {
  Serial.begin(9600);
  blue.begin(9600);
  myservo.attach(3);
  myservo1.attach(4);
  myservo1.write(y);
  myservo.write(x);

  pinMode(M11, OUTPUT);
  pinMode(M12, OUTPUT);
  pinMode(M21, OUTPUT);
  pinMode(M22, OUTPUT);
}

void loop() {
  Serial.print("bdata = ");
  Serial.println(bdata);
  if (blue.available()) {
    bdata = blue.read();
    if (bdata == '3') {
      digitalWrite(M11, HIGH);
      digitalWrite(M12, LOW);
      digitalWrite(M21, HIGH);
      digitalWrite(M22, LOW);
    }
    else if (bdata == '1') {
      digitalWrite(M11, LOW);
      digitalWrite(M12, HIGH);
      digitalWrite(M21, LOW);
      digitalWrite(M22, HIGH);
    }
    else if (bdata == '4') {
      digitalWrite(M11, LOW);
      digitalWrite(M12, HIGH);
      digitalWrite(M21, HIGH);
      digitalWrite(M22, LOW);
    }
    else if (bdata == '2') {
      digitalWrite(M11, HIGH);
      digitalWrite(M12, LOW);
      digitalWrite(M21, LOW);
      digitalWrite(M22, HIGH);
    }
    else if (bdata == '0') {
      digitalWrite(M11, LOW);
      digitalWrite(M12, LOW);
      digitalWrite(M21, LOW);
      digitalWrite(M22, LOW);
    }
    else if (bdata == '5') {
      servoAtas();
    }
    else if (bdata == '7') {
      servoBawah();
    }
    else if (bdata == '6') {
      servoBuka();
    }
    else if (bdata == '8') {
      servoTutup();
    }
    else if (bdata == 'S') {
      digitalWrite(M11, LOW);
      digitalWrite(M12, HIGH);
      digitalWrite(M21, LOW);
      digitalWrite(M22, HIGH);
      delay(200);

      digitalWrite(M11, HIGH);
      digitalWrite(M12, LOW);
      digitalWrite(M21, LOW);
      digitalWrite(M22, HIGH);
      delay(355);

      digitalWrite(M11, LOW);
      digitalWrite(M12, HIGH);
      digitalWrite(M21, LOW);
      digitalWrite(M22, HIGH);
      delay(100);
    }
  }
}

void servoAtas() {
  if (x == 180) {
    x = x;
  } else {
    x = x + 30;
  }
  myservo.write(x);
  delay(1000);
}

void servoBawah() {
  if (x == 0) {
    x = x;
  } else {
    x = x - 30;
  }
  myservo.write(x);
  delay(1000);
}

void servoBuka() {
  if (y == 180) {
    y = y;
  } else {
    y = y + 30;
  }
  myservo1.write(y);
  delay(1000);
}

void servoTutup() {
  if (y == 0) {
    y = y;
  } else {
    y = y - 30;
  }
  myservo1.write(y);
  delay(1000);
}
