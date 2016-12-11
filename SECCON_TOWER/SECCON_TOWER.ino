#include <Servo.h> 
 
Servo servoC;
Servo servoL;
Servo servoR;

void setSemaphorePosition(int c, int l, int r)
{
  int angleC[] = { 45, 86, 131, 180 };
  int angleL[] = { 20, 92, 170 };
  int angleR[] = { 20, 85, 160 };

  servoC.write(angleC[c]);
  servoL.write(angleL[l]);
  servoR.write(angleR[r]);
}
 
void setup() {
  Serial.begin(9600);
  servoC.attach(9);
  servoL.attach(10);
  servoR.attach(11);

  setSemaphorePosition(2, 1, 1);
/*
  setSemaphorePosition(0, 0, 0);
  delay(5000);
  setSemaphorePosition(0, 1, 1);
  delay(5000);
  setSemaphorePosition(0, 2, 2);
  delay(5000);
//  while (1) ;
*/
}

void loop() {
  int lastIndex = -1;

  while (1) {

    while (!Serial.available());
    
    char ch = Serial.read(); // serial input
    Serial.println(ch);

    if (ch >= 'a' && ch <= 'z') ch = ch - 'a' + 'A';
    if (ch == '.') ch = '9';


    int index = String("ABCDEFGHIKLMNOPQRSTUVWXYZJ1234567890").indexOf(ch);
    int tableL[] = { 0, 2, 2, 0, 0, 1, 1, 2, 1 };
    int tableR[] = { 2, 0, 2, 0, 1, 0, 2, 1, 1 };

    if (index < 0) {
      Serial.println(ch);
      // unknown letter; ignore
      lastIndex = -1;
      continue;
    }

    int c = index % 4;
    int l = tableL[index / 4];
    int r = tableR[index / 4];

    if (lastIndex >= 0 && index == lastIndex) {
      // repeated; set neutral position once
      setSemaphorePosition(2, 1, 1);
      delay(200);
      setSemaphorePosition(c, l, r);
      delay(800);
    } else {
      //delay(200);
      setSemaphorePosition(c, l, r);
      delay(1000);
    }

    lastIndex = index;
  }
}

