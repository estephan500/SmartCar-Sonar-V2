// this will try the sonar, but with extensive "looking around."

#include <Smartcar.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

const int TRIGGER_PIN = 8;
const int ECHO_PIN = 7; 
const unsigned int MAX_DISTANCE = 500;
SR04 front(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

const int IN_A0 = A5; // analog input
const int IN_D0 = 9; // digital input
const int IN_A02 = A4; // analog input
const int IN_D02 = 3; // digital input
int vA0;
bool vD0;
int vA02;
bool vD02;

int leftMotorForwardPin = 11;
int leftMotorBackwardPin = 10; //
int leftMotorSpeedPin = 5; //
int rightMotorForwardPin = 13;
int rightMotorBackwardPin = 12;
int rightMotorSpeedPin = 6;
int speakerpin = 2;

int normalspeed = 75;
int normalturn=90;
int miniwait=0;
int swerveduration=650;

BrushedMotor leftMotor(leftMotorForwardPin,leftMotorBackwardPin, leftMotorSpeedPin);
BrushedMotor rightMotor(rightMotorForwardPin, rightMotorBackwardPin, rightMotorSpeedPin);
DifferentialControl control(leftMotor, rightMotor);
SimpleCar car(control);

void swerveleft() {
  Serial.println("Swerveleft  ");
  car.setAngle(-normalturn);  
  car.setSpeed(normalspeed);
  delay(swerveduration);
  car.setAngle(0);  
}

void rotleft() {
  car.overrideMotorSpeed(-100, 100);
  delay(swerveduration/2); 
  car.setSpeed(normalspeed);
}

void swerveright() {
  Serial.println("Swerveright  ");
  car.setAngle(normalturn);  
  car.setSpeed(normalspeed);
  delay(swerveduration);
  car.setAngle(0); 
}

void rotright() {
  car.overrideMotorSpeed(100, -100);
  delay(swerveduration/2); 
  car.setSpeed(normalspeed);
}

void spin180() {
  Serial.println("Back Spinnnnnn  ");
  // car.setSpeed(-normalspeed);
  // delay(500);
  car.overrideMotorSpeed(100, -100);
  delay(swerveduration); 
  car.setSpeed(normalspeed);
}

void buzz() {
  Serial.println("Buzz  ");
  car.setSpeed(0);
  delay(100);
  car.setSpeed(100);
  delay(100);
  car.setSpeed(0);
  delay(100);
  car.setSpeed(100);
  delay(100);
  car.setSpeed(0);
  delay(100);
  car.setSpeed(normalspeed);
}

void lookat(int lookangle) {
  myservo.write(lookangle);
}

bool seewall(int angle) {  //*********************
  Serial.print("Seewall  ");
  Serial.print(angle);
  lookat(angle);
  delay(300);
  int dist = front.getDistance();
  //tone(speakerpin, 131, 80); // low tone "looked..."
  if (dist >0 and dist < 25) {
    Serial.println("  true");
    //tone(speakerpin, 262, 80); // high tone "true!"
    lookat(90);
    return(true);
    
  }
  else {
    Serial.println("  false");
    lookat(90);
    return(false);
    
  }
}


void check(int checkangle){
  Serial.print("checking ");
  Serial.print(checkangle);
  if (seewall(checkangle)) {
    if(checkangle >= 80 and checkangle <= 100) spin180();
    else if (checkangle <80) rotleft();
    else if (checkangle > 100) rotright();
  }
  delay(miniwait);
}


void setup() {   // *************************

Serial.begin(9600);
Serial.println("START  ");

myservo.attach(4);  // attaches the servo on pin 9 to the servo object

Serial.begin(9600);
car.setSpeed(normalspeed);
car.setAngle(0);

myservo.write(90); 

buzz();
}

void loop() {     // *~~~~~~~~~~~~~~~~~~~~~~~~~~*
  check(90);
  check(40);
  check(90);
  check(140);
}
