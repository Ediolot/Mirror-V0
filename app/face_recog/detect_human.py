# -*- coding: utf-8 -*-
"""
Created on Sun May 26 15:25:52 2019

@author: PauL
"""
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import face_recognition
import cv2


cv2.namedWindow("preview")
vc = cv2.VideoCapture(1)

if vc.isOpened(): # try to get the first frame
    rval, frame = vc.read()
else:
    rval = False

cv2.imwrite('frame2.png',frame)

known_image = face_recognition.load_image_file('framed.png')
unknown_image = face_recognition.load_image_file('frame2.png')

biden_encoding = face_recognition.face_encodings(known_image)[0]
unknown_encoding = face_recognition.face_encodings(unknown_image)[0]

results = face_recognition.compare_faces([biden_encoding], unknown_encoding)
print(results)