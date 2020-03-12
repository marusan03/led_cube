# -*- coding: utf-8 -*-

#coding: utf-8
import wave
import pyaudio
import serial

if __name__ == '__main__':
    ser = serial.Serial("/dev/tty.usbmodem1411", 9600)  # Ledcobe
    wf = wave.open("output.wav", "r")

    sw = wf.getsampwidth() * 128 / 6

    # ストリームを開く
    p = pyaudio.PyAudio()
    stream = p.open(format=p.get_format_from_width(wf.getsampwidth()),
                    channels=wf.getnchannels(),
                    rate=wf.getframerate(),
                    output=True)

    # チャンク単位でストリームに出力し音声を再生
    chunk = 512
    data = wf.readframes(chunk)
    while data != '':
        a = data[0]
        stream.write(data)
        if a < sw:
            ser.write("0".encode('utf-8'))
        elif a < sw * 2:
            ser.write("1".encode('utf-8'))
        elif a < sw * 3:
            ser.write("2".encode('utf-8'))
        elif a < sw * 4:
            ser.write("3".encode('utf-8'))
        elif a < sw * 5:
            ser.write("4".encode('utf-8'))
        elif a <= sw * 6:
            ser.write("5".encode('utf-8'))
        else:
            print(str(a)+":"+str(sw))
        data = wf.readframes(chunk)
    stream.close()
    p.terminate()
