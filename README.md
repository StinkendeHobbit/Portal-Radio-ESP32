# Portal-Radio-ESP32
This repository contains all files related to the functional Portal Radio utilizing the ESP32, ILI9341 TFT display , a rotary encoder, YX5300 Serial audio, separate bluetooth audio module MH-M28, and the PAM8610 audio amplifier. Intended for reproducing this project and/or modifications.

Please note that the original .stl files are form Alex I. Who uploaded it on myminifactory.com this derectory only contains modified files from project. Please see the link for the original files: https://www.myminifactory.com/object/3d-print-portal-radio-50006

Bill of Materials:
-esp32 dev v1
-2.2 inch TFT Display 240*320px ILI9341
-YX5300 Serial audio decoder inc 3.5mm jack
-MH-M28 Bluethooth audio module
-custom pcb
-PAM8610 2x15W audio amplifier 12V
-dc-dc buck converter 12v-5v
-12V3A power supply
-2 Full-range 10watt 8ohm speakers
-26 WS2812B 144LEDS/M
-1pdt switch
-3pdt switch
-female barreljack connector
-Rotary Encoder EC11 20mm
-some male-male 3.5mm jack wires
-groundloop isolator(helps angainst noise)
other components are already noted on Alex I myminifactory page.

Wiring:
Simply follow the wiring diagram in the for the pcb. wire the 2 audio courses the 3pdt switch to make an audio switch. then simple wire the 12v form the jack to the amplifier and the buck converter. Which is wired to the pcb via a dupont connector(note us the inner most connection with the thickest trace the otherone is for the MH-M28). Lastley add a groundloop isolator to the input side of the transformer(I used a of the shelf one which is plug and play).
Lastely, make a note: HUGE SUCCES!

