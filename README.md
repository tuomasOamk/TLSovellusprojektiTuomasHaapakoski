TLSovellusprojekti Tuomas Haapakoski A repository for my project by Tuomas Haapakoski 
![image](https://user-images.githubusercontent.com/99179437/207415999-14c23506-a962-4871-ba4d-e89c0ad7313e.png)

What project is all about? 

I can send and receive data from OAMK server database and calculate center points from that data. 

Arduino program 

I used an Arduino program which established a TCP connection between my Arduino UNO microcontroller and OAMK server via Raspberry Pi router. I used a 433 MHz radio receiver and transmitter to transmit accelerometer data in 6 different angles. The program had a flag system which indicates which angle the accelerometer is in. After sending data I get an acknowledgement which tells me if the transmission was successful or not.  

TCP socket client 

In order to get my accelerometer data from the database, I had to make a TCP socket client. The client uses the server’s IP address to connect to the server and then pinpoints my sent data by my ID. After this the client prints out my data and saves it to a CSV file. 

K-means algorithm 

After receiving the data from the server’s database, I made k-means algorithm with Python and NumPy to calculate center points from the given data. The algorithm calculates distances between imported data points and randomly generated points. After this the algorithm takes the smallest results and saves them. It also counts how many times a point has “won” by adding value 1 every time one of the six points “wins”. If one of the points hasn’t had any wins, the point’s values are randomly generated again.  

 This whole process is iterated 500 times in order to get the most accurate results possible. After the iterations, the algorithm prints the center points and creates a whole new file for them.                   Lastly the center points are visualized to a 3D image by using matplotlib plotting. 
 ![kuva](https://user-images.githubusercontent.com/99179437/208653233-9e63e147-6ae5-4231-8f11-3d081bde6f06.png)


K-means on Arduino 

I used the center points file I got from K-means algorithm and the code from Arduino client program to implement the K-means algorithm to my Arduino UNO microcontroller. The program reads the center points and position flags from the file and prints them to serial monitor. The program asks how many measurements I want, and in which position. After that it starts printing the values to the serial monitor with 100ms delay after each value.  

Confusion matrix 

I made a confusion matrix Python file and used scikit-learn confusion matrix function. I made with PuTTY client program a file for the Arduino K-means algorithm results and used it to make the confusion matrix. I used the confusion matrix to show how accurate my algorithm is. It showed me perfect accuracy apart from couple position errors which were made when I had the accelerometer in wrong position during calculations.    
 
 ![kuva](https://user-images.githubusercontent.com/99179437/208653038-5efd99da-e967-4584-95e5-1a4cf962559c.png)



