#include <AccelStepper.h>

// GRBL shield pinouts
#define STEP_X 2
#define STEP_Y 3
#define STEP_Z 4
#define DIR_X 5
#define DIR_Y 6
#define DIR_Z 7
#define ENABLE 8

//AccelStepper stepper(AccelStepper::DRIVER,STEP,DIR);
AccelStepper stepper(AccelStepper::DRIVER, STEP_Y, DIR_Y);

int pot;
int periodMin = 50;
int periodMax = 10000;
int period = periodMax;

int dir = 1;

boolean spinning = false;

String inString = "";


void setup() {

  Serial.begin(115200);

  //pinMode(STEP_X, OUTPUT);
  //pinMode(STEP_Y, OUTPUT);
  //pinMode(STEP_Z, OUTPUT);
  //pinMode(DIR_X, OUTPUT);
  //pinMode(DIR_Y, OUTPUT);
  //pinMode(DIR_Z, OUTPUT);

  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, LOW);

  stepper.setMaxSpeed(1000000);
  stepper.setAcceleration(10000);

  Serial.println("ready");
}


void loop() {
  
  if(spinning) {
    stepper.move(1000000 * dir);
    stepper.runSpeed();
  } else {
    stepper.stop();
  }


  while(Serial.available() > 0) {
    char inChar = Serial.read();
    
    if(inChar == 'b') {
      parseVars();
      float s = 1000000.0/float(period);
      //stepper.setSpeed(s);
      stepper.setMaxSpeed(s);
      //Serial.println(s,4);
      //stepper.setCurrentPosition(stepper.targetPosition());
      spinning = true;

    } else if(inChar == 'x') {
      spinning = false;
      Serial.println("stop");

    } else {
      inString += inChar;
    }
  }
  
}


void parseVars() {  

  int i = inString.indexOf('d');
  String inDir = inString.substring(0, i);
  String inPeriod = inString.substring(i+1, inString.length());

  dir = inDir.toInt();
  period = inPeriod.toInt();

  /*
  Serial.print(dir);
  Serial.print(" ");
  Serial.println(period);
  */
  inString = "";
}
