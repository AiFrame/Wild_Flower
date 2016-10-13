/* Copyright (C) 2016 by Kaisavx <721462533@qq.com> */
/**
   @file MAX485.cpp
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

MAX485 max485_1(USART1,S17,BOARD_USART1_TX_PIN,BOARD_USART1_RX_PIN,STM32_PCLK2);
MAX485 max485_2(USART2,S31,BOARD_USART2_TX_PIN,BOARD_USART2_RX_PIN,STM32_PCLK1);

MAX485::MAX485(usart_dev*usart,uint8_t enPin,uint8_t txPin,uint8_t rxPin,uint32_t clockSpeed){
    this->usart=usart;
    this->enPin=enPin;
    this->txPin = txPin;
    this->rxPin = rxPin;
    this->clockSpeed = clockSpeed;
    
    status = MAX485_STATUS_CREATED;
}

void MAX485::begin(uint32_t baud){//config the uart's register
  if(status == MAX485_STATUS_INITED){
    return;
  }
    const stm32_pin_info *txi = &PIN_MAP[txPin];
    const stm32_pin_info *rxi = &PIN_MAP[rxPin];
    
    gpio_set_mode(txi->gpio_device,txi->gpio_bit,GPIO_AF_OUTPUT_PP);
    gpio_set_mode(rxi->gpio_device,rxi->gpio_bit,GPIO_INPUT_FLOATING);
    
    if(txi->timer_device !=NULL){
        timer_set_mode(txi->timer_device,txi->timer_channel,TIMER_DISABLED);
    }
    usart_init(usart);
    usart_set_baud_rate(usart,clockSpeed,baud);
    //usart_enable(m485Usart);
    
    usart->regs->CR1 =(USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE);
    usart->regs->CR1 |= USART_CR1_UE;
    
    pinMode(enPin, OUTPUT); //config the max485 enable pin
    digitalWrite(enPin,LOW);//init enPin to low
    
    status = MAX485_STATUS_INITED;
}

uint32_t MAX485::available(){
    return usart_data_available(usart);
}

uint8_t MAX485::read(){
    return usart_getc(usart);
}

void MAX485::write(uint8_t*datas,int len){//send the message to max485
    digitalWrite(enPin,HIGH);//set the enPin to High to enable the max485's write mode
    delayMicroseconds(MAX485_DELAY_TIME);//delay sometime to enable
    for(int i=0;i<len;i++){//send the data to the max485's uart
        usart_putc(usart,datas[i]);
        while(!(usart->regs->SR & USART_SR_TC));
    }
    usart_reset_rx(usart);//flush the receive buffer
    digitalWrite(enPin,LOW);//set the enPin to Low to disable the max485's write mode and chang to read mode
}
