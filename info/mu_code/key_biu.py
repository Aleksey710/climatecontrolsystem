# !/usr/bin/python
# -*- coding: utf-8 -*-
#
import RPi.GPIO as GPIO                     # Импортируем библиотеку по работе с GPIO
import time                                 # Импортируем библиотеку для работы со временем




KEY_F1 = 5
KEY_F2 = 6
KEY_F3 = 13
KEY_F4 = 19
KEY_OFF = 26

GPIO.setmode(GPIO.BCM)

GPIO.setup(KEY_F1, GPIO.IN) #, pull_up_down=GPIO.PUD_UP)
GPIO.setup(KEY_F2, GPIO.IN) #, pull_up_down=GPIO.PUD_UP)
GPIO.setup(KEY_F3, GPIO.IN) #, pull_up_down=GPIO.PUD_UP)
GPIO.setup(KEY_F4, GPIO.IN) #, pull_up_down=GPIO.PUD_UP)
GPIO.setup(KEY_OFF, GPIO.IN) #, pull_up_down=GPIO.PUD_UP)

print ("Доброго дня! Це програма перевiрки роботи кнопок БІУ")

try:
    while True:
        if GPIO.input(KEY_F1) == False:
            time.sleep(1)
            print ("F1 натиснута.")

        if GPIO.input(KEY_F2) == False:
            time.sleep(1)
            print ("F2 натиснута.")

        if GPIO.input(KEY_F3) == False:
            time.sleep(1)
            print ("F3 натиснута.")

        if GPIO.input(KEY_F4) == False:
            time.sleep(1)
            print ("F4 натиснута.")

        if GPIO.input(KEY_OFF) == False:
            time.sleep(1)
            print ("OFF натиснута.")


except KeyboardInterrupt:
    GPIO.cleanup()