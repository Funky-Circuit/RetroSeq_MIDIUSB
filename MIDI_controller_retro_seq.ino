/* about adafruit ssd1306 & GFX library:
https://github.com/adafruit/Adafruit_SSD1306
https://github.com/adafruit/Adafruit-GFX-Library
Software License Agreement (BSD License)

Copyright (c) 2012, Adafruit Industries
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holders nor the
names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

/* this code also use the following libraries that are under GNU Lesser General Public License v2.1:
MIDIUSB - https://github.com/arduino-libraries/MIDIUSB */


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MIDIUSB.h"


//variable
int button_up;
int last_button_up;
int button_down;
int last_button_down;
int button_time_up;
int last_button_time_up;
int button_time_down;
int last_button_time_down;
int pot_setting;
int last_pot_setting;
int pot_tempo = 100;
int last_pot_tempo;
int time_;
int pitch_[8] = {1, 3, 5, 6, 8, 10, 12, 0};
int oct_[8] = {1, 1, 1, 1, 1, 1, 1, 1};
int vel_[8] = {8, 8, 8, 8, 8, 8, 8, 8};
int last_pitch;
int last_oct;
int button_play;
int clock_play;
int pulse;
int string_1 = 20;
int string_2 = 35;
int string_3 = 50;


#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



//function

void note_name(int pitch)
{
  if (pitch == 0)
  {oled.print("--");}
  if (pitch == 1)
  {oled.print("C-");}
  if (pitch == 2)
  {oled.print("C#");}
  if (pitch == 3)
  {oled.print("D-");}
  if (pitch == 4)
  {oled.print("D#");}
  if (pitch == 5)
  {oled.print("E-");}
  if (pitch == 6)
  {oled.print("F-");}
  if (pitch == 7)
  {oled.print("F#");}
  if (pitch == 8)
  {oled.print("G-");}
  if (pitch == 9)
  {oled.print("G#");}
  if (pitch == 10)
  {oled.print("A-");}
  if (pitch == 11)
  {oled.print("A#");}
  if (pitch == 12)
  {oled.print("B-");}
}

void screen_update()
{
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(1);
  oled.setCursor(0, 0);
  if (pot_setting == 1)
  {oled.print("-> note / ");
  oled.print("octave");}
  if (pot_setting == 2)
  {oled.print("note / ");
  oled.print("-> octave");}
  if (pot_setting == 3)
  {oled.print("note / ");
  oled.print("-> velocity");}
  
  // -- string 1 --
  if (time_ == 0)
  {oled.setCursor(0, string_1);
  oled.print("x");}
  if (time_ == 1)
  {oled.setCursor(16, string_1);
  oled.print("x");}
  if (time_ == 2)
  {oled.setCursor(32, string_1);
  oled.print("x");}
  if (time_ == 3)
  {oled.setCursor(48, string_1);
  oled.print("x");}
  if (time_ == 4)
  {oled.setCursor(64, string_1);
  oled.print("x");}
  if (time_ == 5)
  {oled.setCursor(80, string_1);
  oled.print("x");}
  if (time_ == 6)
  {oled.setCursor(96, string_1);
  oled.print("x");}
  if (time_ == 7)
  {oled.setCursor(112, string_1);
  oled.print("x");}

  // -- string 2 --
  oled.setCursor(0, string_2);
  note_name(pitch_[0]);
  oled.setCursor(16, string_2);
  note_name(pitch_[1]);
  oled.setCursor(32, string_2);
  note_name(pitch_[2]);
  oled.setCursor(48, string_2);
  note_name(pitch_[3]);
  oled.setCursor(64, string_2);
  note_name(pitch_[4]);
  oled.setCursor(80, string_2);
  note_name(pitch_[5]);
  oled.setCursor(96, string_2);
  note_name(pitch_[6]);
  oled.setCursor(112, string_2);
  note_name(pitch_[7]);

  // -- string 3 octave --
  if (pot_setting == 1 || pot_setting == 2)
  {oled.setCursor(0, string_3);
  oled.print(oct_[0]);
  oled.setCursor(16, string_3);
  oled.print(oct_[1]);
  oled.setCursor(32, string_3);
  oled.print(oct_[2]);
  oled.setCursor(48, string_3);
  oled.print(oct_[3]);
  oled.setCursor(64, string_3);
  oled.print(oct_[4]);
  oled.setCursor(80, string_3);
  oled.print(oct_[5]);
  oled.setCursor(96, string_3);
  oled.print(oct_[6]);
  oled.setCursor(112, string_3);
  oled.print(oct_[7]);}

  // -- string 3 velocity --
  if (pot_setting == 3)
  {oled.setCursor(0, string_3);
  oled.print(vel_[0]);
  oled.setCursor(16, string_3);
  oled.print(vel_[1]);
  oled.setCursor(32, string_3);
  oled.print(vel_[2]);
  oled.setCursor(48, string_3);
  oled.print(vel_[3]);
  oled.setCursor(64, string_3);
  oled.print(vel_[4]);
  oled.setCursor(80, string_3);
  oled.print(vel_[5]);
  oled.setCursor(96, string_3);
  oled.print(vel_[6]);
  oled.setCursor(112, string_3);
  oled.print(vel_[7]);}
  
  oled.display();
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}



//main

