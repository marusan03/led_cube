#define DATAPIN    (13)   // 74HC595のDSへ (オレンジ)
#define LATCHPIN  (11)  // 74HC595のST_CPへ (黄色)
#define CLOCKPIN  (12)  // 74HC595のSH_CPへ (緑)
#define LAYER 5
#define LINE 5
#define BIGIN 2 //ピンが始まる位置
byte cube[LAYER][LINE]; //LEDを光らせるためのデータ

//関数宣言
byte test();
void MyShiftOut(int bit, byte layerData[LINE]);
void setLed(byte cube[LAYER][LINE]);
void lightCube();

int TIME = 30;


//パターン
byte aaa[5][5] {
  {1, 0, 0, 0, 1},
  {1, 1, 0, 1, 1},
  {1, 0, 1, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1}
};

byte piano[9][5][5] {
  {
    {0, 1, 0, 1, 1}, //ド
    {0, 1, 0, 1, 1},
    {0, 1, 1, 1, 1},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0}
  },
  {
    {1, 0, 0, 0, 0}, //レ
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 0}
  },
  {
    {1, 1, 1, 1, 1}, //ミ
    {0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1}
  },
  {
    {1, 1, 1, 1, 1}, //ファ
    {0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 1},
    {1, 0, 0, 1, 0}
  },
  {
    {1, 0, 0, 0, 1}, //ソ
    {1, 0, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 0, 0}
  },
  {
    {1, 1, 1, 1, 1}, //ラ
    {0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1},
    {0, 1, 1, 1, 0}
  },
  {
    {1, 1, 0, 0, 1}, //シ
    {0, 0, 0, 0, 1},
    {1, 1, 0, 0, 1},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 0, 0}
  },
  {
    {1, 0, 0, 1, 1}, //ド
    {1, 0, 0, 1, 1},
    {1, 1, 1, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0}
  },
  {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
  }
};

// BGMあり
byte ledcube[6][LAYER][LINE]{
  {
    {0b00000,0b00000,0b00000,0b00000,0b00000}, //layer1
    {0b00000,0b00000,0b00000,0b00000,0b00000}, //layer2
    {0b00000,0b00000,0b00100,0b00000,0b00000}, //layer3
    {0b00000,0b00000,0b00000,0b00000,0b00000}, //layer4
    {0b00000,0b00000,0b00000,0b00000,0b00000}  //layer5
  },
  {
    {0b00000,0b00000,0b00000,0b00000,0b00000}, //layer1
    {0b00000,0b00000,0b00100,0b00000,0b00000}, //layer2
    {0b00000,0b00100,0b01010,0b00100,0b00000}, //layer3
    {0b00000,0b00000,0b00100,0b00000,0b00000}, //layer4
    {0b00000,0b00000,0b00000,0b00000,0b00000}  //layer5
  },
  {
    {0b00000,0b00000,0b00000,0b00000,0b00000}, //layer1
    {0b00000,0b01110,0b01110,0b01110,0b00000}, //layer2
    {0b00000,0b01110,0b01010,0b01110,0b00000}, //layer3
    {0b00000,0b01110,0b01110,0b01110,0b00000}, //layer4
    {0b00000,0b00000,0b00000,0b00000,0b00000}  //layer5
  },
  {
    {0b00000,0b00000,0b00100,0b00000,0b00000}, //layer1
    {0b00000,0b01110,0b01010,0b01110,0b00000}, //layer2
    {0b00100,0b01010,0b10001,0b01010,0b00100}, //layer3
    {0b00000,0b01110,0b01010,0b01110,0b00000}, //layer4
    {0b00000,0b00000,0b00100,0b00000,0b00000}  //layer5
  },
  {
    {0b00000,0b01110,0b01110,0b01110,0b00000}, //layer1
    {0b01110,0b10001,0b10001,0b10001,0b01110}, //layer2
    {0b01110,0b10001,0b10001,0b10001,0b01110}, //layer3
    {0b01110,0b10001,0b10001,0b10001,0b01110}, //layer4
    {0b00000,0b01110,0b01110,0b01110,0b00000}  //layer5
  },
  {
    {0b11111,0b11111,0b11111,0b11111,0b11111}, //layer1
    {0b11111,0b10001,0b10001,0b10001,0b11111}, //layer2
    {0b11111,0b10001,0b10001,0b10001,0b11111}, //layer3
    {0b11111,0b10001,0b10001,0b10001,0b11111}, //layer4
    {0b11111,0b11111,0b11111,0b11111,0b11111}  //layer5
  }
};

