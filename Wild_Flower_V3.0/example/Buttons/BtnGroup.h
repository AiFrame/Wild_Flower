/* Copyright (C) 2016 by Kaisavx <721462533@qq.com> */
/**
   @file BtnGroup.h
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
#ifndef BUTTON_H
#define BUTTON_H
#include <stdint.h>
#include <maple.h>
#include <WProgram.h>

#define BTN_SHAKE_TIME 8 // 10ms

typedef enum BTN_INTFLAG_e{
  BTN_INTFLAG_CLICK = 0x1<<0,
  BTN_INTFLAG_RELEASE = 0x1<<1,
}BTN_INTFLAG_t;

typedef struct Button_s{
  uint8_t id; // btn port id 
  uint8_t intMode;// btn interrupt mode,HIGH/LOW/CHANGE
  bool btnSwitch;//btn switch
  
  void (*click)(struct Button_s*btn); // press process function
  void (*release)(struct Button_s*btn); // release process function
  void (*handler)(); // handler function
  
  uint8_t intFlag; //interrupt status flag
  int8_t count; // interrupt count
  
}Button_t;

class BtnGroup{
  public:
  Button_t*btnHead;
  uint16_t size;
  
  BtnGroup(Button_t* btnHead,uint16_t size){
    this->btnHead=btnHead;
    this->size=size;
  }
  
  void init();
  void timerProcess();
  int btnsClick();
  int btnsRelease();
  
  void btnsHandler(void (*handler)());
};

#endif
