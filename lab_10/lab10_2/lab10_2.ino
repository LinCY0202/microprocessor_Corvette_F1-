#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
static int num;
#define LATCH_DIO D15   
#define CLK_DIO D14
#define DATA_DIO D2

/* Segment byte maps for numbers 0 to 9*/
const byte SEGMENT_MAP[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0X7F,0X6F};
/* Byte maps to select digit 0 to 3 */
const byte SEGMENT_SELECT[] = {0xFE,0xFD,0xFB,0xF7};

void WriteNumberToSegment(byte Segment, byte Value){
  digitalWrite(LATCH_DIO,LOW);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
  digitalWrite(LATCH_DIO,HIGH);
}
void setup(){
  pinMode(BT1, INPUT_PULLUP); // 設定D1(INT0)為輸入有提升電阻
  attachInterrupt(BT1, BT1_isr_routine, FALLING); // 致能外部中斷腳、函數及負緣
  pinMode(BT2, INPUT_PULLUP); // 設定D2(INT1)為輸入有提升電阻
  attachInterrupt(BT2, BT2_isr_routine, FALLING); // 致能外部中斷腳、函數及負緣
  pinMode(BT3, INPUT_PULLUP); // 設定D3(INT2)為輸入有提升電阻
  attachInterrupt(BT3, BT3_isr_routine, FALLING); // 致能外部中斷腳、函數及負緣
  pinMode(BT4, INPUT_PULLUP); // 設定D4(INT3)為輸入有提升電阻
  attachInterrupt(BT4, BT4_isr_routine, FALLING); // 致能外部中斷腳、函數及負緣
  lcd.begin(16, 2);
  pinMode(LATCH_DIO,OUTPUT);
  pinMode(CLK_DIO,OUTPUT);
  pinMode(DATA_DIO,OUTPUT);
  num = 0;
}

void loop(){
  lcd.setCursor(0, 0);
  lcd.print(num++); 
  delay(1000); 
}
void BT1_isr_routine(){
  unsigned int dly;
  noInterrupts(); // 停止中斷
  dly = 5000;
  while (dly--); // 延時，防止機械彈跳
  while (!digitalRead(BT1)); // 等待放開鍵
  dly = 5000;
  while (dly--); // 延時，防止機械彈跳
  WriteNumberToSegment(3 , 1);
  interrupts(); // 恢復中斷
}
void BT2_isr_routine(){
  unsigned int dly;
  noInterrupts(); // 停止中斷
  dly = 5000;
  while (dly--); // 延時，防止機械彈跳
  while (!digitalRead(BT2)); // 等待放開鍵
  dly = 5000;
  while (dly--); // 延時，防止機械彈跳
  WriteNumberToSegment(3 , 2);
  interrupts(); // 恢復中斷
}
void BT3_isr_routine(){
  unsigned int dly;
  noInterrupts(); // 停止中斷
  dly = 5000;
  while (dly--); // 延時，防止機械彈跳
  while (!digitalRead(BT3)); // 等待放開鍵
  dly = 5000;
  while (dly--); // 延時，防止機械彈跳
  WriteNumberToSegment(3 , 3);
  interrupts(); // 恢復中斷
}
void BT4_isr_routine(){
  unsigned int dly;
  noInterrupts(); // 停止中斷
  dly = 5000;
  while (dly--); // 延時，防止機械彈跳
  while (!digitalRead(BT4)); // 等待放開鍵
  dly = 5000;
  while (dly--); // 延時，防止機械彈跳
  WriteNumberToSegment(3 , 4);
  interrupts(); // 恢復中斷
}
