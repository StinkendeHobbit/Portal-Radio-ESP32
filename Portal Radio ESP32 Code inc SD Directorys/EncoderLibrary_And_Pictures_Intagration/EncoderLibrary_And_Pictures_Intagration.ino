#include <FastLED.h>
#include <pixeltypes.h>
#define NUM_LEDS 46
#define DATA_PIN 33
CRGB leds[NUM_LEDS];

#include <SPI.h>

#include <FS.h>
#include <SD.h>

#include "TFT_eSPI.h"
TFT_eSPI tft = TFT_eSPI();

// JPEG decoder library
#include <JPEGDecoder.h>

#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"

#define ROTARY_ENCODER_A_PIN 14
#define ROTARY_ENCODER_B_PIN 27
#define ROTARY_ENCODER_BUTTON_PIN 26
#define ROTARY_ENCODER_STEPS 4
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, -1, ROTARY_ENCODER_STEPS);

bool circleValues = false;

#define Bounce 50
int Mode = 0;
int CurrentVolume = 5;
int CurrentChannel = 852;
int CurrentBrightness = 50;
//unsigned long ToldEncoderBeginTime = 0; //EPROM
//bool Encoder_Pressed = false; //EPROM
uint32_t LastVolumeUpdate = millis();
uint32_t LastEncoderPush = millis();
int displayVolume_done = 1;
int TextWipe_done = 1;


void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  delay(500);
  YX5300_Setup();
  rotaryEncoder.begin();
  rotaryEncoder.setup(
    [] { rotaryEncoder.readEncoder_ISR(); },
    [] { rotary_onButtonClick(); });
  rotaryEncoder.setBoundaries(800, 1080, circleValues);
  rotaryEncoder.setEncoderValue(CurrentChannel);
  rotaryEncoder.disableAcceleration();
  
  SD_card_setup();
  //tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextColor(tft.color565(0, 255, 255), tft.color565(26, 26, 26));
  tft.setTextSize(2);

  //delay(2000); //incase of brown alert after voltage drop
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(CurrentBrightness);
  for (int i = 0; i < 46; i++) {
    leds[i] = CRGB(0, 255, 255);
  }
  FastLED.show();
}

void loop()
{
  UpdateVariable(Mode);
  YX5300_Update_Volume();
  YX5300_Update_Channel();
  Update_W2812B_brightness();
  if (rotaryEncoder.encoderChanged())
  {
    Serial.print("FM: ");
    Serial.print(float(CurrentChannel) / 10);
    Serial.print("Mhz ");
    Serial.print("Volume: ");
    Serial.print(CurrentVolume);
    Serial.print(" Brightness ");
    Serial.println(CurrentBrightness);

  }
  
  if (millis() - LastVolumeUpdate > 3000 && displayVolume_done == 0) {
    //char buff[10]; //uncoment when I have made 279 remaining images
    //sprintf(buff, "/%i.jpg" , CurrentChannel);
    //drawSdJpeg(buff, 0, 0);     // This draws a jpeg pulled off the SD Card
    drawSdJpeg("/852.jpg", 0, 0);     // This draws a jpeg pulled off the SD Card
    displayVolume_done = 1;
  }
  if (millis() - LastEncoderPush > 1000 && TextWipe_done == 0)
  {
    tft.drawString("                           ", 0, 20, 2);
    TextWipe_done = 1;
  }
  
  while (Serial2.available()) {
    YX5300_Print_Return_Data();
  }
  //Update_EPROM_If_Required(); //EPROM
}
