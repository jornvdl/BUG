# -*- coding: utf-8 -*-
"""
Created on Mon Nov  8 14:32:42 2021

@author: Jorn van der Linden
"""

# SPDX-FileCopyrightText: 2020 ladyada for Adafruit Industries
# SPDX-License-Identifier: MIT

# This example scans for any BLE advertisements and prints one advertisement and one scan response
# from every device found. This scan is more detailed than the simple test because it includes
# specialty advertising types.

from adafruit_ble import BLERadio

from adafruit_ble.advertising import Advertisement
from adafruit_ble.advertising.standard import ProvideServicesAdvertisement
import time

padname = "GAMERBUG"

ble = BLERadio()
print("scanning for BUGs")
found = set()
scan_responses = set()
gamepads = set()

# By providing Advertisement as well we include everything, not just specific advertisements.
for advertisement in ble.start_scan(ProvideServicesAdvertisement, Advertisement, timeout=5):
    addr = advertisement.address
    if advertisement.scan_response and addr not in scan_responses:
        scan_responses.add(addr)
    elif not advertisement.scan_response and addr not in found:
        found.add(addr)
        if advertisement.complete_name == padname:
            gamepads.add(advertisement)
    else:
        continue

print("scan done")

for bug in gamepads:
    print (bug)
    ble.connect(bug)

while len(ble.connections) > 0:
    print ("Connected to at least one BUG!")
    time.sleep(2)