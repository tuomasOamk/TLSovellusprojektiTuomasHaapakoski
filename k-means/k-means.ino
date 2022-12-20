#include "centerPoints.h"   //File includes centerpoints in format: x,y,z,flag
#include "accelerator.h"

void setup() 
{
  //Accelerator pins configuration
  pinMode(A0 ,OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, OUTPUT);
  digitalWrite(A0, LOW);
  digitalWrite(A4, HIGH);
  
  Serial.begin(9600);
}



void loop()
{

    Accelerator Aobject;                                        //Create object for measurements

    Serial.println("Give number how many measurements: ");      //Take number for measurements
    int NumberOfMeasurements = 0;
    while(NumberOfMeasurements == 0)
    {
        if(Serial.available()>0)
        {
            NumberOfMeasurements = Serial.parseInt();
        }
    }

    Serial.println("Give flag number: ");                       //Take position flag
    uint8_t flagIn = 0;
    while(flagIn == 0)
    {
        if(Serial.available()>0)
        {
            flagIn = Serial.parseInt();
        }
    }

    for(int i = 0; i < NumberOfMeasurements; i++)               //Begin to process measurements
    {
        float distance[6] = {};                                 //Initialize variables
        float minVal = 1023;
        int flagOut;

        Aobject.makeMeasurement();
        Measurement m = Aobject.getMeasurement();
        for(int j = 0; j < 6; j++)                              //Calculate distances for one measurement
        {
            distance[j] = sqrt(pow(centerPoints[j][0] - int(m.x), 2) + pow(centerPoints[j][1] - int(m.y), 2) + pow(centerPoints[j][2] - int(m.z), 2));
            //Serial.println(distance[j]);
        }

        
        for(int k = 0; k < 6; k++)                              //Find last minimum value and attach flagOut value
        {
            if(minVal > distance[k])
            {
                minVal = distance[k];
                flagOut = centerPoints[k][3];
            }
        }

        //Serial.println(minVal);
        delay(100);
        Serial.print(flagIn);           //Print given flag firstly
        Serial.print(",");
        Serial.println(flagOut);        //Print calculated flag
        /*switch (flagOut) {
          case 1:
          Serial.println("Z ylös");
          break;

          case 2:
          Serial.println("Z alas");
          break;

          case 3:
          Serial.println("Y ylös");
          break;

          case 4:
          Serial.println("Y alas");
          break;
          
          case 5:
          Serial.println("X ylös");
          break;

          case 6:
          Serial.println("X alas");
          break;
        }*/
        
    }



} //End of main loop
