//EACM
/* Conexion pines
     Arduino        GPS         
        D3           RX
        D4           TX
        Funciona con modulo SD
        7/12/23
          
  */
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <SD.h>

TinyGPS gps;
SoftwareSerial serialgps(4, 3);
const int chipSelect = 10; // Change this to the appropriate CS pin connected to your SD card module

void setup() {
  Serial.begin(115200);
  serialgps.begin(9600);

  if (!SD.begin(chipSelect)) {
    Serial.println("SD initialization failed!");
    return;
  }

  Serial.println("GPS GY-GPS6MV2 Leantec");
  Serial.println(" ---Buscando senal--- ");
}

void loop() {
  while (serialgps.available()) {
    int c = serialgps.read();
    //Serial.println(c);
    if (gps.encode(c)) {
      float latitude, longitude;
      gps.f_get_position(&latitude, &longitude);

      // Open the file. The 'FILE_WRITE' parameter allows us to write to the file.
      File dataFile = SD.open("gps_data.txt", FILE_WRITE);

      // If the file opens, write the GPS data to it.
      if (dataFile) {
        //dataFile.print("Latitud/Longitud: ");
        dataFile.print(latitude, 5);
        dataFile.print("\t ");
        dataFile.println(longitude, 5);
        dataFile.close();

        Serial.println("GPS data written to file.");
      } else {
        Serial.println("Error opening file.");
      }

      //gps.stats(); // Update the statistics (optional)
    } else {
      // Serial.println("GPS connection failed");
    }
  }
}
