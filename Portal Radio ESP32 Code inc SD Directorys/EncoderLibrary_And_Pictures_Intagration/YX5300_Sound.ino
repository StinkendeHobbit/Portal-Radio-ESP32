static int8_t Send_buf[8] = {0} ;
int checkvariable = 0;
int VolumeCheck = 0;
int ChannelCheck = 853;
int StaticNoiseCheck = 0;
//int DAC_off_check = 1;

/************Command byte**************************/
#define CMD_NEXT_SONG 0X01
#define CMD_PREV_SONG 0X02
#define CMD_PLAY_W_INDEX 0X03
#define CMD_VOLUME_UP 0X04
#define CMD_VOLUME_DOWN 0X05
#define CMD_SET_VOLUME 0X06
#define CMD_EQUALIZER 0X07
#define CMD_SINGLE_CYCLE_PLAY 0X08
#define CMD_SEL_DEV 0X09
#define DEV_TF 0X02
#define CMD_SLEEP_MODE 0X0A
#define CMD_WAKE_UP 0X0B
#define CMD_RESET 0X0C
#define CMD_PLAY 0X0D
#define CMD_PAUSE 0X0E
#define CMD_PLAY_FOLDER_FILE 0X0F
#define CMD_STOP_PLAY 0X16
#define CMD_FOLDER_CYCLE 0X17
#define CMD_SHUFFLE_PLAY 0X18
#define CMD_SET_SINGLE_CYCLE 0X19
#define SINGLE_CYCLE_ON 0X00
#define SINGLE_CYCLE_OFF 0X01
#define CMD_SET_DAC 0X1A
#define DAC_ON  0X00
#define DAC_OFF 0X01
#define CMD_PLAY_W_VOL 0X22
#define CMD_SHUFFLE_FOLDER 0X28 //not working as far as I know!
#define Query_STATUS 0X42
#define Query_VOLUME 0X43
#define Query_EQUALIZER 0X44
#define Query_TOT_FILES 0X48
#define Query_PLAYING 0X4C
#define Query_FLDR_FILES 0X4E
#define Query_TOT_FLDR 0X4F

/*********************************************************************/

void sendCommand(byte command, byte option1, byte option2)
{
  delay(20);
  Send_buf[0] = 0x7e; //
  Send_buf[1] = 0xff; //
  Send_buf[2] = 0x06; //
  Send_buf[3] = command; //
  Send_buf[4] = 0x00;//
  Send_buf[5] = option1;//datah
  Send_buf[6] = option2; //datal
  Send_buf[7] = 0xef; //
  for (uint8_t i = 0; i < 8; i++) //
  {
    Serial2.write(Send_buf[i]) ;
  }
}

void YX5300_Setup() {
  sendCommand(CMD_RESET, 0 , 0);
  delay(1000);
  sendCommand(CMD_SEL_DEV, 0, DEV_TF);
  delay(200);

}

void YX5300_Update_Volume() {
  if (CurrentVolume != VolumeCheck) {
    sendCommand(CMD_SET_VOLUME, 0, CurrentVolume);
    delay(200);
    sendCommand(Query_VOLUME, 0, 0);
    delay(200);
    if (VolumeCheck > CurrentVolume) {
      for (int i = VolumeCheck; i > CurrentVolume; i--)
      {
        fillArc(160, 150, i * 3.3 - 55 , 1, 200, 100, 10, tft.color565(26, 26, 26));
      }
    }
    int i = VolumeCheck;
    if (displayVolume_done == 1 || VolumeCheck == 0) 
    {
        i = 1;
    }
    for (i; i <= CurrentVolume; i++)
    {
      fillArc(160, 150, i * 3.3 - 55 , 1, 200, 100, 10, tft.color565(0, 255, 255));
      if (i == 1 || i == 2) {
        tft.fillRect(2, 70, 10, 25, tft.color565(26, 26, 26));
      }
    }
    tft.fillRect(306, 70, 10, 25, tft.color565(26, 26, 26));
    displayVolume_done = 0;
    LastVolumeUpdate = millis();
    VolumeCheck = CurrentVolume;
  }
}

