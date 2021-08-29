/*
shelfed due to Rising edge activation of interupt rotary_onButtonClick() thus making it imposible with INPUT_PULLUP. 
if you want to utalize this function update the library PULLUP to PULLDOWN.
!!!Please not tested!!!
also EPROM code needs to be added for this function to work. 
comment sign of related code that needs to be uncommented is //EPROM
*/


/*void EPROM_Setup() {

}

void Update_EPROM_If_Required() {
  Serial.print(Encoder_Pressed);
  if (Encoder_Pressed == true) {
    if (digitalRead(ROTARY_ENCODER_BUTTON_PIN) == LOW) {
      Serial.print(" Button Still Pressed");
      if (ToldEncoderBeginTime - millis() > 2000) {
        Serial.print(" Data Stored In EPROM");
        Encoder_Pressed = false;
      }
    }
    else {
      Encoder_Pressed = false;
    }
  }
}*/
