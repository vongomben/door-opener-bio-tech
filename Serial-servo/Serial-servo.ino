#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32

int pos = 0;  // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
// Possible PWM GPIO pins on the ESP32-S2: 0(used by on-board button),1-17,18(used by on-board LED),19-21,26,33-42
// Possible PWM GPIO pins on the ESP32-S3: 0(used by on-board button),1-21,35-45,47,48(used by on-board LED)
// Possible PWM GPIO pins on the ESP32-C3: 0(used by on-board button),1-7,8(used by on-board LED),9-10,18-21
#if defined(CONFIG_IDF_TARGET_ESP32S2) || defined(CONFIG_IDF_TARGET_ESP32S3)
int servoPin = 17;
#elif defined(CONFIG_IDF_TARGET_ESP32C3)
int servoPin = 7;
#else
int servoPin = 18;
#endif


const int ledPin = 13;  // the pin that the LED is attached to
int incomingByte;       // a variable to read incoming serial data into

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);            // standard 50 hz servo
  myservo.attach(servoPin, 1000, 2000);  // attaches the servo on pin 18 to the servo object
                                         // using default min/max of 1000us and 2000us
                                         // different servos may require different min/max settings
                                         // for an accurate 0 to 180 sweep
}

void loop() {
  // see if there's incoming serial data:
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'S') {
      myservo.write(90);
    }
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'K') {
      myservo.write(100);
    }

    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'L') {
      myservo.write(80);
    }

    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'P') {

      myservo.write(70);
      delay(1000);
      myservo.write(100);
      delay(1500);
      myservo.write(90);
    }

    if (incomingByte == 'O') {  // indietro

      myservo.write(90);  // stop
      myservo.write(180);
      delay(250);
      myservo.write(90);
    }

    if (incomingByte == 'L') {  // avanti

      myservo.write(90);  // stop
      myservo.write(0);
      delay(250);
      myservo.write(90);
    }
    if (incomingByte == 'I') {  // avanti

      myservo.write(90);  // stop
      myservo.write(0);
      delay(200);
      myservo.write(180);
      delay(200);
      myservo.write(90);
    }
  }
}