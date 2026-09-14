#include <ESP32Servo.h>

#define LEFT_SENSOR     26
#define CENTER_SENSOR   14
#define RIGHT_SENSOR    27
#define LEFT_WIDE       13
#define RIGHT_WIDE      35

#define IN1 5
#define IN2 18
#define IN3 19
#define IN4 21

#define ENA 2
#define ENB 4

#define TRIG 33
#define ECHO 32

#define S0 23
#define S1 17
#define S2 15
#define S3 22
#define OUT 34

#define ARM_PIN 16
#define GRIPPER_PIN 25

#define STOP 98

// Arm movement
#define ARM_FORWARD 70
#define ARM_BACKWARD 180

// Gripper movement
#define GRIP_CLOSE 30
#define GRIP_OPEN 115 

Servo armServo;
Servo gripperServo;

int redValue = 0;
int greenValue = 0;

long duration;
float distance;

int baseSpeed = 90;

// PID tuning
float Kp = 32;
float Ki = 0;
float Kd = 14;

float error = 0;
float previousError = 0;
float integral = 0;
float derivative = 0;

int lastAction = 0;

void setup()
{
  Serial.begin(115200);

  pinMode(LEFT_SENSOR, INPUT);
  pinMode(CENTER_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);

  pinMode(LEFT_WIDE, INPUT);
  pinMode(RIGHT_WIDE, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  //FIXED ULTRASONIC
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  //color sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);


  armServo.setPeriodHertz(50);
  gripperServo.setPeriodHertz(50);

  armServo.attach(ARM_PIN, 500, 2400);
  gripperServo.attach(GRIPPER_PIN, 500, 2400);
}

void dropObject() {

  // 1. Move arm forward (lower object to ground)
  Serial.println("Arm forward (lowering)");
  armServo.write(ARM_FORWARD);
  delay(1500);

  // 2. Stop arm
  armServo.write(STOP);
  delay(100);

  // 3. Open gripper (release object)
  Serial.println("Gripper open");
  gripperServo.write(GRIP_OPEN);
  delay(1000);

  // 4. Stop gripper
  gripperServo.write(STOP);
  delay(100);

  // 5. Move arm back (return to original position)
  Serial.println("Arm backward (return)");
  armServo.write(ARM_BACKWARD);
  delay(1500);

  // 6. Final stop
  armServo.write(STOP);
}

void pickObject() {

  moveMotorsBack(100,100);
  delay(700);

  stopRobot();

  // Move arm to object
  Serial.println("Arm forward");
  armServo.write(ARM_FORWARD);
  delay(1500);

  // Stop arm
  armServo.write(STOP);
  delay(100);

  // Close gripper
  Serial.println("Gripper close");
  gripperServo.write(GRIP_CLOSE);
  delay(1000);

  // Stop gripper
  gripperServo.write(STOP);
  delay(100);

  // Move arm back
  Serial.println("Arm backward");
  armServo.write(ARM_BACKWARD);
  delay(1500);

  //  Stop arm (object held)
  armServo.write(STOP);
}




int readColor(bool s2, bool s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);
  delay(50);

  return pulseIn(OUT, LOW);
}

String getColor() {

  int red = readColor(LOW, LOW);
  int green = readColor(HIGH, HIGH);

  if (red < 90 && green > 90) {
    return "RED";
  } 
  else if (green < 120 && red > 80) {
    return "GREEN";
  } 
  else {
    return "UNKNOWN";
  }
}

//FIXED DISTANCE FUNCTION
float getDistance()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(3);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);

  if(duration <= 0) return -1;

  float dist = duration * 0.0343 / 2;

  if(dist <= 0 || dist > 400) return -1;

  return dist;
}

