# hw2
* void analy()產生sawtooth waveform
>將週期T分十份時間，前3份時間上升，後三份時間下降
>>因為波峰要在3，又D7會乘3.3V，所以讓i加至0.9 (3/3.3V=0.9)， 再降下
>>>因為sleepfor不能<1ms，所以用wait_us(單位為μs)

```C++
    for (float i = 0.0f; i < 0.9f; i += 0.45f) {
      aout = i;
      wait_us(T/10*1000000);
    }
    for (float i=0.9f; i > 0.0f; i -= 0.15f) {
      aout = i;
      wait_us(T/10*1000000);
    }
```
* void samp()sample值
>每sample分之一秒讀取一個通過濾波器的波(Ain)的值存起
```c++
  for (int k = 0; k < sample; k++){
    ADCdata[k] = Ain;
    ThisThread::sleep_for(1000ms/sample);
  }
```
int main()
>讀按鈕值，print menu是要一直做的，所以寫在無窮回圈內
```C++
  while(1)
```
 * 讀取按鍵的狀態
```C++
    bs1 = bup.read();
    bs2 = bdn.read();
    bs3 = bst.read();
```
* 建menu，選頻率
>算按了幾次，跳至相對case(以case1為例)
```c++
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
      .
      .
      .
    }
  ```
* 若select，輸出相對頻率的波，並sample
>若先輸出波再sample，sample時已無波，所以須將analy和samp放至thread同時進行
>因為thread內不能print所以將print拉回main中
```C++
    if(bs3 == 1){
      thread.start(analy);
      thread.start(samp);
      for (int k = 0; k < sample; k++){
        printf("%f\r\n", ADCdata[k]);
      }
```
