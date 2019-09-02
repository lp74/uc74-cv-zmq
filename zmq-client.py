import cv2
import time
import zmq
import sys

context=zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:6666")

img = cv2.imread("/home/lp74/Pictures/lena.png", cv2.IMREAD_GRAYSCALE)
enc = cv2.imencode(".jpg", img)

while True:
    t1 = time.time()
    socket.send(enc[1].tobytes(), zmq.NOBLOCK)
    t2 = time.time()
    socket.recv()
    t3 = time.time()
    print('{:.3f} {:.3f}'.format(t2-t1, t3-t2))
