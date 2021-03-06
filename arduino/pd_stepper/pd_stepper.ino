
// GRBL shield pinouts
#define STEP_X 2
#define STEP_Y 3
#define STEP_Z 4
#define DIR_X 5
#define DIR_Y 6
#define DIR_Z 7
#define ENABLE 8

// Potentiometer connected to SDA pin (A4)
#define POT A4

int stepPin = STEP_Y;
int dirPin = DIR_Y;

int pot;
int periodMin = 50;
int periodMax = 10000;
int period = periodMax;

String inString = "";
int dir = 0;

boolean manualMode = false;
boolean spinning = false;

void setup() {
  Serial.begin(115200);

  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, LOW);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, LOW);
  pinMode(stepPin, OUTPUT);
  digitalWrite(stepPin, LOW);
  
  Serial.println("ready");
  Serial.flush();
}

void loop() {

  if(manualMode) {
    pot = analogRead(POT);
    period = map(pot, 1, 1023, periodMax, periodMin);
  }
  
  if(dir > 0) {
    digitalWrite(dirPin, LOW);
  } else {
    digitalWrite(dirPin, HIGH); 
  }

  if(dir == 0) {
    manualMode = true;
  } else {
    manualMode = false;
  }

  //Serial.print(period);
  //Serial.print(", ");
  //Serial.println(periodMax);

  if(spinning && period > periodMin && period < periodMax) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(period);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(period);
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
  String inDir = inString.substring(0, i);
  String inPeriod = inString.substring(i+1, inString.length());

  dir = inDir.toInt();
  period = inPeriod.toInt();
  
  /*
  Serial.print(dir);
  Serial.print(" ");
  Serial.println(stepDelay);
  */
  inString = "";
    
}
