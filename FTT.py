#coding:utf-8
import sys
import wave
import numpy as np
from scipy import fftpack
import pyaudio
import serial

wf = wave.open("output.wav" , "r" )
fs = wf.getframerate()  # サンプリング周波数

FORMAT = pyaudio.paInt16
start = 0    # サンプリングする開始位置
CHUNK = 1024
N = 12      # FFTのサンプル数
amplitudeSpectrum = ''
ser = serial.Serial("/dev/tty.usbmodem1411", 9600)  # Ledcobe

p = pyaudio.PyAudio()
stream = p.open(format = p.get_format_from_width(wf.getsampwidth()),
                channels=wf.getnchannels(),
                rate=fs,
                output=True,
                frames_per_buffer = CHUNK)

hammingWindow = np.hamming(N)
freqList = fftpack.fftfreq(N, d=1.0/fs)  # 周波数軸の値を計算

def update(x):
    global amplitudeSpectrum
    windowedData =  hammingWindow * x[start:start+N]  # 切り出した波形データ（窓関数あり）
    X = fftpack.fft(windowedData)  # FFT

    pidxs = np.where(freqList > 0)
    amplitudeSpectrum = np.abs(X)[pidxs]  # 振幅スペクトル
    freqs = freqList[pidxs]



def loop():
        try:
            data = wf.readframes(CHUNK)
            while data != '':
                x = np.array(data)
                stream.write(data)
                x = np.frombuffer(x, dtype= "int32") / 32768.0 ** 2
                update(x)
                np.log2(amplitudeSpectrum)
                a = amplitudeSpectrum[0:5] * 10
                a[np.where(a > 6)] = 5
                ser.write("H".encode('utf-8'))
                print(str(a.astype(np.int32)))
                ser.write(str(a[0].astype(np.int32)).encode('utf-8'))
                ser.write(str(a[1].astype(np.int32)).encode('utf-8'))
                ser.write(str(a[2].astype(np.int32)).encode('utf-8'))
                ser.write(str(a[3].astype(np.int32)).encode('utf-8'))
                ser.write(str(a[4].astype(np.int32)).encode('utf-8'))
                data = wf.readframes(CHUNK)

        except KeyboardInterrupt:
            wf.close()
            p.close()

        print("End...")

loop()
