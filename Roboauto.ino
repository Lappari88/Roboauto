/* Program that enables two dc-motors to drive and stops them when distance measured by ultrasonic sensor is low
*/


const int trig = 11; // Trig on PIN11
const int echo = 12; // Echo on PIN12

const int controlPin1_motor1 = 2; // Control pin 1 for motor 1
const int controlPin2_motor1 = 3; // Control pin 2 for motor 1
const int enablePin_motor1 = 9; // Enable pin for motor 1

const int controlPin1_motor2 = 4; // Control pin 1 for motor 2
const int controlPin2_motor2 = 5; // Control pin 2 for motor 2
const int enablePin_motor2 = 10; // Enable pin for motor 2

const int onOffSwitchStateSwitchPin = 6;  // Switch pin
const int resetSwitchPin = 7; // Alternative reset switch

int onOffSwitchState = 0;
int resetSwitchState = 0;
int previousOnOffSwitchState = 0;
int motorEnabled = 0;
int motorSpeedhigh = 0;
int motorSpeedlow = 0;

void setup() {
  Serial.begin(9600); // Serial begin to display check correct function of ultrasonic sensor
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(resetSwitchPin, INPUT);
  pinMode(controlPin1_motor1, OUTPUT);
  pinMode(controlPin2_motor1, OUTPUT);
  pinMode(enablePin_motor1, OUTPUT);
  pinMode(controlPin1_motor2, OUTPUT);
  pinMode(controlPin2_motor2, OUTPUT);
  pinMode(enablePin_motor2, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(enablePin_motor1, LOW);
  digitalWrite(enablePin_motor2, LOW);
}

void loop() {
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  resetSwitchState = digitalRead(resetSwitchPin);
  delay(10); // Debounce delay
  motorSpeedhigh = 255;
  motorSpeedlow = 180;

  if (resetSwitchState == HIGH) {
    motorEnabled = 0;
  }
  if (onOffSwitchState != previousOnOffSwitchState) {
    if (onOffSwitchState == HIGH) {
      motorEnabled = !motorEnabled;
    }
  }

  digitalWrite(controlPin1_motor1, LOW);
  digitalWrite(controlPin2_motor1, HIGH);
  digitalWrite(controlPin1_motor2, LOW);
  digitalWrite(controlPin2_motor2, HIGH);
  
  long time, distance;
  
  digitalWrite(trig, HIGH); // Trig sending
  delayMicroseconds(255); // Duration of sent trig
  digitalWrite(trig, LOW);
    
  time = pulseIn(echo, HIGH); // Receiving reflected trig
  distance = (time/2) / 28;  // Calculating the distance, in centimeters
  // final distance from sensors to items
  // the variable distance is in cm
      
  Serial.print(distance);  
  Serial.println("cm");

  if (motorEnabled == 1) {
    if (distance > 20) {
      analogWrite(enablePin_motor1, motorSpeedhigh);
      analogWrite(enablePin_motor2, motorSpeedhigh);
    }

    /* Alternative action to slow down before collission
    if (distance > 10) {
    analogWrite(enablePin_motor1, motorSpeedlow);
    analogWrite(enablePin_motor2, motorSpeedlow);
    */
    }
    else if (distance <= 20) {
      analogWrite(enablePin_motor1, 0);
      analogWrite(enablePin_motor2, 0);


      /* Alternative action when distance is low
      unsigned long startTime = millis();
      while (millis() - startTime < 5000) {
      digitalWrite(controlPin1_motor1, LOW);
      digitalWrite(controlPin2_motor1, HIGH);
      digitalWrite(controlPin1_motor2, HIGH);
      digitalWrite(controlPin2_motor2, LOW);
      delay(10); // Just to prevent too rapid toggling
      /*
    }
  }
  
  previousOnOffSwitchState = onOffSwitchState;
}
