#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 20

void UpdateVariable(int CurrentMode)
{
  switch (CurrentMode) {
    case 0:
      CurrentChannel = rotaryEncoder.readEncoder();
      break;
    case 1:
      CurrentVolume = rotaryEncoder.readEncoder();
      break;
    case 2:
      CurrentBrightness = rotaryEncoder.readEncoder();
      break;
    default:
      break;
  }
}

void rotary_onButtonClick()
{
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if (interruptTime - lastInterruptTime > Bounce) {
    Mode++;
    if (Mode == 3) //incase of more modes in the future
    {
      Mode = 0;
    }
    lastInterruptTime = interruptTime;
    //ToldEncoderBeginTime = millis(); //EPROM
    //Encoder_Pressed = true; //EPROM
    
    LastEncoderPush = millis();
    TextWipe_done = 0;
    switch (Mode) {
      case 0:
        rotaryEncoder.setBoundaries(800, 1080, circleValues);
        rotaryEncoder.setEncoderValue(CurrentChannel);
        //Serial.println("check");
        tft.drawString("        Frequenty          ", 0, 20, 2);
        break;
      case 1:
        rotaryEncoder.setBoundaries(0, 30, circleValues);
        rotaryEncoder.setEncoderValue(CurrentVolume);
        //Serial.println("check");
        tft.drawString("          Volume           ", 0, 20, 2);
        break;
      case 2:
        rotaryEncoder.setBoundaries(MIN_BRIGHTNESS, MAX_BRIGHTNESS, circleValues);
        rotaryEncoder.setEncoderValue(CurrentBrightness);
        //Serial.println("check");
        tft.drawString("        Brightness         ", 0, 20, 2);
        break;
      default:
        break;
    }
  }
}
