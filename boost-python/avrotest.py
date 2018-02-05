'''
Created on Feb 2, 2018

@author: copernicus
'''

def func(x,y):
    return x+y

def process(record):
    val=func(record.re,record.im)
    print val
    return