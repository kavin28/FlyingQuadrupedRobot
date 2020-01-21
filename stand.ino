#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
void stand();
void RF(int,int);
void RB(int,int);
void LF(int,int);
void LB(int,int);


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  100 
#define SERVOMAX  650 
int a=1;
// our servo # counter
uint8_t servonum = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
 
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

}

void loop() {
    
stand();
}

int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   Serial.print("Angle: ");Serial.print(ang);
   Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}
void stand()
{       pwm.setPWM(0, 0, angleToPulse(95) );
          delay(50);
            pwm.setPWM(1, 0, angleToPulse(90) );
          delay(50);
            pwm.setPWM(2, 0, angleToPulse(95) );
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
  void RF(int rf,int rfr) //RightFront
{
  for(int RFpos=rf;RFpos>=rfr;RFpos-=1)
  {pwm.setPWM(1, 0, angleToPulse(110) );
          delay(50);
 pwm.setPWM(5, 0, angleToPulse(RFpos) );
          //delay(50);
          
  }
  pwm.setPWM(1, 0, angleToPulse(90) );
          delay(5);
}
void RB(int rb,int rbr) //RightBack
{
  for(int RBpos=rb;RBpos>=rbr;RBpos-=1)
  {
 pwm.setPWM(2, 0, angleToPulse(70) );
          delay(50);
 pwm.setPWM(6, 0, angleToPulse(RBpos) );
          //delay(50);
  }
   pwm.setPWM(2, 0, angleToPulse(95) );
          delay(5);
}
void LF(int lf,int lfr) //LeftFront
{
  for(int LFpos=lf;LFpos<=lfr;LFpos+=1)
  {
     pwm.setPWM(0, 0, angleToPulse(70) );
          delay(5);
 pwm.setPWM(4, 0, angleToPulse(LFpos) );
          //delay(50);
  }
  pwm.setPWM(0, 0, angleToPulse(90) );
          delay(5);
}
void LB(int lb,int lbr) //LeftBack
{
  for(int LBpos=lb;LBpos<=lbr;LBpos+=1)
  {
 pwm.setPWM(3, 0, angleToPulse(110) );
          delay(50);
 pwm.setPWM(7, 0, angleToPulse(LBpos) );
         // delay(50);
  }
  pwm.setPWM(3, 0, angleToPulse(90) );
          delay(5);
}
