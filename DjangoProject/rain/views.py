from django.shortcuts import render
from django.http import HttpResponse
from django.template import Context
from django.template.loader import get_template
import RPi.GPIO as GPIO
import time 
import os,glob

ldrpin=21
trig=23
echo=24
linkit=15
GPIO.setmode(GPIO.BCM)
GPIO.setup(linkit,GPIO.OUT)
GPIO.setup(trig, GPIO.OUT)
GPIO.setup(echo,GPIO.IN)
GPIO.output(linkit,False)
os.system('modprobe w1-gpio') 
os.system('modprobe w1-therm') 
base_dir = '/sys/bus/w1/devices/' 
device_folder = glob.glob(base_dir + '28*')[0] 
device_file = device_folder + '/w1_slave' 

def ldr(request):
    reading=0 
    GPIO.setup(ldrpin,GPIO.OUT) 
    GPIO.output(ldrpin,GPIO.LOW) 
    time.sleep(0.2) 
    GPIO.setup(ldrpin,GPIO.IN) 
    while (GPIO.input(ldrpin)==GPIO.LOW): 
        reading=reading+1 
    contam=reading/42 
    contam=round(contam,2) 
    time.sleep(1) 
    t=get_template('ldr.html')
    html=t.render(Context({'contam': contam}))
    return HttpResponse(html) 
def ultrasound(request):
    height=50
    GPIO.output(trig,False) 
    time.sleep(0.5)
    GPIO.output(trig,True) 
    time.sleep(0.00001) 
    GPIO.output(trig,False) 
    start=time.time()
    while GPIO.input(echo)==0: 
        start=time.time() 
    while GPIO.input(echo)==1: 
        end=time.time() 
 
 
    duration=end-start 
    cm=duration*17150 
    if cm>height: 
        cm=height 
   
    cm=round(cm,2) 
    fill=height-cm 
    fillpercent=(fill/height)*100 
    fillpercent=round(fillpercent, 2) 
    t=get_template('ultrasound.html')
    html=t.render(Context({'us': fillpercent}))
    return HttpResponse(html)
def home(request):
    GPIO.output(linkit,True)
    return render(request,'home.html')
def closed(request):
    GPIO.output(linkit,False)
    return render (request,'home_closed.html')

def read_temp_raw(): 
    f = open(device_file, 'r') 
    lines = f.readlines() 
    f.close() 
    return lines 

def read_temp(): 
    lines = read_temp_raw() 
    while lines[0].strip()[-3:] != 'YES': 
        time.sleep(0.2) 
        lines = read_temp_raw() 
    equals_pos = lines[1].find('t=') 
    if equals_pos != -1: 
        temp_string = lines[1][equals_pos+2:] 
        temp_c = float(temp_string) / 1000.0 
        return temp_c 

def temperature(request):
    t=get_template('temp.html')
    html=t.render(Context({'temp': read_temp()}))
    return HttpResponse(html)
