import RPi.GPIO as GPIO
import time
LedPin = 11
def setup():
	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(LedPin, GPIO.OUT)
	GPIO.output(LedPin, GPIO.HIGH)
def loop():
	while True:
		print("...led on")
		GPIO.output(LedPin, GPIO.LOW)
		time.sleep(0.5)
		print("led off...")
		GPIO.output(LedPin, GPIO.HIGH)
		time.sleep(0.5)
def destroy():
	GPIO.output(LedPin, GPIO.HIGH)
	GPIO.cleanup()
if__name__ == '__main__':
	setup()
	try:
		loop()
	except Keyboardinterrupt:
		destroy()
