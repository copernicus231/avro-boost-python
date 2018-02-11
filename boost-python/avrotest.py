'''
Created on Feb 2, 2018

@author: copernicus
'''

def func(x,y):
    return x+y
def func2(r):
    for p in r.children:
        print p.stringvalue
def process(record):
    val=func(record.intvalue,record.intvalue)
    print val
    func2(record)
    return