void YX5300_Update_Channel() {
  if (CurrentChannel != ChannelCheck) {
    ChannelCheck = CurrentChannel;
    //if ((CurrentChannel != 800) && (DAC_off_check = 1)) {
    //sendCommand(CMD_SET_DAC, 0, DAC_ON);
    //DAC_off_check = 0;
    //delay(200);
    //}
    switch (CurrentChannel) {
      case 800:
        sendCommand(CMD_STOP_PLAY, 0 , 0);
        delay(200);
        //sendCommand(CMD_SET_DAC, 0, DAC_OFF);
        //delay(200);
        //DAC_off_check = 1;
        StaticNoiseCheck = 0;
        leds[45] = CRGB(0, 255, 255);
        FastLED.show();
        break;
      case 825:
        sendCommand(CMD_FOLDER_CYCLE, 0 , 1);
        delay(200);
        StaticNoiseCheck = 0;
        leds[45] = CRGB(0, 255, 255);
        FastLED.show();
        break;
      case 852:
        sendCommand(CMD_SET_SINGLE_CYCLE, 0 , SINGLE_CYCLE_ON);
        delay(200);
        sendCommand(CMD_PLAY_FOLDER_FILE, 1, 1);
        delay(200);
        StaticNoiseCheck = 0;
        leds[45] = CRGB(0, 255, 255);
        FastLED.show();
        break;
      case 950:// || 955 || 960 || 965 || 970 || 975 || 980 || 985 || 990 || 995 || 1000 || 1005 || 1010 || 1015 || 1020 || 1025 || 1030 || 1035 || 1040 || 1045 || 1050 || 1055 || 1060 || 1065 || 1070 || 1075 || 1080: //WHY NOT IDE
      case 955:
      case 960:
      case 965:
      case 970:
      case 975:
      case 980:
      case 985:
      case 990:
      case 995:
      case 1000:
      case 1005:
      case 1010:
      case 1015:
      case 1020:
      case 1025:
      case 1030:
      case 1035:
      case 1040:
      case 1045:
      case 1050:
      case 1055:
      case 1060:
      case 1065:
      case 1070:
      case 1075:
      case 1080:
        Serial.print("Easterege ");
        sendCommand(CMD_SET_SINGLE_CYCLE, 0 , SINGLE_CYCLE_ON);
        delay(200);
        Serial.print(int((CurrentChannel - 950) / 5 + 1));
        sendCommand(CMD_PLAY_FOLDER_FILE, 4, int((CurrentChannel - 950) / 5 + 1));
        delay(200);
        StaticNoiseCheck = 0;
        leds[45] = CRGB(0, 255, 0);
        FastLED.show();
        break;
      default:
        if (StaticNoiseCheck == 0) {
          sendCommand(CMD_FOLDER_CYCLE, 0 , 3);
          delay(200);
          StaticNoiseCheck = 1;
          leds[45] = CRGB(255, 0, 0);
          FastLED.show();
        }
        break;

    }
    //char buff[10]; //uncoment when I have made 279 remaining images
    //sprintf(buff, "/%i.jpg" , CurrentChannel);
    //drawSdJpeg(buff, 0, 0);     // This draws a jpeg pulled off the SD Card
  }
}

void YX5300_Print_Return_Data() {
  checkvariable++;
  //Serial.print(" ");
  //Serial.print(checkvariable);
  //Serial.print(" ");
  String ReturnHex = String(Serial2.read(), HEX);
  if (ReturnHex == "7e") {
    Serial.print("Start ");
    checkvariable = 1;
  }
  else {
    if (ReturnHex == "ef") {
      Serial.println("End");
      checkvariable = 0;
    }
    else {
      if (checkvariable == 4) {
        if (ReturnHex == "3a") {
          Serial.print("TF_INSERT ");
        }
        else {
          if (ReturnHex == "3b") {
            Serial.print("TF_REMOVE ");
          }
          else if (ReturnHex == "3d") {
            Serial.print("FILE_END ");
          }
          else if (ReturnHex == "3f") {
            Serial.print("INIT ");
          }
          else if (ReturnHex == "40") {
            Serial.print("ERR_FILE ");
          }
          else if (ReturnHex == "41") {
            Serial.print("ACK_OK ");
          }
          else if (ReturnHex == "42") {
            Serial.print("STATUS ");
          }
          else if (ReturnHex == "43") {
            Serial.print("VOLUME ");
          }
          else if (ReturnHex == "44") {
            Serial.print("EQUALIZER ");
          }
          else if (ReturnHex == "48") {
            Serial.print("TOT_FILES ");
          }
          else if (ReturnHex == "4c") {
            Serial.print("PLAYING ");
          }
          else if (ReturnHex == "4e") {
            Serial.print("FLDR_FILES");
          }
          else if (ReturnHex == "4f") {
            Serial.print("TOT_FLDR ");
          }
          else {
            Serial.print(ReturnHex);
            Serial.print(" ");
          }
        }
      }
      else {
        Serial.print(ReturnHex);
        Serial.print(" ");
      }
      if (checkvariable == 1) {
        Serial.println(ReturnHex);
      }
    }
  }
}
