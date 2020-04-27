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

void greenLightOn (int yellow, int red, int green)
{
  digitalWrite(westYellow, LOW);
  digitalWrite(westRed, LOW); //change west-facing lights from red to green
  digitalWrite(westGreen, HIGH);
}

void pedLightsRed (int green, int red)
{
  digitalWrite(westPedGreen, LOW); //change pedestrian lights based on west button being high
  digitalWrite(westPedRed, HIGH);
}

void pedLightsGreen (int green, int red)
{
  digitalWrite(eastPedGreen, HIGH);
  digitalWrite(eastPedRed, LOW);
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

      greentToYelllow(eastGreen, eastYellow);

      yellowToRed (eastYellow, eastRed);

      blinkYellowLight (westYellow);

      greenLightOn (westYellow, westRed, westGreen);

      pedLightsRed (westPedGreen, westPedRed);

      pedLightsGreen (eastPedGreen, eastPedRed);
    }
  }
  if ( digitalRead(eastButton) == HIGH) //request east>west traffic flow
  {
    if ( trafficWest == true)
      //only continue if traffic flow is in the opposite (west) direction
    {
      trafficWest = false; // change traffic flow flag to east>west
      delay(flowTime);     //give time for traffic to flow

      greentToYelllow(westGreen, westYellow);

      yellowToRed (westYellow, westRed);

      blinkYellowLight (eastYellow);

      greenLightOn (westYellow, eastRed, eastGreen);

      pedLightsGreen (westPedGreen, westPedRed);

      pedLightsRed (eastPedGreen, eastPedRed);
    }

  }

}
