
//http://blog.sina.com.cn/s/blog_5e9b181a01011ycg.html
#include "wild_flower_TimerOne.h"

#define N 15
#define Chest_LED 2
#define BOARD_LED_PIN 13
#define FILTER_RATE 2500 // in microseconds
#define breathLED 13    //呼吸燈參數 數值越大 頻率越高

unsigned int analog_Value[10][N];
unsigned int battery_Value;
unsigned int temp_Value[10];
unsigned int PWM_Value[10];
unsigned int PWM_DIR[10] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0}; //跟隨方向 1 代表正向 0代表反向 分別代表 左邊四個自由度 L4 L3 L2 L1  右邊四個自由度 R1 R2 R3 R4 和 搖桿兩個自由度的方向 X Y
unsigned int PWM_NBR[8] = {5, 6, 7, 8, 25, 26, 27, 28};// 5678 25 26 27 28
unsigned int pointer[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned int L_R[10] = {A5, A7, A4, A6, A2, A0, A3, A1, A8, A9}; // 57462031
unsigned int max_Value[10] = {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024};
unsigned int min_Value[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned int button_value = 0;
unsigned char button_value2 = 0;
unsigned char button_value3 = 0;
unsigned char button_value4 = 0;
unsigned char redata[100];

int button_nbr[10] = {22, 24, 26, 28, 30, 32, 34, 36, 40, 38};
boolean button_change = false;

void setup() {
  for (int i = 0; i < 10; i ++) {
      pinMode(button_nbr[i], INPUT_PULLUP);
  }
  
  pinMode(BOARD_LED_PIN, OUTPUT);
  // Declare analogInputPin as INPUT_ANALOG:
  /*for (int i = 0; i < 8; i ++) {
      pinMode(L_R[i], INPUT_ANALOG);
  }*/
  digitalWrite(BOARD_LED_PIN, HIGH);
  limit_calculate();
  
  Timer1.initialize(10000);
  Timer1.attachInterrupt(filter);
  
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.println("EN0!");
  delay(50);
}

void loop() {
  // Read the analog input into a variable:
  /*for (char i = 0; i < 8; i ++) {
      PWM_Value[i] = analogRead(L_R[i]);
  }*/
  Chest_LED_Fading();
  for (int j = 0; j < 10; j ++) {
              temp_Value[j] = analogRead(L_R[j]);
              max_Value[j] = max(temp_Value[j], max_Value[j]);
              min_Value[j] = min(temp_Value[j], min_Value[j]);
         }
  Serial_process();
  if ((button_change == true) && (button_value2 == 0)) {
    if ( button_value3 == 0 ) {
      switch (button_value)
      {
            case 4:
            Serial1.println("EN8!");//
            break;
            case 64:
            Serial1.println("EN7!");//
            break;
            case 8:
            Serial1.println("EN14!");//
            break;
            case 2:
            Serial1.println("EN13!");//
            break;
            case 1:
            Serial1.println("EN11!");//
            break;
            case 128:
            Serial1.println("EN12!");//
            break;
            default :
                Serial1.println("EN0!");
                delay(10);
            break;
      }
    }
    if ( button_value == 0) {
      switch (button_value3)
      {
            case 1:
            Serial1.println("EN1!");//
            break;
            case 2:
            Serial1.println("EN2!");//
            break;
            case 3:
            Serial1.println("EN3!");//
            break;
            case 4:
            Serial1.println("EN4!");//
            break;
            case 5:
            Serial1.println("EN5!");//
            break;
            case 6:
            Serial1.println("EN6!");//
            break;
            default :
                Serial1.println("EN0!");
                delay(10);
            break;
      }
    }
      button_change = false;
  }
  
  for (char i = 0; i < 10; i ++) {
          Serial.print(PWM_Value[i]);
          Serial.print(',');
          if (i == 9) {
              Serial.println(button_value);
          }
  } 
  if (button_value2 == 1) {

      for (char i = 0; i < 8; i ++) {
                Serial1.write('#');
                Serial1.print(PWM_NBR[i], DEC);
                Serial1.write('P');
                
                if (PWM_DIR[i] == 0) {
                    Serial1.print( min(max(map(PWM_Value[i],min_Value[i], max_Value[i], 700, 2400),900),2200),DEC);
                } else {
                    Serial1.print( min(max(map(PWM_Value[i],min_Value[i], max_Value[i], 2400, 700),900),2200),DEC);
                }    
                if (i == 7) {
                     Serial1.println("T50!");
                }
            }
    
  }
  delay(50);
}

void filter()
{
    char count,nbr;
    unsigned int analog_sum;
    static unsigned int t;
    unsigned int temp_button = 0;
    unsigned char temp_button2 = 0;
    unsigned char temp_button3 = 0;
    unsigned char temp_button4 = 0;
    t ++;
    
    battery_Value = analogRead(A11);
    for (nbr = 0; nbr < 10; nbr ++) {
         analog_Value[nbr][pointer[nbr] ++] = analogRead(L_R[nbr]);
         if (pointer[nbr] == N) {
             pointer[nbr] = 0; 
         }
         analog_sum = 0;
         for (count = 0; count < N; count ++) {
             analog_sum += analog_Value[nbr][count];
         }
         PWM_Value[nbr] = analog_sum / N;
    }
    temp_button = 0;
    for (int i = 0; i < 10; i ++) {
      bitWrite(temp_button, i, !(digitalRead(button_nbr[i])));
    }
    temp_button4 = digitalRead(button_nbr[8]);
    temp_button2 = digitalRead(button_nbr[9]);
     if((PWM_Value[9]<300) && (400<PWM_Value[8]<550))
    {
      temp_button3 = 1;//Serial1.println("EN1!");
    }
    else if((PWM_Value[9]>650) && (400<PWM_Value[8]<550))
    {
      temp_button3 = 2;//Serial1.println("EN2!");
    }
    else if((400<PWM_Value[9]<550) && (PWM_Value[8]>650))
    {
      temp_button3 = 3;//Serial1.println("EN3!");
    }
    else if((400<PWM_Value[9]<550) && (PWM_Value[8]<300))
    {
      temp_button3 = 4;//Serial1.println("EN4!");
    }
    else if((PWM_Value[9]<300) && (PWM_Value[8]>650))
    {
      temp_button3 = 5;//Serial1.println("EN5!");
    }
    else if((PWM_Value[9]<300) && (400<PWM_Value[8]<300))
    {
      temp_button3 = 6;//Serial1.println("EN6!");
    }
    else 
      temp_button3 = 0;
    if(temp_button != button_value || temp_button2 != button_value2 || temp_button3 != button_value3 || temp_button4 != button_value4) {
        button_value = temp_button;
        button_value2 = temp_button2;
        button_value3 = temp_button3;
        button_value4 = temp_button4;
        button_change = true;
    }
    
    if (t == 25) {
        digitalWrite(BOARD_LED_PIN, LOW); 
    } 
    if (t == 150) {
        digitalWrite(BOARD_LED_PIN, HIGH); 
        t = 0;
    }
}

void limit_calculate()
{
    unsigned int i,j;
    for(i = 0; i < 10; i ++) {
        max_Value[i] = 0;
        min_Value[i] = 1024;
    }
    for(i = 0; i < 200; i ++) {
         for (j = 0; j < 10; j ++) {
              temp_Value[j] = analogRead(L_R[j]);
              max_Value[j] = max(temp_Value[j], max_Value[j]);
              min_Value[j] = min(temp_Value[j], min_Value[j]);
         }
         delay(50);
    }
}

void Serial_process()
{
  static unsigned int ptr=0;
  if(Serial.available())
  {
    redata[ptr] = (char)Serial.read();
    ptr++;
  } else if (Serial1.available()) {
      redata[ptr] = Serial1.read();
      ptr++;     
  }
  if(ptr>99)
    ptr=0;
}

static int fadevalue = 0;
boolean fadedirection = 1;
void Chest_LED_Fading()
{
   if( fadevalue >= 255)
    fadevalue = 0;
    if (fadedirection == 1)
   fadevalue += breathLED;
   analogWrite(Chest_LED, fadevalue);
   
}
