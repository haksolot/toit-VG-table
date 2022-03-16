#include <WiFi.h>

const char* ssid = "*******";
const char* password = "********";

WiFiServer server(80);

String header;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup()
{
  Serial.begin(115200);
    
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.print(".");  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  }

  /*Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);  
  server.begin();*/

}

//Variables humiditée
int humidityLevel[] = {12, 35, 87, 56, 30, 69};
//Sélections plantes
int plantSelect[] ={0, 0, 0, 0, 0, 0}; 

int configState = 0;

void loop()
{
  String HTML = "";
  WiFiClient client = server.available();   

  if (client)
  {                            
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");         
    String currentLine = "";               

    while (client.connected() && currentTime - previousTime <= timeoutTime)
    {  
      currentTime = millis();
      if (client.available())
      {            
        char c = client.read();             
        Serial.write(c);                    
        header += c;
        if (c == '\n')
        {                    
          if (currentLine.length() == 0)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            int Case = header.substring(header.indexOf("Case:")+6,header.indexOf("Case:")+8).toInt();
            int ValeurCase = header.substring(header.indexOf("ValeurCase:")+12,header.indexOf("ValeurCase:")+14).toInt();

            if (header.substring(header.indexOf("Accept:")+8,header.indexOf("Accept:")+11).equals("*/*"))
            {
                plantSelect[Case] = ValeurCase;
                if(header.substring(header.indexOf("dryLevel:")+10,header.indexOf("dryLevel:")+12).toInt() == 1)
                {
                  configState = 1;
                }
                if(header.substring(header.indexOf("wetLevel:")+10,header.indexOf("wetLevel:")+12).toInt() == 1)
                {
                  configState = 2;
                }
            }

            client.println(HTML);
            client.println();
            Serial.println("Case:");
            Serial.println(Case);
            Serial.println(ValeurCase);
            Serial.println(String(plantSelect[0])+String(plantSelect[1])+String(plantSelect[2])+String(plantSelect[3])+String(plantSelect[4])+String(plantSelect[5]));
            Serial.println(header.substring(header.indexOf("Accept:")+8,header.indexOf("Accept:")+11));  
            break;
          } 

          else
          { 
            currentLine = "";
          }
        }

        else if (c != '\r')
        {  
          currentLine += c;      
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}