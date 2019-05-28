# -*- coding: utf-8 -*-
"""
Created on Sun May 26 15:25:52 2019

@author: PauL
"""
from subprocess import call
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import face_recognition
import cv2
import time
import os

directory = 'C:\\Users\\PauL\\Documents\\MAI\\HCI\\mirror\\Mirror-V0\\app\\cmake-build-debug\\'
app = 'mirror_app.exe'

valid_users = [i for  i in os.listdir() if '.png' in i]
valid_users = [i for i in valid_users if not 'current_frame' in i]
while(True):
    cv2.namedWindow("preview")
    vc = cv2.VideoCapture(1)
    
    if vc.isOpened(): # try to get the first frame
        rval, frame = vc.read()
    else:
        rval = False
    
    cv2.imwrite('current_frame.png',frame)
    person = None
    for user in valid_users:
        try:
            known_image = face_recognition.load_image_file('pau.png')
            unknown_image = face_recognition.load_image_file('current_frame.png')
            
            biden_encoding = face_recognition.face_encodings(known_image)[0]
            unknown_encoding = face_recognition.face_encodings(unknown_image)[0]
            
            results = face_recognition.compare_faces([biden_encoding], unknown_encoding)
            if results:    
                person = user.split('.')[0]
        except:
            pass
    if person:
        os.system(directory+app + ' ' + person)
    print(person)
    time.sleep(5)
