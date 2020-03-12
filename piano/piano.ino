//***************************************/
// シンプル楽器ガジェットプログラム
//***************************************/
int s = 0;
int speaker = 13;
int sounds[] = {262, 294, 330, 349, 392, 440, 494};
int BEATTIME = 100;
void setup() {
  Serial.begin(9600);
}
void loop() {
  //一度音をリセット
  noTone(12);
  int code;
  char input = Serial.read();
  switch (input) {
    case 'a':
      code = 0;
      break;
    case 's':
      code = 1;
      break;
    case 'd':
      code = 2;
      break;
    case 'f':
      code = 3;
      break;
    case 'j':
      code = 4;
      break;
    case 'k':
      code = 5;
      break;
    case 'l':
      code = 6;
      break;
    case ';':
      code = 7;
      break;
    default:
      code = 8;
  }
  if(code != 8){
    tone(speaker, sounds[code], BEATTIME);
  }
  delay(100);
}
