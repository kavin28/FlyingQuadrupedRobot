/*
* Project Name:   Flying_Quadruped_Robot
* Author List:    K.Govintharaj, A.Heeraj, G.Kavinraja, A.T Anand
* Filename:       Flying_Quadpod_Code
* Functions:      stand(),forward(),rotate(),Dronepos()
* Global Variables: chA, chB. ch1 & ch2 holds the values of ch1 & ch2
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h> // Xcluma Servo Driver for Power  Distribution
/* chA - Channel 5 of the receiver is connected to Arduino for choosing the movement of the quadpod.
 *       Functions called:
 *                 1)Stand 2)Forward 3)Rotate (3-State toggle switch)
 * chB - Channel 6 of the receiver is connected to Arduino for making the positions for take off.
 *                 1)Dronepos Function is called.
           
*/                                                                                                  
const int chA = 32; 
const int chB = 34;
/*
 * Function Descriptions:
 *      stand()   : Used for making the quadpod to stand upright making all the servos at their initial states
 *      forward() : Used for making the quadpod to move forward direction
 *      rotate()  : Used for making the quadpod to rotate, for changing direction (left or right)
 *      dronepos(): Used for making the quadpod to rest all legs on ground, for take off
 * */
void stand(); 
void forward();
void rotate();
void dronepos();
void RF(int, int);
void RB(int, int);
void LF(int, int);
void LB(int, int);
void RRF(int, int);
void RRB(int, int);
void RLF(int, int);
void RLB(int, int);
int angleToPulse(int);
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
// Watch video V1 to understand the two lines below: http://youtu.be/y8X9X10Tn1k
#define SERVOMIN  100 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  650 // this is the 'maximum' pulse length count (out of 4096)
int ch1,ch2;
uint8_t servonum = 0;

void setup()
{
  /*
   * Serial 0 of Arduino Mega for communication with Xcluma-Servo Controller
   * Serial 1 of Arduino Mega for communication with RF Transmitter (FlySky-i6)
  */
     
  //Below are some Servo Controller inbuilt functions66
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);
  pinMode(chA, INPUT);
  pinMode(chB, INPUT);
}

/*
  Some Common descriptions to be noted for better understanding:
      pwm.setPWM(pin_number_as_per_xclumaServoDriver, Always 0, angleToPulse(angle_for_servos_to_change))
*/
void loop()
{
  /*Monitoring the Signals from RF Receiver and calling the respective functions (Movements) as described earlier
    PWM values obtained from the receiver for various positions are as follows:
    Channel 1 : Low - 1970 ; Mid - 1484 ; High - 988 (3-State Toggle Switch)
    Channel 2 : Low - 1970 ; High - 988 (2-State Toggle Switch)
  */
  /*digitalWrite(4,HIGH);
  ch1 = pulseIn(chA,HIGH);
  ch2 = pulseIn(chB,HIGH);
  Serial.print("Ch1:");
  Serial.print(ch1);
  Serial.print("Ch2:");
  Serial.print(ch2);
  if (ch1 >= 1970)
  {
    digitalWrite(LED_BUILTIN,HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN,LOW);
    stand();
  }
  else if (ch1 > 1440 && ch1<=1500)
  {
    forward();
    
  }
  else if (ch1 >= 960 && ch1<=1000)
  {
    rotate();
  }
  else if (ch2 >= 970 && ch2<=1000 && ch1 >=1900)
  {
    dronepos();
  }
  else
  {
    stand();
  }*/
  stand();
  delay(1000);
  while(1)
  {
RF(140, 100);
    delay(50);
    LF(60, 100);
   delay(50);
    RB(100, 60);
    delay(50);
    LB(70, 130);
    delay(50);
}
}

int angleToPulse(int ang)
{
  //Inbuilt Xcluma Servo controller library function for mapping the pwm values
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX); // map angle of 0 to 180 to Servo min and Servo max
  return pulse;
}

void stand()
{
  //Logic used for making the stand position of the quadpod
  pwm.setPWM(0, 0, angleToPulse(90) );
  delay(50);
  pwm.setPWM(1, 0, angleToPulse(90) );
  delay(50);
  pwm.setPWM(2, 0, angleToPulse(90) );
  delay(50);
  pwm.setPWM(3, 0, angleToPulse(90) );
  delay(50);
  pwm.setPWM(4, 0, angleToPulse(90) );
  delay(50);
  pwm.setPWM(5, 0, angleToPulse(90) );
  delay(50);
  pwm.setPWM(6, 0, angleToPulse(90) );
  delay(50);
  pwm.setPWM(7, 0, angleToPulse(90) );
  delay(50);
  return;
}

