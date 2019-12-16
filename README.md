# ClimateСontrolSystem

Система управления климатом пассажирского вагона с комплексом EB32-01


#1. Rasbery Pi 3 Model B+

https://www.raspberrypi.org/downloads/raspbian/
Raspbian Buster with desktop

#2. Настройка 7inch_HDMI_LCD_(B)

https://www.waveshare.com/wiki/7inch_HDMI_LCD_(B)
Working with Raspberry Pi
Turn on the "backlight" switch then connect the LCD to your Pi 
(HDMI Port of LCD -> HDMI Port of Pi; USB Port of LCD -> USB Port of Pi; 5V~2A power supply). 
Download the Raspbian image from Raspberry Pi web site. 
Write the image to a TF card and append the following lines to the config.txt file which is located in the root of your TF card:

max_usb_current=1
hdmi_group=2
hdmi_mode=87
hdmi_cvt 800 480 60 6 0 0 0
hdmi_drive=1
If you use the LCD with Raspberry Pi 4B, you need to remove line dtoverlay=vc4-fkms-V3D from config.txt file

You must make sure that there are no spaces on either side of the equal sign.
Save and connect the TF card to your Pi then power up.
(Touch input working well means that the LED firmware is Rev2.1. If the LCD firmware is 1.1, see #About LCD revision)
Note: Resolution of Ubuntu Mate OS or Windows 10 IoT Core OS can also be set properly by editing config.txt.

Описание настроек
http://wikihandbk.com/wiki/Raspberry_Pi:%D0%9D%D0%B0%D1%81%D1%82%D1%80%D0%BE%D0%B9%D0%BA%D0%B0/config.txt#.D0.9E.D0.BF.D1.86.D0.B8.D0.B8_.D0.B4.D0.BB.D1.8F_.D1.80.D0.B5.D0.B6.D0.B8.D0.BC.D0.B0_HDMI



