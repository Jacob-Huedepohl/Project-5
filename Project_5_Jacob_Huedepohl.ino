//Jacob Huedepohl
//Traffic Lights
//Project 5

#define westButton 3
#define eastButton 13
#define westRed 2
#define westYellow 1
#define westGreen 0
#define eastRed 12
#define eastYellow 11
#define eastGreen 10
#define westPedRed 4
#define westPedGreen 5
#define eastPedRed 6
#define eastPedGreen 7


#define yellowBlinkTime 500

boolean trafficWest = true; // west = true, east = false
int flowTime = 10000; // amount of time to let traffic flow
int changeDelay = 2000; // amount of time between color chages



void setup()
{
  // setup digital I/O pins
  pinMode(westButton, INPUT); //sets output pins
  pinMode(eastButton, INPUT);
  pinMode(westRed, OUTPUT);
  pinMode(westYellow, OUTPUT);
  pinMode(westGreen, OUTPUT);
  pinMode(eastRed, OUTPUT);
  pinMode(eastYellow, OUTPUT);
  pinMode(eastGreen, OUTPUT);
  pinMode(westPedRed, OUTPUT); //pedestrian output pins
  pinMode(westPedGreen, OUTPUT);
  pinMode(eastPedRed, OUTPUT);
  pinMode(eastPedGreen, OUTPUT);

  // set initial state for lights - west side is green first
  digitalWrite(westRed, LOW);
  digitalWrite(westYellow, LOW);
  digitalWrite(westGreen, HIGH);
  digitalWrite(eastRed, HIGH);
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastGreen, LOW);
  digitalWrite(westPedRed, HIGH); //Initial states of pedestrian lights
  digitalWrite(westPedGreen, LOW);
  digitalWrite(eastPedRed, LOW);
  digitalWrite(eastPedGreen, HIGH);
}
void blinkYellowLight(int yellowLED)
{
  for ( int i = 0; i < 5; i++) // blink yellow light
  {
    digitalWrite(yellowLED, LOW);
    delay(yellowBlinkTime);
    digitalWrite(yellowLED, HIGH);
    delay(yellowBlinkTime);
  }
}

void greentToYelllow(int green, int yellow)
{
  digitalWrite(green, LOW); //change east-facing lights from green
  // to yellow to red
  digitalWrite(yellow, HIGH);
  delay(changeDelay);
}

void yellowToRed(int yellow, int red)
{
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastRed, HIGH);
  delay(changeDelay);
}

void loop()
{
  if ( digitalRead(westButton) == HIGH) // request west>east traffic flow
  {
    if ( trafficWest != true)
      // Only continue if traffic flowing in the opposite (east) direction
    {
      trafficWest = true; // change traffic flow flag to west>east
      delay(flowTime); //give time for traffic to flow
      /*
        digitalWrite(eastGreen, LOW); //change east-facing lights from green
                                    // to yellow to red
        digitalWrite(eastYellow, HIGH);
        delay(changeDelay);*/
      greentToYelllow(eastGreen, eastYellow);
      /*
        digitalWrite(eastYellow, LOW);
        digitalWrite(eastRed, HIGH);
        delay(changeDelay);*/
      yellowToRed (eastYellow, eastRed);
      blinkYellowLight (westYellow);

      /*
        for ( int i = 0; i < 5; i++) // blink yellow light
        {
        digitalWrite(westYellow, LOW);
        delay(yellowBlinkTime);
        digitalWrite(westYellow, HIGH);
        delay(yellowBlinkTime);
        }
      */
      digitalWrite(westYellow, LOW);
      digitalWrite(westRed, LOW); //change west-facing lights from red to green
      digitalWrite(westGreen, HIGH);
      
      digitalWrite(westPedGreen, LOW); //change pedestrian lights based on west button being high
      digitalWrite(westPedRed, HIGH);
      digitalWrite(eastPedGreen, HIGH);
      digitalWrite(eastPedRed, LOW);

    }
  }
  if ( digitalRead(eastButton) == HIGH) //request east>west traffic flow
  {
    if ( trafficWest == true)
      //only continue if traffic flow is in the opposite (west) direction
    {
      trafficWest = false; // change traffic flow flag to east>west
      delay(flowTime);     //give time for traffic to flow
      /*
        digitalWrite(westGreen, LOW);
        //change west lights from green to yellow to red
        digitalWrite(westYellow, HIGH);
        delay(changeDelay);*/
      greentToYelllow(westGreen, westYellow);
      /*
        digitalWrite(westYellow, LOW);
        digitalWrite(westRed, HIGH);
        delay(changeDelay);*/
      yellowToRed (westYellow, westRed);
      blinkYellowLight (eastYellow);
      /*
        for ( int i = 0; i < 5; i++) // blink yellow light
        {
        digitalWrite(eastYellow, LOW);
        delay(yellowBlinkTime);
        digitalWrite(eastYellow, HIGH);
        delay(yellowBlinkTime);
        }
      */
      digitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, LOW); // change east-facing lights from red to green
      digitalWrite(eastGreen, HIGH);
      
      digitalWrite(westPedGreen, HIGH); //change pedestrian lights based on east button being high
      digitalWrite(westPedRed, LOW);
      digitalWrite(eastPedGreen, LOW);
      digitalWrite(eastPedRed, HIGH);

    }

  }

}
