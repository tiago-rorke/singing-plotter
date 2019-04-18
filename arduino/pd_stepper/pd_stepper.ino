
// GRBL pinouts
#define STEP_X 2
#define STEP_Y 3
#define STEP_Z 4
#define DIR_X 5
#define DIR_Y 6
#define DIR_Z 7
#define ENABLE 8

int stepPin = STEP_X;
int dirPin = DIR_X;

int pot;
int stepDelayMin = 1;
int stepDelayMax = 10000;
int stepDelay = stepDelayMax;

String inString = "";
int dir = 0;

boolean manualMode = false;
boolean spinning = true;

void setup() {
  Serial.begin(115200);

  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, LOW);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, LOW);
  pinMode(stepPin, OUTPUT);
  digitalWrite(stepPin, LOW);
  
  pinMode(A5, OUTPUT);
  digitalWrite(A5, HIGH);
  
  Serial.println("ready");
  Serial.flush();
}

void loop() {

  if(manualMode) {
    pot = analogRead(A4);
    stepDelay = map(pot, 1, 1023, stepDelayMax, stepDelayMin);
  }
  
  if(dir > 0) {
    digitalWrite(dirPin, LOW);
  } else {
    digitalWrite(dirPin, LOW); 
  }

  if(dir == 0) {
    manualMode = true;
  } else {
    manualMode = false;
  }

  //Serial.print(stepDelay);
  //Serial.print(", ");
  //Serial.println(stepDelayMax);

  if(spinning && stepDelay < stepDelayMax) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }

  while(Serial.available() > 0) {
    char inChar = Serial.read();
    if(inChar == 'b') {
      parseVars();
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
  String inStepDelay = inString.substring(i+1, inString.length());

  dir = inDir.toInt();
  stepDelay = inStepDelay.toInt();
  
  Serial.print(dir);
  Serial.print(" ");
  Serial.println(stepDelay);
  
  inString = "";
    
}
