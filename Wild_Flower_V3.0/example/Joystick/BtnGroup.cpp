/* Copyright (C) 2016 by Kaisavx <721462533@qq.com> */
/**
   @file BtnGroup.cpp
   @brief Various architecture definitions Rocker
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
#include "BtnGroup.h"

  
void BtnGroup::init(){
  Button_t*btn;
  for(int i=0;i<size;i++){
    btn=&btnHead[i];
    pinMode(btn->id,INPUT_PULLUP);
    attachInterrupt(btn->id,btn->handler,(ExtIntTriggerMode)btn->intMode);
  }
}
  
void BtnGroup::timerProcess(){
  Button_t*btn;
  for(int i=0 ;i<size;i++){
    btn=&btnHead[i];
    if(btn->count > 0){
      btn->count--;
    }else if(btn->count == 0){
      uint8_t val=digitalRead(btn->id);
      btn->count--;
      if(btn->btnSwitch!=val){
        btn->btnSwitch==HIGH ? btn->intFlag|=BTN_INTFLAG_CLICK : btn->intFlag|=BTN_INTFLAG_RELEASE;
        
        btn->btnSwitch = val;
      }
    }else{
      uint8_t val=digitalRead(btn->id);
      if(btn->btnSwitch != val){
        btn->count = BTN_SHAKE_TIME;
      }
    }
  }
}

int BtnGroup::btnsClick(){
  Button_t *btn;
  int ret=0;
  for(int i=0;i<size;i++){
    btn=&btnHead[i];
    if(btn->intFlag&BTN_INTFLAG_CLICK){
      btn->intFlag&=~BTN_INTFLAG_CLICK;
      switch(btn->intMode){
      case RISING:
      break;
      case FALLING:
      case CHANGE:
        if(btn->click!=NULL){
          btn->click(btn);
        }
        ret++;
      break;
      }
    }
  }
  return ret;
}

int BtnGroup::btnsRelease(){
  Button_t *btn;
  int ret = 0;
  for(int i=0;i<size;i++){
    btn=&btnHead[i];
    if(btn->intFlag&BTN_INTFLAG_RELEASE){
      btn->intFlag&=~BTN_INTFLAG_RELEASE;
      switch(btn->intMode){
        case FALLING:
        break;
        case RISING:
        case CHANGE:
        if(btn->release!=NULL){
          btn->release(btn);
        }
        ret++;
        break;
      }
    }
  }
  return ret;
}
  
void BtnGroup::btnsHandler(void (*handler)()){
  Button_t *btn;
  for(int i=0;i<size;i++){
    btn=&btnHead[i];
    if(btn->handler == handler){
      if(btn->count<0 && btn->btnSwitch!=digitalRead(btn->id)){
        btn->count = BTN_SHAKE_TIME;
        
      }
      return;
    }
  }
}
