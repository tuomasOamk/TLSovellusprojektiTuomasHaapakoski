import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn import metrics
import csv

data = np.genfromtxt("./groupid68data.csv", usecols=(6,7,8), delimiter=',') #Hakee datan tiedostosta
#numberOfRows = int(len(data)/3) #Datalle rivit, joissa x,y,z arvot
numberOfRows = int(data.size/3)
print(data)
#print("number of rows=",numberOfRows)
#n = np.reshape(n,(numberOfRows,3))
#data=np.zeros((numberOfRows,3))
#data[:,0]=n[:,0]
#data[:,1]=n[:,1]
#data[:,2]=n[:,2]
#print("data=",data)
cp = np.random.randint(np.amin(data),np.amax(data),size=(6,3))
#print("randomi")
#print(cp)

z = 0
y = 0
a = 0
x = 0
m = 0

oikeat_pisteet = np.zeros((6,3))

centerPointCumulativeSum = np.zeros((6,3))# Tähän summataan aina voittavalle keskipisteelle yhden datapisteen x,y,z komponentit

counts = np.zeros((1,6)) #tänne kasvatetaan aina voittavan keskipisteen datapisteiden lukumäärää yhdellä jokaisen voiton jälkeen.

Distances = np.zeros(6) #tähän talletetaan laskennan edetessä yksittäisen x,y,z pisteen etäisyys kaikkiin keskipisteet datarakenteessa oleviin 4 keskipisteeseen ja nuo 4 etäisyysarvoa talletetaan tähän muuttujaan.

#point1 = np.array([100,300,240])
#point2 = np.array([100,299,240])

def distance3D(point1,point2): #kolmiulotteisen etäisyyden laskemiseen oleva funktio
    pointSum = (point1[0]-point2[0])**2 +(point1[1]-point2[1])**2 + (point1[2]-point2[2])**2
    P = np.sqrt(pointSum)
    return P 
#arvo1 = np.zeros(3)
#arvo2 = np.zeros(3)
#print(distance3D(arvo1,arvo2))
for z in range(500):
    counts = np.zeros((1,6))
    centerPointCumulativeSum = np.zeros((6,3),dtype=int)
    for x in range(numberOfRows): #loopit etäisyyksien laskemiseen ja pienimpien arvojen hakemiseen
    
        for y in range(6): #sisäinen loop
            Distances[y]=distance3D(data[x],cp[y])

            
        minimi = np.argmin(Distances)
        #centerpoints = centerPointCumulativeSum/counts
        #counts[minimi]=counts[minimi]+1 #haetaan minimi arvo ja lisätään siihen 1
        if (np.argmin(Distances)==0):
            counts[0,0]=counts[0,0]+1
        elif np.argmin(Distances)==1:
            counts[0,1]=counts[0,1]+1
        elif np.argmin(Distances)==2:
            counts[0,2]=counts[0,2]+1
        elif np.argmin(Distances)==3:
            counts[0,3]=counts[0,3]+1
        elif np.argmin(Distances)==4:
            counts[0,4]=counts[0,4]+1
        else:
            counts[0,5]=counts[0,5]+1
        centerPointCumulativeSum[minimi]=centerPointCumulativeSum[minimi]+data[x] #summataan voittajalle yhden kolmiulotteisen datapisteen
        #print(centerpoints)     
    for a in range(6):   
        if counts[0,a] == 0: #Tarkistetaan onko jollekkin pisteelle tullut 0 voittoa ja laitetaan sille uusi satunnainen arvo
         cp[a,:] = np.random.randint(np.amin(data),np.amax(data),size=(1,3))
        else: 
         cp[a,:] = centerPointCumulativeSum[a,:]/counts[0,a]

tiedosto = open('keskipiste.h', 'w') #Tehdään funktio, joka luo ja tallentaa keskipisteet omaan tiedostoon: keskipiste.csv
writer = csv.writer(tiedosto)
writer.writerow(cp)
tiedosto.close()         
f = open("centerPoints.h", "w")     #Open/create new -h -file with write permissions and write data
f.write(f"int centerPoints[6][3] = {{ {{{cp[0,0]},{cp[0,1]},{cp[0,2]}}},{{{cp[1,0]},{cp[1,1]},{cp[1,2]}}},{{{cp[2,0]},{cp[2,1]},{cp[2,2]}}},{{{cp[3,0]},{cp[3,1]},{cp[3,2]}}},{{{cp[4,0]},{cp[4,1]},{cp[4,2]}}},{{{cp[5,0]},{cp[5,1]},{cp[5,2]} }} }};")
print("counts")
print(counts)
#print("centerPointCumulativeSum")
#print(centerPointCumulativeSum)
print("centerpoints")
print(cp)

fig = plt.figure(figsize=(10,10))
xyz = fig.add_subplot(projection='3d')
for m in ['o','^','']:
    xyz.scatter3D(cp[:,0],cp[:,1],cp[:,2],marker=m)
xyz.set_xlabel('X')
xyz.set_ylabel('Y')
xyz.set_zlabel('Z')
plt.show()


