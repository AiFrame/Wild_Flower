/* Copyright (C) 2016 by Kaisavx <721462533@qq.com> */
/**
   @file MAX485.h
   @brief Various architecture definitions Joint
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
#ifndef MAX485_H
#define MAX485_H

#include <stdint.h>

#include <WProgram.h>

#include "usb_serial.h"
#include "usart.h"
#include "gpio.h"
#include "boards.h"
#include "timer.h"
#include "io.h"
#include "KMacro.h"

#define MAX485_ENABLE 1
#define MAX485_DISABLE 0

#define MAX485_DELAY_TIME 100 //100us

typedef enum MAX485_STATUS_e{
  MAX485_STATUS_CREATED = 0x0,
  MAX485_STATUS_INITED = 0x1,
}MAX485_STATUS_t;

class MAX485{
private:
    
    uint8_t enPin;
    uint8_t txPin;
    uint8_t rxPin;
    uint32_t clockSpeed;
    
    MAX485_STATUS_t status;
    
    public:
    usart_dev*usart;
    
    MAX485(usart_dev*usart,uint8_t enPin,uint8_t txPin,uint8_t rxPin,uint32_t clockSpeed);
    void begin(uint32_t baud);
    uint32_t available();
    uint8_t read();
    void write(uint8_t*datas,int len);
};

extern MAX485 max485_1;
extern MAX485 max485_2;

#endif