void setup() {
  Serial.begin(9600); //シリアル通信をON
  Serial.setTimeout(15000UL); // タイムアウト設定（15秒）
  pinMode(DATAPIN, OUTPUT);
  pinMode(LATCHPIN, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
  for (int i = BIGIN; i - BIGIN < LAYER; i++) {
    pinMode(i, OUTPUT);
  }
  setLedoff(cube); //初期化
}

void loop() {
  //LEDのパターンをセット
  setLedPiano(cube); //2ピアノ
  //setLedBGM(cube); //1-1
  //setLedWeve(cube); //1-2
  //setLedon(cube);
  //LEDを光らせる処理
  lightCube();
}

void MyShiftOut(byte layerData[LINE]) {
  for ( int i = 0; i < LAYER; i++) {
    for (int j = 0; j < LINE; j++) {
      digitalWrite(DATAPIN, !(((int)layerData[i] >> j) & 1));
      digitalWrite(CLOCKPIN, HIGH);
      digitalWrite(CLOCKPIN, LOW);
    }
  }
}

// これは変更しなくて良い
void lightCube() {
  for (int a = 0; a < TIME; a++) {
    for (int i = 0; i < LAYER; i++) {
      digitalWrite(i + BIGIN, HIGH);
      digitalWrite(LATCHPIN, LOW);    // 送信中はLATCHPINをLOWに
      // シフト演算を使って点灯するLEDを選択しています
      MyShiftOut(cube[i]);
      digitalWrite(LATCHPIN, HIGH);   // 送信後はLATCHPINをHIGHに戻す
      digitalWrite(i + BIGIN, LOW);
    }
  }
}

//全てをON
void setLedon(byte cube[LAYER][LINE]) {
  for (int i = 0; i < LAYER; i++) {
    for (int j = 0; j < LINE; j++) {
      cube[i][j] = 0x1F;
    }
  }
}

//全てをOFF
void setLedoff(byte cube[LAYER][LINE]) {
  for (int i = 0; i < LAYER; i++) {
    for (int j = 0; j < LINE; j++) {
      cube[i][j] = 0x00;
    }
  }
}

//全体をrandamにセット
void setLed(byte cube[LAYER][LINE]) {
  for (int i = 0; i < LAYER; i++) {
    /*音楽データを入力*/
    for (int j = 0; j < LINE; j++) {
      cube[i][j] = random(256);
    }
  }
}

//レイヤーをシフトしつつランダムにセット
void setLed2(byte cube[LAYER][LINE]) {
  for (int i = 0; i < LAYER; i++) {
    for (int j = 0; j < LINE; j++) {
      cube[i][j] = (((cube[i][j] << 1) + random(2)) & 0x1F);
    }
  }
}

//パターンを入力するときのサンプル
void setLed3(byte cube[LAYER][LINE]) {
  for (int i = 0; i < LAYER; i++) {
    for (int j = 0; j < LINE; j++) {
      cube[i][j] = (((cube[i][j] << 1) + aaa[i][j]) & 0x1F);
    }
  }
}

//テスト
void setLed4(byte cube[LAYER][LINE]) {
  for (int i = 0; i < LAYER; i++) {
    cube[i][0] = Serial.read() - 0x61;
  }
}

//ピアノ
void setLedPiano(byte cube[LAYER][LINE]) {
  TIME = 30;
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
  for (int i = 0; i < LAYER; i++) {
    for (int j = 0; j < LINE; j++) {
      cube[i][j] = (((cube[i][j] << 1) + piano[code][i][j]) & 0x1F);
    }
  }
}

void setLedBGM(byte cube[LAYER][LINE]) {
  char input = Serial.read();
  TIME = 15;
  switch (input) {
    case '0':
      for(int i = 0;i < LAYER;i++){
        for(int j = 0; j < LINE;j++){
          cube[i][j] = ledcube[0][i][j];
        }
      } 
      break;
    case '1':
      for(int i = 0;i < LAYER;i++){
        for(int j = 0; j < LINE;j++){
          cube[i][j] = ledcube[1][i][j];
        }
      } 
      break;
    case '2':
      for(int i = 0;i < LAYER;i++){
        for(int j = 0; j < LINE;j++){
          cube[i][j] = ledcube[2][i][j];
        }
      } 
      break;
    case '3':
      for(int i = 0;i < LAYER;i++){
        for(int j = 0; j < LINE;j++){
          cube[i][j] = ledcube[3][i][j];
        }
      } 
      break;
    case '4':
      for(int i = 0;i < LAYER;i++){
        for(int j = 0; j < LINE;j++){
          cube[i][j] = ledcube[4][i][j];
        }
      } 
      break;
    case '5':
      for(int i = 0;i < LAYER;i++){
        for(int j = 0; j < LINE;j++){
          cube[i][j] = ledcube[5][i][j];
        }
      } 
      break;
    default:
      break;
  }
}


void setLedWeve(byte cube[LAYER][LINE]){
  byte wave[5][5];
  int layer[5];
  int input;

  TIME = 12;
  
if ( Serial.available() >= 6 ) {
    // ヘッダの確認
    if ( Serial.read() == 'H' ) {
      for(int i = 0; i < LAYER; i++){
        layer[i] = Serial.read() - 0x30;
        Serial.print(layer[i]);
      }      
    }
  }else{
    for(int i = 0; i < LAYER; i++){
        layer[i] = 0;
      }
  }
  for (int i = 0; i < LAYER; i++) {
    for (int j = 0; j < LINE; j++) {
      if(layer[j] == (LAYER - i)){
        wave[i][j] = 1;
      }else{
        wave[i][j] = 0;
      }
    }
  }
  for (int i = 0; i < LAYER; i++) {
    for (int j = 0; j < LINE; j++) {
      if(wave[i][j] == 1){
        for (int k = i; k < LAYER; k++) {
          wave[k][j] = 1;
        }
      }
    }
  }

  
  for (int i = 0; i < LAYER; i++) {
    for (int j = 0; j < LINE; j++) {
      cube[i][j] = (((cube[i][j] << 1) + wave[i][j]) & 0x1F);
    }
  }
  
}


