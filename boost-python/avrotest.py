'''
Created on Feb 2, 2018

@author: copernicus
'''

def func(x,y):
    return x+y
def func2(r):
    actt = 0
    for p in r.children:
        actt = actt + p.intvalue
    return actt
def process(record):
    d={}
    d['func']=func(record.intvalue,record.intvalue)
    print d['func']
    d['func2']=func2(record)
    print d['func2']
    return d