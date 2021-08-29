int CheckBrightness = 100;

void Update_W2812B_brightness()
{
  if (CurrentBrightness != CheckBrightness)
  {
    FastLED.setBrightness(CurrentBrightness);
    FastLED.show();
    //Serial.print("Brightness updated");
    CheckBrightness = CurrentBrightness;
  }
}
