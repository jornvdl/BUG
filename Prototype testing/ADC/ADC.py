# -*- coding: utf-8 -*-
"""
Created on Wed Nov 10 09:39:22 2021

@author: floris van der Heijde
"""

import serial
import csv  #  https://www.pythontutorial.net/python-basics/python-write-csv-file/
from datetime import datetime   #https://thispointer.com/python-how-to-get-current-date-and-time-or-timestamp/
import os
import time

serialPort = serial.Serial("COM8", 115200, timeout=2)

header = ["timestamp", "ADC value"]

#serialPort.open()


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
            #btn = int(serialString.decode('Ascii').split(",")[0])
            timestamp = datetime.now()
            timestampStr = timestamp.strftime("%H:%M:%S")
            writer.writerow(["\""+timestampStr+"\"", serialString])
            time.sleep(0.1)
            
            
except KeyboardInterrupt: 
    serialPort.close()
    f.close()
    print("Serial port closed, csv saved.")
