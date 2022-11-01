/*

Tällä ohjelmalla demotaan kiihtyvyys-anturin toimintaa ja kiihtyvyys-näkymiä Serial Plotteria hyödyntäen 
 8.5.2017 -Jaakko Kaski-
 
 */

// Määritellään kytkentänavat kiihtyvyysanturille:
 const int VccPin2 = A0;  // Käyttöjännite
 const int xPin   = A1;   // x-kanavan mittaus
 const int yPin   = A2;   // y-kanava
 const int zPin   = A3;   // z-kanava
 const int GNDPin2 = A4;  // laitteen maa-napa

// Muuttujamäärittelyt. Huomaa, että desimaalierotin on piste!
unsigned long aika = 0; 
unsigned long vanha_aika = 0;

 int x = 0; //x-kanavan sensoriarvo 0 - 1023
 int y = 0;
 int z = 0;
 float ax = 0.0;  // x-kanavan kiihtyvyysarvo SI-muodossa (m/s^2)
 float ay = 0.0;
 float az = 0.0;
 float axyz = 0.0;
 int SisaanTunniste = 0;
 int indeksi = 0;
 
 int tila =  0;
 int toistot = 0;
 float ax_out = 0.0;
 float ay_out = 0.0;
 float az_out = 0.0;
 float axyz_out = 0.0;
 float vx = 0.0;
 float vx1 = 0.0;
 float vx2 = 0.0;
 float t1 = 0.0;
 float t2 = 0.0;

// Alustetaan kytkentänavat ja sarjayhteys
void setup() {
 Serial.begin (19200); // Tämä täytyy valita myös Serial Monitorista samaksi
 
 // Kiihtvyys-anturin napojen määrittely:
 pinMode(VccPin2, OUTPUT);     // Kiihtyvyysanturin käyttöjännite Vcc
 pinMode(GNDPin2, OUTPUT);     // Kiihtyvyysanturin GND

// Asetetaan syöttöjännite (5V UNO-BOARDILLA, 3.3V Genuino 101:llä) ja maa-arvot (0V):
    digitalWrite(VccPin2, HIGH);
    delayMicroseconds(2); 
    digitalWrite(GNDPin2, LOW); 
    delayMicroseconds(2);

    while(Serial.available() != 0)
     {
        // Odotellaan että yhteys käynnistyy jos tässä sattuu olemaan viivettä. 0 tarkoittaa että yhteys on.
     } 

}

void loop() {

  // eka sisäänmenolla annetaan 1ms aikaa käynnistyä. Muuten 1. arvo on pelkkää häiriötä.
  if(SisaanTunniste == 0)
  {
    delay(1); // 1ms viive käynnistymiselle
    SisaanTunniste = 1; // muutetaan testattava muuttuja jotta tänne ei enää tulla
  }

  if (axyz >= 8 && tila == 0){
    tila = 1;
    toistot = toistot + 1;
  }

  if (axyz < 6)
  {
    tila = 0;
  }

 // alustetaan mitattavat sensoriarvot nolliksi
 x = 0;
 y = 0;
 z = 0;

 // Kiihtyvyysmittaus, otetaan 10 kpl arvoja nopeasti jotta tulee keskimääräistystä; kirjoittaminen on hidasta
 for(indeksi = 0; indeksi < 10; indeksi++)
 {
  x = x + analogRead(xPin);  // Luetaan x-sensoriarvo, joka tulee 10-bittisellä koodauksella eli lukualueella 0 - 1023. 0 = 0V ja 1023 = Vcc.
  y = y + analogRead(yPin);
  z = z + analogRead(zPin);
 }

  // Aikaleima (ms)
 aika = millis(); // Aikaleima luetaan ennen laskentaa, tosi SERIAL PLOTTER EI KÄYTÄ TÄTÄ!

  x = x / 10;
  y = y / 10;
  z = z / 10;

 // Huomaa että kaikki mittaukset tehtiin nipussa, jotta aikaleima olisi niille mahdollisimman sama.
 // Aikaleiman lukemisen jälkeen vasta tehdään laskentaa...
 // Kalibroinnit kiihtyvyydelle lasketaan ennen tulostusta. 
 // Muunnos sensoriarvosta SI-muotoon. Selvitetty kalibrointimittauksella.
 // Huom! tarkka kalibrointi edellyttää että teet itse mittauksen ja selvität kullekin kanavalle tarkan yhtälön.
 // Tämä kalibrointi on vain "tyypillinen" tilanne, joka antaa likimäärin oikeat tulokset.
 // Voit testata kalibroinnin maan vetovoiman avulla. Akseli ylös = 9,81m/s^2 ja alas sama negatiivisena
 // kun et muuten liikuttele anturia.
 ax = 0.1422 * x - 48.525; 
 ax_out = 0.05 * ax + 0.95 * ax_out;
 
 ay = 0.1419 * y - 48.444; // ay kiihtyvyytenä. ay = z / 1023.0 * 5.0; // az jännitteenä / V, laskettiin nyt ay:n päälle.
 ay_out = 0.05 * ay + 0.95 * ay_out;
 
 az = 0.1463 * z - 50.334;
 az_out = 0.05 * az + 0.95 * az_out;
 
 axyz = sqrt(ax*ax + ay*ay + az*az);
 axyz_out = 0.05 * axyz + 0.95 * axyz_out;

 vx = vx + ax_out * (t2 - t1);
 vx1 = 0.95 * vx1 + 0.05 * vx;
 vx2 = vx - vx1; 
 

 ax = ax - ax_out;
 ay = ay - ay_out;
 az = az - az_out;
 axyz = axyz -axyz_out;
 
 

 Serial.print(aika); 
 Serial.print(" ");
 Serial.print(ax);  // x-suuntainen kiihtyvyys (m/s^2)
 Serial.print(" ");
 Serial.print(ay);  // y-suuntainen kiihtyvyys (m/s^2)
 Serial.print(" ");
 Serial.print(az); // z-suuntainen kiihtyvyys (m/s^2)
 Serial.print(" ");
 Serial.println(axyz); // z-acceleration (m/s^2)
 Serial.print(" ");
 Serial.print(vx);
 Serial.print(" ");
 Serial.print(vx2);
 
 
 delay(2);
}
