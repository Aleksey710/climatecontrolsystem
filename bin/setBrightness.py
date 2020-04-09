#!/usr/bin/python
# -*- coding: utf-8 -*-

#import wiringpi

# GPIO pin 12 = BCM pin 18 = wiringpi pin 1
#led_pin  = 1

#wiringpi.wiringPiSetup()
#wiringpi.pinMode(led_pin, 2)
#wiringpi.pwmWrite(led_pin, 0)

#def led(led_value):
#    wiringpi.pwmWrite(led_pin, led_value)

# значение должно быть от 0 до 1024
#led(512)

import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setup(12, GPIO.OUT)

p = GPIO.PWM(12, 1000)
p.start(1)
input('Press return to stop:')   # use raw_input for Python 2

try:
    while 1:
        for dc in range(0, 101, 5):
            p.ChangeDutyCycle(dc)
            time.sleep(0.1)
        for dc in range(100, -1, -5):
            p.ChangeDutyCycle(dc)
            time.sleep(0.1)
except KeyboardInterrupt:
    pass


p.stop()
GPIO.cleanup()


