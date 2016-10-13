/* Copyright (C) 2016 by Kaisavx <721462533@qq.com> */
/**
   @file Buttons.cpp
   @brief Various architecture definitions Buttons
*/
/*
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   
   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
   
   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
   
   - Neither the name of the Ai.Frame Company nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.
   
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COMPANY OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "KMacro.h"
#include <stdint.h>
#include "BtnGroup.h"

#define TIMER1_DELAY 1000 //1ms/t

enum BTN_t{
  BTN_ROCKER = S1,
  BTN1 = S2,
  BTN2 = S3,
  BTN3 = S6,
  BTN4 = S7,
  BTN5 = S11,
  BTN6 = S12,
  BTN7 = S13,
  BTN8 = S15,
  BTN9 = S16,
};

Button_t btns[]={ //declare buttons 
  {BTN1 , CHANGE , HIGH , btnsPress , btnsRelease , NULL,0,-1},
  {BTN2 , CHANGE , HIGH , btnsPress , btnsRelease , NULL,0,-1},
  {BTN3 , CHANGE , HIGH , btnsPress , btnsRelease , NULL,0,-1},
  {BTN4 , CHANGE , HIGH , btnsPress , btnsRelease , NULL,0,-1},
  {BTN5 , CHANGE , HIGH , btnsPress , btnsRelease , NULL,0,-1},
  {BTN6 , CHANGE , HIGH , btnsPress , btnsRelease , NULL,0,-1},
  {BTN7 , CHANGE , HIGH , btnsPress , btnsRelease , NULL,0,-1},
  {BTN8 , CHANGE , HIGH , btnsPress , btnsRelease , NULL,0,-1},
  {BTN9 , CHANGE , HIGH , btnsPress , btnsRelease , NULL,0,-1},
  {BTN_ROCKER , CHANGE , HIGH , btnsPress , btnsRelease , NULL,0,-1},
};

BtnGroup btnGroup(btns,ARRAY_LEN(btns));// declare buttons manager


void setup(){
  SerialUSB.begin();
   
  btnGroup.init();//buttons manager init
  
  
  //timer1 config
  Timer1.pause();
  Timer1.setChannel1Mode(TIMER_OUTPUT_COMPARE);
  Timer1.setPeriod(TIMER1_DELAY);
  Timer1.setCompare1(1);
  Timer1.attachCompare1Interrupt(Timer1_Interrupt);
  Timer1.refresh();
  Timer1.resume();
}


void loop(){
  btnGroup.btnsClick();//buttons click process
  btnGroup.btnsRelease();//buttons release process
  delay(100);
}

void Timer1_Interrupt(){
  
  btnGroup.timerProcess();//buttons timer process
}


void btnsPress(Button_t*btn){// press process function
  switch(btn->id){
   case BTN_ROCKER:
   SerialUSB.println("BTN ROCKER press!");
   break;
   case BTN1:
   SerialUSB.println("BTN1 press!");
   break;
   case BTN2:
   SerialUSB.println("BTN2 press!");
   break;
   case BTN3:
   SerialUSB.println("BTN3 press!");
   break;
   case BTN4:
   SerialUSB.println("BTN4 press!");
   break;
   case BTN5:
   SerialUSB.println("BTN5 press!");
   break;
   case BTN6:
   SerialUSB.println("BTN6 press!");
   break;
   case BTN7:
   SerialUSB.println("BTN7 press!");
   break;
   case BTN8:
   SerialUSB.println("BTN8 press!");
   break;
   case BTN9:
   SerialUSB.println("BTN9 press!");
   break;
   
  }
}


void btnsRelease(Button_t*btn){// press release function
  
    switch(btn->id){
     case BTN_ROCKER:
     SerialUSB.println("BTN ROCKER release!");
     break;
     case BTN1:
     SerialUSB.println("BTN1 release!");
     break;
     case BTN2:
     SerialUSB.println("BTN2 release!");
     break;
     case BTN3:
     SerialUSB.println("BTN3 release!");
     break;
     case BTN4:
     SerialUSB.println("BTN4 release!");
     break;
     case BTN5:
     SerialUSB.println("BTN5 release!");
     break;
     case BTN6:
     SerialUSB.println("BTN6 release!");
     break;
     case BTN7:
     SerialUSB.println("BTN7 release!");
     break;
     case BTN8:
     SerialUSB.println("BTN8 release!");
     break;
     case BTN9:
     SerialUSB.println("BTN9 release!");
     break;
     
    }
}
