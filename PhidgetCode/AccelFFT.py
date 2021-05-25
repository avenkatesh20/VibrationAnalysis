from scipy.fftpack import fft, ifft, fftfreq
import numpy as np
import matplotlib.pyplot as plt
import statistics as stat
import warnings

#global variables
x = []
y = []
z = []
time = []

def getPhidgetData():
    global x, y, z, time
    phidget_data_file = open("phidgetdata.txt")
    data = phidget_data_file.read().split(',');
    x = np.array(data[::4])
    x = [x for x in x if x]
    x = np.asfarray(x,float)
    y = data[1::4]
    y = [y for y in y if y]
    y = np.asfarray(y,float)
    z = data[2::4]
    z = [z for z in z if z]
    z = np.asfarray(z,float)
    time = data[3::4]
    time = [time for time in time if time]
    time = np.asfarray(time,float)

    #Plotting Waveforms
    plt.figure()
    plt.title("X vs time Waveform")
    plt.xlabel("Time (s)")
    plt.ylabel("Amplitude (m/s^2)")
    plt.plot(time, x)
    plt.savefig("X Waveform")

    plt.figure()
    plt.title("Y vs time Waveform")
    plt.xlabel("Time (s)")
    plt.ylabel("Amplitude (m/s^2)")
    plt.plot(time, y)
    plt.savefig("Y Waveform")

    plt.figure()
    plt.title("Z vs time Waveform")
    plt.xlabel("Time (s)")
    plt.ylabel("Amplitude (m/s^2)")
    plt.plot(time, z)
    plt.savefig("Z Waveform")

def FastFourierTrans():
    global x, y, z, time
    xFFT = fft(x)
    freq_xFFT = fftfreq(len(xFFT)) * (1/(stat.mean(time)))
    plt.figure()
    plt.title("FFT of X Waveform")
    plt.yscale('log')
    plt.xlabel("Frequencies (Hz)")
    plt.ylabel("Amplitude (m/s^2)")
    plt.plot(freq_xFFT, xFFT)
    plt.savefig("X FFT")
    #plt.show()


    yFFT = fft(y)
    freq_yFFT = fftfreq(len(yFFT)) * (1/(stat.mean(time)))
    plt.figure()
    plt.title("FFT of Y Waveform")
    plt.yscale('log')
    plt.xlabel("Frequencies (Hz)")
    plt.ylabel("Amplitude (m/s^2)")
    plt.plot(freq_yFFT, yFFT)
    plt.savefig("Y FFT")
    #plt.show()

    zFFT = fft(z)
    freq_zFFT = fftfreq(len(zFFT)) * (1/(stat.mean(time)))
    plt.figure()
    plt.title("FFT of Z Waveform")
    plt.yscale('log')
    plt.xlabel("Frequencies (Hz)")
    plt.ylabel("Amplitude (m/s^2)")
    plt.plot(freq_zFFT, zFFT)
    plt.savefig("Z FFT")
    #plt.show()



#main
warnings.filterwarnings('ignore')
getPhidgetData()
FastFourierTrans()
