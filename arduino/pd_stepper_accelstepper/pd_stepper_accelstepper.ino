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
AccelStepper stepper(AccelStepper::DRIVER, STEP_X, DIR_X);

int pot;
int periodMin = 50;
int periodMax = 10000;
int period = periodMax;

int dir = 1;

boolean spinning = false;

String inString = "";


void setup() {
  Serial.begin(115200);

  /*
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, LOW);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, LOW);
  pinMode(stepPin, OUTPUT);
  digitalWrite(stepPin, LOW);
  */
  stepper.setEnablePin(ENABLE);

  Serial.println("ready");

  stepper.enableOutputs();

}


void loop() {
  
  if(spinning) {
    stepper.setSpeed(1/period);
    stepper.move(1000 * dir);
    stepper.run();
  } else {
    stepper.stop();
  }


  while(Serial.available() > 0) {
    char inChar = Serial.read();
    if(inChar == 'b') {
      parseVars();
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
  String inDir = inString.substring(1, i);
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
