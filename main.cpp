// uLCD-144-G2 basic text demo program for uLCD-4GL LCD driver library
//
#include "mbed.h"
#include "uLCD_4DGL.h"


DigitalIn bup(D8);
DigitalIn bdn(D9);
DigitalIn bst(D10);
uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

AnalogOut aout(PA_4);
AnalogIn Ain(A0);
Thread thread;
int sample = 10000;
float ADCdata[10000];
int f;

void analy()
{
  float T=1/f;
  while (1)
  {
      // change the voltage on the digital output pin by 0.1 * VCC
      //  and print what the measured voltage should be (assuming VCC = 3.3v)
    for (float i = 0.0f; i < 0.9f; i += 0.45f) {
      aout = i;
            //printf("aout = %f volts\n", aout.read() * 3.3f);
      wait_us(T/10*1000000);
    }
    for (float i=0.9f; i > 0.0f; i -= 0.15f) {
      aout = i;
            //printf("aout = %f volts\n", aout.read() * 3.3f);
      wait_us(T/10*1000000);
    }
  }
}
void samp()
{
  for (int k = 0; k < sample; k++){
    ADCdata[k] = Ain;
    ThisThread::sleep_for(1000ms/sample);
  }
}
int main()
{
  int bs1,bs2,bs3;
  int count=1;
  while(1){
    bs1 = bup.read();  //讀取按鍵的狀態
    bs2 = bdn.read();
    bs3 = bst.read();

    if(bs1 == 1){  
      count++;
    }else if(bs2 == 1){       
      count--;
    }
    switch(count%6)
    {
      case 1:
        uLCD.locate(0,0);
        uLCD.color(RED);
        uLCD.printf("\nHf=90 Hz\n");
        uLCD.color(GREEN);
        uLCD.printf("\nf=100 Hz\n");
        uLCD.printf("\nf=200 Hz\n");
        uLCD.printf("\nf=300 Hz\n");
        uLCD.printf("\nf=400 Hz\n");

        uLCD.printf("\nf=500 Hz\n");
        f = 90;
        break;
      case 2:
        uLCD.locate(1,0);
        uLCD.color(GREEN);
        uLCD.printf("\nf=90 Hz\n");
        uLCD.color(RED);
        uLCD.printf("\nf=100 Hz\n");
        uLCD.color(GREEN);
        uLCD.printf("\nf=200 Hz\n");
        uLCD.printf("\nf=300 Hz\n");
        uLCD.printf("\nf=400 Hz\n");
        uLCD.printf("\nf=500 Hz\n");
        f = 100;
        break;
      case 3:
        uLCD.locate(2,0);
        uLCD.color(GREEN);
        uLCD.printf("\nf=90 Hz\n");
        uLCD.printf("\nf=100 Hz\n");
        uLCD.color(RED);
        uLCD.printf("\nf=200 Hz\n");
        uLCD.color(GREEN);
        uLCD.printf("\nf=300 Hz\n");
        uLCD.printf("\nf=400 Hz\n");
        uLCD.printf("\nf=500 Hz\n");
        f = 200;
        break;
      case 4:
        uLCD.locate(3,0);
        uLCD.color(GREEN);
        uLCD.printf("\nf=90 Hz\n");
        uLCD.printf("\nf=100 Hz\n");
        uLCD.printf("\nf=200 Hz\n");
        uLCD.color(RED);
        uLCD.printf("\nf=300 Hz\n");
        uLCD.color(GREEN);
        uLCD.printf("\nf=400 Hz\n");
        uLCD.printf("\nf=500 Hz\n");
        f = 300;
        break;
      case 5:
        uLCD.locate(4,0);
        uLCD.color(GREEN);
        uLCD.printf("\nf=90 Hz\n");
        uLCD.printf("\nf=100 Hz\n");
        uLCD.printf("\nf=200 Hz\n");
        uLCD.printf("\nf=300 Hz\n");
        uLCD.color(RED);
        uLCD.printf("\nf=400 Hz\n");
        uLCD.color(GREEN);
        uLCD.printf("\nf=500 Hz\n");
        f = 400;
        break;
      case 6:
        f = 500;
        uLCD.locate(5,0);
        uLCD.color(GREEN);
        uLCD.printf("\nf=90 Hz\n");
        uLCD.printf("\nf=100 Hz\n");
        uLCD.printf("\nf=200 Hz\n");
        uLCD.printf("\nf=300 Hz\n");
        uLCD.printf("\nf=400 Hz\n");
        uLCD.color(RED);
        uLCD.printf("\nf=500 Hz\n");
        break;
    }
  //  uLCD.printf("f=%d",f);
    if(bs3 == 1){
      thread.start(analy);
      thread.start(samp);
      for (int k = 0; k < sample; k++){
        printf("%f\r\n", ADCdata[k]);
      }
    }
  }
}