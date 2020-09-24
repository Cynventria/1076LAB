import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
LED_PIN = 12
GPIO.setup(LED_PIN, GPIO.OUT)

while True:
    for i in xrange(0, 1):
        print('on')
        GPIO.output(LED_PIN, GPIO.HIGH)
        time.sleep(1)
        print('off')
        GPIO.output(LED_PIN, GPIO.LOW)
        time.sleep(1)
    for i in xrange(0, 1):
        GPIO.output(LED_PIN, GPIO.HIGH)
        time.sleep(1)
        GPIO.output(LED_PIN, GPIO.LOW)
        time.sleep(1)
    for i in xrange(0, 1):
        GPIO.output(LED_PIN, GPIO.HIGH)
        time.sleep(0.5)
        GPIO.output(LED_PIN, GPIO.LOW)
        time.sleep(0.5)

        

GPIO.cleanup();