void dronepos()
{ 
  //Logic used for making the Dronetake off position of the quadpod
  pwm.setPWM(0, 0, angleToPulse(30) );
  delay(50);
  pwm.setPWM(1, 0, angleToPulse(150) );
  delay(50);
  pwm.setPWM(2, 0, angleToPulse(30) );
  delay(50);
  pwm.setPWM(3, 0, angleToPulse(150) );
  delay(50);
  pwm.setPWM(4, 0, angleToPulse(43) );
  delay(50);
  pwm.setPWM(5, 0, angleToPulse(130) );
  delay(50);
  pwm.setPWM(6, 0, angleToPulse(55) );
  delay(50);
  pwm.setPWM(7, 0, angleToPulse(130) );
  delay(50);
}
/*
void rotate()
{ 
  //Logic used for making the quadpod to Rotate
  RRF(140, 100);
  delay(50);
  RLB(70, 130);
  delay(50);
  RRB(100, 80);
  delay(50);
  RLF(60, 100);
  delay(50);
}
void forward()
{
  //Logic used for making the quadpod to move in the forward direction
for (int RFpos = 140; RFpos >= 100; RFpos -= 20)
  { pwm.setPWM(0, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(90) );
    pwm.setPWM(1, 0, angleToPulse(110) );
    pwm.setPWM(5, 0, angleToPulse(RFpos) );
  }
  pwm.setPWM(1, 0, angleToPulse(90) );
  delay(50);

 for (int LFpos = 60; LFpos <= 100; LFpos += 20)
  { pwm.setPWM(1, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(90) );

    pwm.setPWM(0, 0, angleToPulse(70) );
    pwm.setPWM(4, 0, angleToPulse(LFpos) );
  }
  pwm.setPWM(0, 0, angleToPulse(90) );
delay(50);
for (int RBpos = 100; RBpos >= 60; RBpos -= 20)
  {
    pwm.setPWM(0, 0, angleToPulse(90) );
    pwm.setPWM(1, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(70) );
    pwm.setPWM(6, 0, angleToPulse(RBpos) );
  }
  pwm.setPWM(2, 0, angleToPulse(90) );
 delay(50);
  for (int LBpos = 70; LBpos <= 130; LBpos += 20)
  {
    pwm.setPWM(0, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(90) );
    pwm.setPWM(1, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(110) );
    pwm.setPWM(7, 0, angleToPulse(LBpos) );
  }
  pwm.setPWM(3, 0, angleToPulse(90) );
  delay(50);
  return;
}

void RRF(int rrf, int rrfr)
{
  for (int RRFpos = rrf; RRFpos >= rrfr; RRFpos -= 20)
  { pwm.setPWM(0, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(90) );
    pwm.setPWM(1, 0, angleToPulse(100) );
    pwm.setPWM(5, 0, angleToPulse(RRFpos) );
  }
  pwm.setPWM(1, 0, angleToPulse(90) );
}

//Rotating Right Back Leg
void RRB(int rrb, int rrbr) 
{
  for (int RRBpos = rrb; RRBpos >= rrbr; RRBpos -= 20)
  {
    pwm.setPWM(0, 0, angleToPulse(90) );
    pwm.setPWM(1, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(80) );
    pwm.setPWM(6, 0, angleToPulse(RRBpos) );
  }
  pwm.setPWM(2, 0, angleToPulse(90) );
}

//Rotating Left Front Leg
void RLF(int rlf, int rlfr)
{
  for (int RLFpos = rlf; RLFpos <= rlfr; RLFpos += 20)
  { pwm.setPWM(1, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(90) );
    pwm.setPWM(0, 0, angleToPulse(80) );
    pwm.setPWM(4, 0, angleToPulse(RLFpos) );
  }
  pwm.setPWM(0, 0, angleToPulse(90) );
}

//Rotating Left Back Leg
void RLB(int rlb, int rlbr) 
{
  for (int RLBpos = rlb; RLBpos <= rlbr; RLBpos += 20)
  {
    pwm.setPWM(0, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(90) );
    pwm.setPWM(1, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(100) );
    pwm.setPWM(7, 0, angleToPulse(RLBpos) );
  }
  pwm.setPWM(3, 0, angleToPulse(90) );
}*/
void RF(int rf, int rfr) //RightFront
{
  for (int RFpos = rf; RFpos >= rfr; RFpos -= 20)
  { pwm.setPWM(0, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(90) );

    pwm.setPWM(1, 0, angleToPulse(110) );
    pwm.setPWM(5, 0, angleToPulse(RFpos) );
  }
  pwm.setPWM(1, 0, angleToPulse(90) );
}
void RB(int rb, int rbr) //RightBack
{
  for (int RBpos = rb; RBpos >= rbr; RBpos -= 20)
  {
    pwm.setPWM(0, 0, angleToPulse(90) );
    pwm.setPWM(1, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(70) );
    pwm.setPWM(6, 0, angleToPulse(RBpos) );
  }
  pwm.setPWM(2, 0, angleToPulse(90) );
}
void LF(int lf, int lfr) //LeftFront
{
  for (int LFpos = lf; LFpos <= lfr; LFpos += 20)
  { pwm.setPWM(1, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(90) );

    pwm.setPWM(0, 0, angleToPulse(70) );
    pwm.setPWM(4, 0, angleToPulse(LFpos) );
  }
  pwm.setPWM(0, 0, angleToPulse(90) );
}
void LB(int lb, int lbr) //LeftBack
{
  for (int LBpos = lb; LBpos <= lbr; LBpos += 20)
  {
    pwm.setPWM(0, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(90) );
    pwm.setPWM(1, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(115) );
    pwm.setPWM(7, 0, angleToPulse(LBpos) );
  }
  pwm.setPWM(3, 0, angleToPulse(90) );
}