void setup() 
{
  // initialize OLED display with address 0x3C for 128x64
  Serial.begin(9600);
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  delay(2000);         // wait for initializing
  pinMode(4 ,INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  //pinMode(8, INPUT);
  screen_update();
}


void loop() 
{

  // -- tempo --
  /*pot_tempo = map(analogRead(A1), 0, 1023, 60, 200);
  if (pot_tempo != last_pot_tempo)
  {
    screen_update();
  }
  last_pot_tempo = pot_tempo;*/

  //  -- setting --
  pot_setting = constrain(map(analogRead(A0), 0, 1023, 1, 4), 1, 3);
  if (pot_setting != last_pot_setting)
  {
    screen_update();
  }
  last_pot_setting = pot_setting;


  // -- time up --
  button_time_up = digitalRead(4);
  if (button_time_up != last_button_time_up && button_time_up == 1)
  {
    time_ += 1;
    if (time_ > 7)
    {
      time_ = 0;
    }
    screen_update();
  }
  last_button_time_up = button_time_up;


  // -- time down --
  button_time_down = digitalRead(5);
  if (button_time_down != last_button_time_down && button_time_down == 1)
  {
    time_ -= 1;
    if (time_ < 0)
    {
      time_ = 7;
    }
    screen_update();
  }
  last_button_time_down = button_time_down;


  // -- setting up --
  button_up = digitalRead(6);
  if (button_up != last_button_up && button_up == 1)
  {
    // -> pitch ++
    if (pot_setting == 1)
    {pitch_[time_] += 1;
    if (pitch_[time_] > 12)
    {
      oct_[time_] += 1;
      if (oct_[time_] > 4)
      {
        oct_[time_] = 1;
      }
      pitch_[time_] = 0;
    }
    screen_update();}
    // -> octave ++
    if (pot_setting == 2)
    {oct_[time_] += 1;
    if (oct_[time_] > 4)
    {
      oct_[time_] = 1;
    }
    screen_update();}
    // -> velocity ++
    if (pot_setting == 3)
    {vel_[time_] += 1;
    if (vel_[time_] > 12)
    {
      vel_[time_] = 1;
    }
    screen_update();}
  }
  last_button_up = button_up;


  // -- setting down --
  button_down = digitalRead(7);
  if (button_down != last_button_down && button_down == 1)
  {
    // -> pitch --
    if (pot_setting == 1)
    {pitch_[time_] -= 1;
    if (pitch_[time_] < 0)
    {
      oct_[time_] -= 1;
      if (oct_[time_] < 1)
      {
        oct_[time_] = 4;
      }
      pitch_[time_] = 12;
    }
    screen_update();}
    // -> octave --
    if (pot_setting == 2)
    {oct_[time_] -= 1;
    if (oct_[time_] < 1)
    {
      oct_[time_] = 4;
    }
    screen_update();}
    // -> velocity --
    if (pot_setting == 3)
    {vel_[time_] -= 1;
    if (vel_[time_] < 1)
    {
      vel_[time_] = 12;
    }
    screen_update();}
  }
  last_button_down = button_down;


  // --play without clock--
  /*button_play = digitalRead(8);
  if (button_play == 1)
  {
    for(int i = 0; i<=7; i++)
    {
      time_ = i;
      screen_update();
      if (pitch_[i] == 0)
      {
        noteOff(1, 35 + last_pitch + 12*(last_oct - 1), 80);
        MidiUSB.flush();
        delay(pot_tempo);
      }
      else
      {
        noteOn(1, 35 + pitch_[time_] + 12*(oct_[time_] - 1), 10*vel_[time_]);
        MidiUSB.flush();
        if (pitch_[time_] != last_pitch)
        {noteOff(1, 35 + last_pitch + 12*(last_oct - 1), 80);
        MidiUSB.flush();}
        delay(pot_tempo);
      }
      last_pitch = pitch_[i];
    }
  }*/

  // --play with clock--
  midiEventPacket_t rx;
  rx = MidiUSB.read();
  if(rx.byte1 == 0xFA)
  {
    time_ = 0;
    pulse = 0;
    clock_play = 1;
    noteOn(1, 35 + pitch_[time_] + 12*oct_[time_], 10*vel_[time_]);
    MidiUSB.flush();
    last_pitch = pitch_[time_];
    last_oct = oct_[time_];
    screen_update();
  }
  while (clock_play == 1)
  {
    rx = MidiUSB.read();
    if (rx.byte1 == 0xF8)
    {
      pulse += 1;
      if (pulse == 12)
      {
        time_ +=1;
        if (time_ > 7)
        {time_ = 0;}
        if (pitch_[time_] == 0)
        {
          noteOff(1, 35 + last_pitch + 12*last_oct, 80);
          MidiUSB.flush();
        }
        else
        {
          noteOn(1, 35 + pitch_[time_] + 12*oct_[time_], 10*vel_[time_]);
          MidiUSB.flush();
          if (pitch_[time_] != last_pitch)
          {noteOff(1, 35 + last_pitch + 12*last_oct, 80);
          MidiUSB.flush();}
        }
        last_pitch = pitch_[time_];
        screen_update();
        pulse = 0;
      }
    }
    if (rx.byte1 == 0xFC)
    {
      noteOff(1, 35 + pitch_[time_] + 12*oct_[time_], 80);
      MidiUSB.flush();
      clock_play = 0;
      screen_update();
    }
  }
  
}
