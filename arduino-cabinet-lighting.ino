#include <Adafruit_NeoPixel.h>

#define LEDS 6
#define NUMPIXELS 90

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDS, NEO_GRB + NEO_KHZ800);

const uint32_t off = pixels.Color(0,0,0);
const uint32_t niteLite = pixels.Color(200,85,0);

int lightSensor = A1;
int motionSensor = 11;
int greenLed = 12;

int pirState = LOW;
int moveTime = 0;

float rawRange = 1024; // 3.3v
float logRange = 5.0; // 3.3v = 10^5 lux

void setup(){
  Serial.begin(9600);
  pinMode(greenLed, OUTPUT);
  pinMode(motionSensor, INPUT);
  Serial.println("Sensors initialized..");
  
  pixels.begin(); // This initializes the NeoPixel library.
  colorWipe(off);
  pixels.show();
  Serial.println(F("Neopixels initialized.."));
    
  Serial.println("=== Start-ed up ===");
}

void loop(){
  int rawLite = analogRead(lightSensor);
//  Serial.println("here");
//  Serial.print("Raw data: ");
//  Serial.print(rawLite);
//  Serial.print(" - Lux: ");
//  Serial.println(RawToLux(rawLite));
//      colorWipe(niteLite);
//  delay(50);
//      Serial.println("off");
//      colorWipe(off);
//  delay(50);  
  moveTime = digitalRead(motionSensor);  // read input value
  if (moveTime == HIGH) {            // check if the input is HIGH
//    digitalWrite(leds, HIGH);  // turn LED ON

//digitalWrite(greenLed, HIGH);
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
      digitalWrite(greenLed, HIGH);
      
  Serial.println("here");
  Serial.print("Raw data: ");
  Serial.print(rawLite);
  Serial.print(" - Lux: ");
  Serial.println(RawToLux(rawLite));

      
      if(rawLite < 100){
        Serial.println("Illuminating");    
        
        colorWipe(niteLite);
      }      
    }
  } else {

    if (pirState == HIGH){
      digitalWrite(greenLed, LOW); // turn LED OFF
      colorWipe(off);
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}

float RawToLux(int raw)
{
  float logLux = raw * logRange / rawRange;
  return pow(10, logLux);
}

void colorWipe(uint32_t c) {
  for(uint16_t i=0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
    
  }
  pixels.show();
}
