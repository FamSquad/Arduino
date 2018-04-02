


void setup()
{
  // define pin modes
  
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(6,OUTPUT);
 pinMode(7,OUTPUT);
 pinMode(8,OUTPUT);
}

void loop() 
{
  // loop to turn leds od seven seg ON
  
  for(int i=2;i<8;i++)
  {
    digitalWrite(i,HIGH);
    delay(100);
  }
  
  // loop to turn leds od seven seg OFF
  for(int i=2;i<8;i++)
  {
    digitalWrite(i,LOW);
    delay(100);
  }
  
  delay(0);
}
