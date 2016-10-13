/* Copyright (C) 2016 by Kaisavx <721462533@qq.com> */
/**
   @file Joint.cpp
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
#include "MAX485.h"


void sendHex(uint8_t data){//chang 0xFF to ASCII'FF ' and print to SerialUSB
  SerialUSB.print((data>>4)&0xF,HEX);
  SerialUSB.print(data&0xF,HEX);
  SerialUSB.print(" ");
}

uint8_t sum(uint8_t id,uint8_t len,uint8_t*data){//crc function (~(id+len+data[0]+...+data[len-1]))%0xFF
    uint8_t sum=0;
    sum+=id;
    sum+=len+1;
    for(int i=0;i<len;i++){
        sum+=data[i];
    }
    sum=~sum;
    return sum%0xFF;
}

void send(uint8_t id,uint8_t*datas,uint8_t dataLen){//give the id and datas to packet to the protocol and send to max485
    uint8_t sDatas[256];
    int n=0;
    sDatas[n++]=KPROTOCOL_HEAD1;
    sDatas[n++]=KPROTOCOL_HEAD2;
    sDatas[n++]=id;
    sDatas[n++]=dataLen+1;
    for(int i=0;i<dataLen;i++){
        sDatas[n++]=datas[i];
    }
    sDatas[n++]=sum(id,dataLen,datas);
    
    max485_1.write(sDatas,n);
    SerialUSB.println("Send Datas:");
    for(int i=0;i<n;i++){
      sendHex(sDatas[i]);
    }
    SerialUSB.println();
}



void setup(){
  SerialUSB.begin();//SerialUSB begin
  max485_1.begin(1000000);//max485 begin with 1M baud
}

void loop(){
  uint8_t sData[]={0x1};//cmd data 0x1 is get joint's status
  uint8_t rData[100];
  int rIndex=0;
  
  send(0x1,sData,ARRAY_LEN(sData));//packet and send the protocol to joint with id 0x1
  for(int i=0;i<5000;i++){
    while(max485_1.available()){
      rData[rIndex++]=max485_1.read();
    }
  }
  SerialUSB.println("Receive Datas:");//receive Datas print to USB
  for(int i=0;i<rIndex;i++){
      sendHex(rData[i]);
    }
    SerialUSB.println();
    delay(500);
}
