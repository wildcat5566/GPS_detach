#include <SoftwareSerial.h>
SoftwareSerial SoftSerial(2, 3);
#define ACTUATOR 4                                    // Detach device pin number

double latitude, longitude;                           // Store retrieved latitude / longitude info
//double latitude0 = 2502.06, longitude0 = 12137.13;  // House
double latitude0 = 2504.26,   longitude0 = 12161.20;  // Office
double latitude_margin = 1.0, longitude_margin = 1.0; // Set detach margin

int satellite = 0;                                    // Satellite information accessibility
String s;
String serialResponse = "";

void setup()
{
    SoftSerial.begin(9600); 
    Serial.begin(9600); 
    pinMode(ACTUATOR, OUTPUT);
}
void loop()
{
    if (SoftSerial.available()) {
        serialResponse = SoftSerial.readStringUntil('\r\n');
        if(serialResponse.indexOf("GPGGA") > 0){              // Row containing desired information
            int index = 0;                                    // Index of data
            char buf[64];                                     
            serialResponse.toCharArray(buf, sizeof(buf));     // Convert from String Object to String.
            char *p = buf;
            char *str;
    
            while ((str = strtok_r(p, ",", &p)) != NULL){     // Parse string at commas
                //Serial.println(str);
                if(index == 2){                               // Latitude info should be index #2
                    s = String(str);
                    if (s != "0"){                            // Check data existence, infer satellite accessibility
                        satellite = 1;
                        latitude = s.toDouble();
                    }
                    else{
                        Serial.println("No satellite information");
                        satellite = 0;
                    }
                }
                if(index == 4){                               // Latitude info should be index #4
                    s = String(str);
                    if (s != "M"){
                        longitude = s.toDouble();
                        satellite = 1;
                    }
                    else{
                        Serial.println("No satellite information");
                        satellite = 0;
                    }
                }

                index++;
            }
            Serial.print("Latitude: \t");    Serial.print(latitude);
            Serial.print(", Longitude: \t"); Serial.println(longitude);
        }
        
        // Activate detach device when reaches certain displacement
        if(satellite == 1 && (abs(latitude - latitude0) > latitude_margin || abs(longitude - longitude0) > longitude_margin)){
            digitalWrite(ACTUATOR, HIGH);
        }
        else{
            digitalWrite(ACTUATOR, LOW);
        }
    }
}