void moveMotorsBack(int leftSpeed, int rightSpeed)
{
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void moveMotors(int leftSpeed, int rightSpeed)
{
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);

  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void stopRobot()
{
  analogWrite(ENA,0);
  analogWrite(ENB,0);

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void moveForwardShort()
{
  analogWrite(ENA, 90);
  analogWrite(ENB, 90);

  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void avoidObstacle()
{
  // Step 1: Move back
  moveMotorsBack(100, 100);
  delay(400);

  // Step 2: Turn right until all sensors = 1
  unsigned long startTime = millis();

  while(true)
  {
    int L  = digitalRead(LEFT_SENSOR);
    int C  = digitalRead(CENTER_SENSOR);
    int R  = digitalRead(RIGHT_SENSOR);
    int LW = digitalRead(LEFT_WIDE);
    int RW = digitalRead(RIGHT_WIDE);

    if(L==1 && C==1 && R==1 && LW==1 && RW==1)
      break;

    moveMotors(100, 0);
  }

  unsigned long turnTime = millis() - startTime;

  // Step 3: Move forward slightly
  moveMotors(100, 100);
  delay(500);

  // Step 4: Turn left using measured time
  moveMotors(0, 100);
  delay(turnTime * 2.1);   // ← your idea, now actually valid

  // Step 5: Move forward until line found
  while(true)
  {
    if(digitalRead(CENTER_SENSOR) == 0)
      break;

    moveMotors(110, 110);
  }

  // Reset PID
  integral = 0;
  previousError = 0;
}

void smartTurnLeft()
{
  while(true)
  {
    moveForwardShort();

    int L = digitalRead(LEFT_SENSOR);
    int C = digitalRead(CENTER_SENSOR);
    int R = digitalRead(RIGHT_SENSOR);

    if(L==1 && C==1 && R==1)
      break;
  }

  delay(20);

  analogWrite(ENA,60);
  analogWrite(ENB,105);

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  while(true)
  {
    if(digitalRead(CENTER_SENSOR) == 0)
    {
      delay(10);
      if(digitalRead(CENTER_SENSOR) == 0)
        break;
    }
  }
}

void smartTurnRight()
{
  while(true)
  {
    moveForwardShort();

    int L = digitalRead(LEFT_SENSOR);
    int C = digitalRead(CENTER_SENSOR);
    int R = digitalRead(RIGHT_SENSOR);

    if(L==1 && C==1 && R==1)
      break;
  }

  delay(20);

  analogWrite(ENA,90);
  analogWrite(ENB,60);

  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  while(true)
  {
    if(digitalRead(CENTER_SENSOR) == 0)
    {
      delay(10);
      if(digitalRead(CENTER_SENSOR) == 0)
        break;
    }
  }
}

void loop()
{
  float d = getDistance();

  Serial.print("Distance: ");
  Serial.println(d);

  //obstacle detect
  if(d > 0 && d <= 2.5)
  {
    Serial.print("color detecting");
    String color = getColor();
    if (color=="RED"){
      Serial.print("avoiding");
      avoidObstacle();
      
    }
    else if(color == "GREEN"){
      Serial.print("picking");
      pickObject();
    }
    
    return;
  }

  int L = digitalRead(LEFT_SENSOR);
  int C = digitalRead(CENTER_SENSOR);
  int R = digitalRead(RIGHT_SENSOR);

  int LW = digitalRead(LEFT_WIDE);
  int RW = digitalRead(RIGHT_WIDE);

  if(LW == 0)
  {
    lastAction = -1;
    smartTurnLeft();
    return;
  }

  if(RW == 0)
  {
    lastAction = 1;
    smartTurnRight();
    return;
  }

  if(L==1 && C==1 && R==1)
  {
    if(lastAction == -1)
      smartTurnLeft();
    else if(lastAction == 1)
      smartTurnRight();
    else{

      stopRobot();
    }

    return;
  }

  if(L==0 && C==1 && R==1) error = -1;
  else if(L==0 && C==0 && R==1) error = -0.5;
  else if(L==1 && C==0 && R==1) error = 0;
  else if(L==1 && C==0 && R==0) error = 0.5;
  else if(L==1 && C==1 && R==0) error = 1;

  integral += error;
  derivative = 0.7 * derivative + 0.3 * (error - previousError);

  float correction = Kp * error + Ki * integral + Kd * derivative;
  correction = constrain(correction, -80, 80);

  int turnFactor = abs(correction);
  int dynamicBase = baseSpeed - turnFactor * 0.5;
  dynamicBase = constrain(dynamicBase, 60, baseSpeed);

  int leftMotorSpeed  = dynamicBase + correction;
  int rightMotorSpeed = dynamicBase - correction;

  moveMotors(leftMotorSpeed, rightMotorSpeed);

  previousError = error;
  lastAction = 0;

  delay(5); // small stabilization
}