# -*- coding: utf-8 -*-
"""
Created on Wed Sep 29 21:31:17 2021

@author: Jorn
"""

import keyboard
import serial

serialPort = serial.Serial("COM11", 9600, timeout=2)

#serialPort.open()

btns = [1,1,1,1]

serialPort.read_all()

try:
    while(1):
        if(serialPort.in_waiting>0):
            serialString = serialPort.readline()
            btns = serialString.decode('Ascii').split(",")
            btns[3] = btns[3][0]
    
        if "0" in btns:
            keyboard.send('space')
        else:
            keyboard.release('space')
            
except KeyboardInterrupt:
    serialPort.close()
    print("Serial port closed")
