/* Copyright (C) 2016 by Kaisavx <721462533@qq.com> */
/**
   @file KMacro.h
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

#ifndef K_MACRO_H
#define K_MACRO_H

#define ARRAY_LEN(arr) (sizeof(arr)/sizeof(arr[0]))

#define HEX_H(data) (((uint8_t*)&data)[1])
#define HEX_L(data) (((uint8_t*)&data)[0])

#define S1 21
#define S2 22
#define S3 23
#define S4 17
#define S5 18
#define S6 2
#define S7 3
#define S8 1
#define S9 0
#define S10 10
#define S11 12
#define S12 11
#define S13 19
#define S14 20
#define S15 27
#define S16 28
#define S17 31
#define S18 32
#define S19 33
#define S20 34
#define S21 35
#define S22 36
#define S23 37
#define S24 38
#define S25 6
#define S26 26
#define S27 25
#define S28 4
#define S29 5
#define S30 9
#define S31 14
#define S32 24

#define AD0 15
#define AD1 16

#endif
