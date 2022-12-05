import numpy as np
import pandas as pd


n = np.loadtxt("putty.log")
numberOfRows = int(len(n)/3)

print("number of rows=",numberOfRows)

data=np.zeros((numberOfRows,3))
data[:,0]=n[0:len(n):3]
data[:,1]=n[1:len(n):3]
data[:,2]=n[2:len(n):3]
print(data)

randomi = np.random.rand(4,3)*1023
print("randomi")
print(randomi)

centerPointCumulativeSum = np.zeros((4,3))# Tähän summataan aina voittavalle keskipisteelle yhden datapisteen x,y,z komponentit

counts = np.zeros((1,4)) #tänne kasvatetaan aina voittavan keskipisteen datapisteiden lukumäärää yhdellä jokaisen voiton jälkeen.

Distances = np.zeros((1,4)) #tähän talletetaan laskennan edetessä yksittäisen x,y,z pisteen etäisyys kaikkiin keskipisteet datarakenteessa oleviin 4 keskipisteeseen ja nuo 4 etäisyysarvoa talletetaan tähän muuttujaan.

dif = np.zeros((1,3))

def distance3D(point1,point2): #etäisyyden laskemiseen oleva funktio
    for x in range(3):
        dif[0,x]=point2[x]-point1[x]
    pointSum=np.power(dif[0,0],2)+np.power(dif[0,1],2)+np.power(dif[0,2],2)
    P = np.sqrt(pointSum)
    return(P) 
        



arvo1 = np.array([300,260,40])
arvo2 = np.array([300,200,40])
print("funktio testi")
print(distance3D(arvo1,arvo2))
for x in range(numberOfRows): #loopit etäisyyksien laskemiseen ja pienimpien arvojen hakemiseen
    print(x)
    
    for y in range(4):
        Distances[0,y]=distance3D(arvo1[x],arvo2[y])
        minimi = np.argmin(Distances)
        counts[0,minimi]=counts[0,minimi]+1
        centerPointCumulativeSum[min]=centerPointCumulativeSum[min]+arvo1[x]
        
print("counts")
print(counts)
print("centerPointCumulativeSum")
print(centerPointCumulativeSum)

     
    
