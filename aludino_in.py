# -*- coding: utf-8 -*-
# Arduinoと通信するためのクラス
#
import serial
from getch import getch, pause

class aludino(object):
    def __init__(self):
        self.ser1 = serial.Serial("/dev/tty.usbmodem1411", 9600) #Ledcobe
        self.ser2 = serial.Serial("/dev/tty.usbmodem1421", 9600) #スピーカー



    def input(self):
        self.in_data = getch()
        if(self.in_data == "q"): # qを入力したら終了
            exit()

        print("入力完了")
        self.ser1.write(self.in_data.encode('utf-8'))
        self.ser2.write(self.in_data.encode('utf-8'))
        return self.in_data

if __name__ == "__main__":
    a = aludino()
    while True:
        a.input()
