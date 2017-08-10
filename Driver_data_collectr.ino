// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 int echo =13;
int trig =12;
int vcc=11;
int flex_vcc=8;
int flexpin=A0;
int pulsevcc=7;
int pulseground=6;
int pulsepin=A1;

int ultra2gnd=2;
int echo2=3;
int trig2=4;
int ultra2vcc=5;
static int time1,time2,time3,time4;
boolean flag=false;
void setup() 
{ 
  Serial.begin(9600);
  pinMode(echo2,INPUT);
  pinMode(trig2,OUTPUT);
  pinMode(ultra2gnd,OUTPUT);
  digitalWrite(ultra2gnd,LOW);
  pinMode(ultra2vcc,OUTPUT);
  digitalWrite(ultra2vcc,HIGH);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(vcc,OUTPUT);
  digitalWrite(vcc,HIGH);
  pinMode(flex_vcc,OUTPUT);
  digitalWrite(flex_vcc,HIGH);
  pinMode(pulsevcc,OUTPUT);
  digitalWrite(pulsevcc,HIGH);
  pinMode(pulseground,OUTPUT);
  digitalWrite(pulseground,LOW);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
void flexvalue_read()
{
 int flex_value = analogRead(flexpin);
//Serial.print("flex value =");
Serial.print(flex_value);
Serial.print(",");
//delay(1);  
}

void pulsevalue_read()
{  
int pulse_value = analogRead(pulsepin);
//Serial.print("pulse value=");
Serial.print(pulse_value);
Serial.print(",");
//delay(1);
}

void ultrasound_func()
{  
    digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  //digitalWrite(trig,LOW);
 int value=pulseIn(echo,HIGH);
 int  ultravalue=value/58.2;
 if ((ultravalue<=20)&&(flag==false))
  {
    time1=millis();
    flag=true;
  }
  
 if((ultravalue>20)&&(flag==true))
{time2=millis();
flag=false;
int tot=time2-time1;
Serial.print(tot);
Serial.print(",");
} 
  Serial.print(ultravalue);
  Serial.print(",");
  // Serial.println();
//delay(1);
}

void ultrasound_func2()
{  
    digitalWrite(trig2,LOW);
  delayMicroseconds(2);
  digitalWrite(trig2,HIGH);
  delayMicroseconds(10);
  //digitalWrite(trig,LOW);
 int value=pulseIn(echo2,HIGH);
 int  ultravalue=value/58.2;
 if ((ultravalue<=20)&&(flag==false))
  {
    time3=millis();
    flag=true;
  }
  
 if((ultravalue>20)&&(flag==true))
{time4=millis();
flag=false;
int tot=time4-time3;
Serial.print(tot);
Serial.print(",");
} 
  Serial.print(ultravalue);
  Serial.print(",");
  // Serial.println();
//delay(1);
}




void servo_sweep()
{
    for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {
pulsevalue_read();
flexvalue_read();
ultrasound_func(); 
ultrasound_func2();

Serial.println();
delay(50);// in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {
pulsevalue_read();
flexvalue_read(); 
ultrasound_func();  
Serial.println();
delay(50);
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
}

void loop() 
{ 
servo_sweep();
} 
