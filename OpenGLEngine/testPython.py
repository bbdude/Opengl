import random
import math

def helloWorld():
    returnData =  "Yahoooooooo !!!!!!!!!!!! Nice to meet you too !!!  "
    return returnData

def add(x,y):
    return x + y


def wander(x,y):
    
    datNumber = random.uniform(-1, 1)
    return datNumber

def seekX(numX,numY,targetX,targetY,speed):
    angle = atan2(numY-targetY, numX-targetX)
    dx = (double) (Math.cos(angle) * speed);          
    numX += dx;
    return numX
def seekY(numX,numY,targetX,targetY,speed):
    angle = atan2(numY-targetY, numX-targetX)
    dy = (double) (Math.sin(angle) * speed);          
    numY += dx;
    return numY


