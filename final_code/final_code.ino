/*
  Project Name:   Flying_Quadruped_Robot
  Author List:    K.Govintharaj, A.Heeraj, G.Kavinraja, A.T Anand
  Filename:       Flying_Quadpod_Code
  Functions:      stand(),forward(),rotate(),Dronepos()
  Global Variables: chA, chB. ch1 & ch2 holds the values of ch1 & ch2
*/
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>// Xcluma Servo Driver for Power  Distribution
/* chA - Channel 5 of the receiver is connected to Arduino for choosing the movement of the quadpod.
         Functions called:
                   1)Stand 2)Forward 3)Rotate (3-State toggle switch)
   chB - Channel 6 of the receiver is connected to Arduino for making the positions for take off.
                   1)Dronepos Function is called.

*/
const int chA = 32;
const int chB = 34;
/*
   Function Descriptions:
        stand()   : Used for making the quadpod to stand upright making all the servos at their initial states
        forward() : Used for making the quadpod to move forward direction
        rotate()  : Used for making the quadpod to rotate, for changing direction (left or right)
        dronepos(): Used for making the quadpod to rest all legs on ground, for take off
 * */
int ch1, ch2;
void stand();
void RF(int, int);
void RB(int, int);
void LF(int, int);
void LB(int, int);
void RRF(int, int);
void RRB(int, int);
void RLF(int, int);
void RLB(int, int);
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  100 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  650 // this is the 'maximum' pulse length count (out of 4096)
int a = 1;
uint8_t servonum = 0;

void setup() {
  /*
    Serial 0 of Arduino Mega for communication with Xcluma-Servo Controller
    Serial 1 of Arduino Mega for communication with RF Transmitter (FlySky-i6)
  */
  //Below are some Servo Controller inbuilt functions
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
  ch1 = pulseIn(chA, HIGH);
  ch2 = pulseIn(chB, HIGH);
  if (ch1 >= 1970)    //Logic for standing position of quadpod
  {
    stand();
  }
  else if (ch1 > 1440 && ch1 <= 1500)  //Logic for forward motion of quadpod
  {
    RF(140, 100);
    delay(5);
    LF(60, 100);
    delay(5);
    RB(100, 60);
    delay(5);
    LB(80, 120);
    delay(5);
  }
  else if (ch1 >= 960 && ch1 <= 1000) //Logic for Rotation of quadpod
  {

    RRF(140, 100);
    delay(50);
    RLB(70, 130);
    delay(50);
    RRB(100, 80);
    delay(50);
    RLF(60, 100);
    delay(50);
  }
  else if (ch2 >= 970 && ch2 <= 1000 && ch1 >= 1900)  //Logic for Drone Take Off position
  {
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
  else
  {
    stand();
  }
}
int angleToPulse(int ang) {
  //Inbuilt Xcluma Servo controller library function for mapping the pwm values
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX); // map angle of 0 to 180 to Servo min and Servo max
  Serial.print("Angle: "); Serial.print(ang);
  Serial.print(" pulse: "); Serial.println(pulse);
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

}
void RF(int rf, int rfr) //RightFront
{
  for (int RFpos = rf; RFpos >= rfr; RFpos -= 20)
  { pwm.setPWM(0, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(90) );

    pwm.setPWM(1, 0, angleToPulse(110) );
    pwm.setPWM(5, 0, angleToPulse(RFpos) );
  }
  pwm.setPWM(5, 0, angleToPulse(90) );
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
  pwm.setPWM(6, 0, angleToPulse(90) );
  pwm.setPWM(2, 0, angleToPulse(95) );
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
  pwm.setPWM(4, 0, angleToPulse(90) );
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
  pwm.setPWM(7, 0, angleToPulse(90) );
  pwm.setPWM(3, 0, angleToPulse(80) );
}

void RRF(int rf, int rfr) //Rotating RightFront leg
{
  for (int RFpos = rf; RFpos >= rfr; RFpos -= 20)
  { 
    pwm.setPWM(0, 0, angleToPulse(90));
    pwm.setPWM(2, 0, angleToPulse(90));
    pwm.setPWM(3, 0, angleToPulse(90));
    pwm.setPWM(1, 0, angleToPulse(100));
    pwm.setPWM(5, 0, angleToPulse(RFpos));
  }
  pwm.setPWM(1, 0, angleToPulse(90) );
}
void RRB(int rb, int rbr)//Rotating Right Back Leg
{
  for (int RBpos = rb; RBpos >= rbr; RBpos -= 20)
  {
    //RRBpos holds the raw data (Angle)
    pwm.setPWM(0, 0, angleToPulse(90) );
    pwm.setPWM(1, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(80) );
    pwm.setPWM(6, 0, angleToPulse(RBpos) );
  }
  pwm.setPWM(2, 0, angleToPulse(90) );
}
void RLF(int lf, int lfr) //Rotating Left Front Leg
{
  for (int LFpos = lf; LFpos <= lfr; LFpos += 20)
  { 
    //LFpos holds the raw data (Angle)
    pwm.setPWM(1, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(90) );

    pwm.setPWM(0, 0, angleToPulse(80) );
    pwm.setPWM(4, 0, angleToPulse(LFpos) );
  }
  pwm.setPWM(0, 0, angleToPulse(90) );
}
void RLB(int lb, int lbr) //Rotating LeftBack leg
{
  //LBpos holds the raw data (Angle)
  for (int LBpos = lb; LBpos <= lbr; LBpos += 20)
  {
    pwm.setPWM(0, 0, angleToPulse(90) );
    pwm.setPWM(2, 0, angleToPulse(90) );
    pwm.setPWM(1, 0, angleToPulse(90) );
    pwm.setPWM(3, 0, angleToPulse(100) );
    pwm.setPWM(7, 0, angleToPulse(LBpos) );
  }
  pwm.setPWM(3, 0, angleToPulse(90) );
}
