from selenium.webdriver import PhantomJS
from hashlib import md5
from random import choice
from string import ascii_letters
import os
import time

def get_md5(string):
    t = md5(string.encode()).hexdigest()
    return t

def get_rand_str(size=6):
    t = [choice(ascii_letters) for x in range(size) ]
    t = ''.join(t)
    return t 

def evaluate_mail(file_name):
    b = PhantomJS()
    file_location = os.getcwd() + '/mails/' + file_name
    print(file_location)
    file_location = "file://" + file_location
    print(file_location)
    b.get(file_location)
    time.sleep(4)
