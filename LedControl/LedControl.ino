struct rocker         //XY摇杆
{
  const byte Xpin = A0 ;
  const byte Ypin = A1 ;
  
  int x ;
  int y ;
}rocker;
struct encoder      //旋转编码器
{
  const byte CLKpin = 2 ;
  const byte DTpin = 3 ;

  int lastCLK = 0;
}encoder;

struct LEDry        //红黄LED
{
  const byte Redpin = 5 ;
  const byte Yelpin = 6 ;
  //亮度
  int count = 100;
}LEDry;
struct LEDrgb       //红绿蓝LED
{
  const byte Redpin = A3 ;
  const byte Genpin = A4 ;
  const byte Blupin = A5 ;
  //亮度
  int count = 255;
}LEDrgb;
struct LEDbg      //蓝绿LED
{
  const byte Blupin = 9 ;
  const byte Genpin = 10 ;

  int count = 100;
}LEDbg;

void setup() 
{
  //设置XY摇杆
  pinMode(rocker.Xpin, INPUT);
  pinMode(rocker.Ypin, INPUT);
    
  //设置旋转编码器
  pinMode(encoder.CLKpin, INPUT);
  pinMode(encoder.DTpin, INPUT);
  Serial.begin(9600);

  //设置红黄LED
  pinMode(LEDry.Redpin, OUTPUT);
  pinMode(LEDry.Yelpin, OUTPUT);

  //设置红绿蓝LED
  pinMode(LEDrgb.Redpin, OUTPUT);
  pinMode(LEDrgb.Genpin, OUTPUT);
  pinMode(LEDrgb.Blupin, OUTPUT);

  //设置蓝绿LED
  pinMode(LEDbg.Blupin, OUTPUT);
  pinMode(LEDbg.Genpin, OUTPUT);
}
void closeLED(int opt)
{
  switch( opt )
  {
    case 0:
      {
        analogWrite( LEDrgb.Redpin , 0);
        analogWrite( LEDrgb.Blupin , 0);
        analogWrite( LEDrgb.Genpin , 0);
        analogWrite( LEDbg.Blupin , 0);
        analogWrite( LEDbg.Genpin , 0);
      };break;
    case 1:
      {
        analogWrite( LEDry.Redpin , 0);
        analogWrite( LEDry.Yelpin , 0);
        analogWrite( LEDbg.Genpin , 0);
        analogWrite( LEDbg.Blupin , 0);
      };break;
    case 2:
      {
        analogWrite( LEDrgb.Redpin , 0);
        analogWrite( LEDrgb.Blupin , 0);
        analogWrite( LEDrgb.Genpin , 0);
        analogWrite( LEDry.Redpin , 0);
        analogWrite( LEDry.Yelpin , 0);
      };break;
  }
}

void setLEDry()
{
  closeLED(0);
  //Serial.println("welcome setLEDry             ");
  LEDry.count = ClockChanged( LEDry.count );
  analogWrite( LEDry.Redpin , LEDry.count );
  analogWrite( LEDry.Yelpin , LEDry.count);
}
void setLEDrgb()
{
  closeLED(1);
  //Serial.println("welcome setLEDrgb*********   ");

  LEDrgb.count = ClockChanged( LEDrgb.count );
  analogWrite( LEDrgb.Redpin , LEDrgb.count );
  analogWrite( LEDrgb.Genpin , LEDrgb.count );
  analogWrite( LEDrgb.Blupin , LEDrgb.count );
}
void setLEDbg()
{
  closeLED(2);
  //Serial.println("*********   welcome setLEDbg");
  LEDbg.count = ClockChanged( LEDbg.count );
  analogWrite( LEDbg.Blupin , LEDbg.count );
  analogWrite( LEDbg.Genpin , LEDbg.count );
}

int opt = 0;

void loop() {
  // put your main code here, to run repeatedly:
  rocker.x = analogRead( rocker.Xpin );
  rocker.y = analogRead( rocker.Ypin );
  if( rocker.x > 900 || rocker.y > 900 )
    {++opt;delay(100);}
  else if( rocker.x < 125 || rocker.y < 125 )
    {--opt;delay(100);}
 // delay(50);
  if( opt < 0 )
    opt = 2;
  else if( opt >2 )
    opt = 0;
 // Serial.print( rocker.x );Serial.print( "    " );
 // Serial.print( rocker.y );Serial.print( "    " );
 // Serial.println( opt );
  switch( opt )
  {
    case 0:setLEDry();break;
    case 1:setLEDrgb();break;
    case 2:setLEDbg();break;
  }
}
int ClockChanged(int val)
{
  int clkValue = digitalRead(encoder.CLKpin);
  int dtValue = digitalRead(encoder.DTpin);
  if (encoder.lastCLK != clkValue)
  {
    encoder.lastCLK = clkValue;
    val += (clkValue != dtValue ? 5 : -5);      //计数
    Serial.print("val = ");
    Serial.println(val);
  }
  return abs(val);
}
