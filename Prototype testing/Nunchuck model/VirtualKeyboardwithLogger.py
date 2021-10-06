# -*- coding: utf-8 -*-
"""
Created on Wed Sep 29 21:31:17 2021

@author: Jorn
"""

import keyboard
import serial
import csv  #  https://www.pythontutorial.net/python-basics/python-write-csv-file/
from datetime import datetime   #https://thispointer.com/python-how-to-get-current-date-and-time-or-timestamp/
import os

serialPort = serial.Serial("COM4", 38400, timeout=2)

header = ["timestamp", "button"]

#serialPort.open()

btn = 0

timestamp = datetime.now()
timestampStr = timestamp.strftime("%Y%m%d-%H%M%S")

f = open(os.path.dirname(os.path.realpath(__file__))+'/'+timestampStr+'.csv', 'w', newline='')
writer = csv.writer(f)

writer.writerow(['time','button'])

serialPort.read_all()

print("Logger and keyboard emulator started. Quit with Ctrl+C to close COM-port")

try:
    while(1):
        
        # infinite loop to check incoming data on serial port. Convert to int
        if(serialPort.in_waiting>0):
            serialString = serialPort.readline()
            btn = int(serialString.decode('Ascii').split(",")[0])
            
            # If released, release space. If pressed, press space and log button number
            if (btn == 0):
                keyboard.release('space')
            else:
                keyboard.press('space')
                timestamp = datetime.now()
                timestampStr = timestamp.strftime("%H:%M:%S")
                writer.writerow(["\""+timestampStr+"\"", btn])
                
except KeyboardInterrupt: 
    serialPort.close()
    f.close()
    print("Serial port closed, csv saved.")
