#include <WiFi.h>

const char* ssid = "NIIIIIIGAAAA";
const char* password = "devine";

WiFiServer server(80);

String header;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup()
{
  Serial.begin(115200);
    
  /*Serial.print("Connecting to ");
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
  }*/

  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);  
  server.begin();

}

//Variables humiditée
int humidityLevel[] = {12, 35, 87, 56, 30, 69};
//Sélections plantes
int plantSelect[] ={0, 0, 0, 0, 0, 0}; 

void loop()
{
  String HTML = "<!DOCTYPE html> <html> <head> <title>Toit VG-table</title> </head> <script language=JavaScript>document.onkeydown=checkKey;function checkKey(a){a=a||window.event;if(a.keyCode==\"27\"){document.getElementById(\"main\").style.filter=\"blur(0px)\";document.getElementById(\"dialog\").style.display=\"none\"}else{if(a.keyCode==\"13\"){applyPlant();post()}else{if(a.keyCode==\"37\"){plantList(2)}else{if(a.keyCode==\"39\"){plantList(1)}}}}}let plantesIcones=['<svg version=\"1.1\" id=\"Capa_1\" class=\"icons\"xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"viewBox=\"0 0 490 490\" style=\"enable-background:new 0 0 490 490;fill:red;\" xml:space=\"preserve\"><polygon points=\"386.813,0 245,141.812 103.188,0 0,103.188 141.813,245 0,386.812 103.187,489.999 245,348.187 386.813,490 490,386.812 348.187,244.999 490,103.187 \"/></svg>','<svg version=\"1.1\" class=\"icons\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 284.933 284.933\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" enable-background=\"new 0 0 284.933 284.933\" style=\"enable-background:new 0 0 490 490;fill:#ff0ffb;\"><path d=\"m277.651,133.196c-0.974-1.24-10.02-12.337-27.357-20.004-7.234-3.199-16.642-6.08-28.046-6.967 4.019-9.175 3.801-16.8 3.314-20.502-1.834-13.929-12.424-24.519-26.352-26.353-3.595-0.472-10.884-0.693-19.7,2.97-1.373-8.744-4.088-16.115-7.05-21.999-8.289-16.463-20.149-24.957-21.474-25.872l-8.521-5.88-8.521,5.881c-1.325,0.914-13.184,9.409-21.473,25.871-2.963,5.884-5.678,13.257-7.051,22.003-8.816-3.663-16.106-3.443-19.699-2.973-13.928,1.834-24.519,12.424-26.352,26.353-0.488,3.701-0.706,11.326 3.313,20.501-11.406,0.887-20.816,3.77-28.05,6.97-17.337,7.67-26.381,18.769-27.355,20.009l-7.277,9.267 7.281,9.266c0.974,1.24 10.02,12.337 27.357,20.004 7.233,3.199 16.643,6.079 28.046,6.966-4.02,9.176-3.801,16.801-3.313,20.502 1.833,13.929 12.424,24.519 26.352,26.353 1.073,0.141 2.474,0.26 4.147,0.26 3.933,0 9.367-0.66 15.551-3.23 1.373,8.745 4.088,16.116 7.051,22 8.289,16.463 20.149,24.957 21.475,25.872l8.52,5.88 8.521-5.881c1.325-0.914 13.184-9.409 21.473-25.871 2.962-5.884 5.677-13.255 7.05-22 6.185,2.57 11.62,3.23 15.552,3.23 1.673,0 3.075-0.119 4.147-0.26 13.928-1.834 24.518-12.424 26.352-26.353 0.487-3.702 0.705-11.327-3.314-20.502 11.405-0.887 20.818-3.769 28.051-6.969 17.337-7.67 26.381-18.769 27.355-20.009l7.278-9.268-7.281-9.265zm-85.326-43.66c1.072-0.35 1.893-0.451 2.467-0.451 0.48,0 0.788,0.071 0.929,0.127 0.123,0.309 0.317,1.428-0.324,3.396-0.739,2.268-3.691,8.622-14.553,15.889-0.686-0.774-1.39-1.537-2.131-2.278-0.74-0.74-1.503-1.444-2.276-2.13 7.267-10.861 13.621-13.814 15.888-14.553zm-34.825,67.964c-8.29,8.289-21.777,8.288-30.067,0.001-8.29-8.29-8.29-21.778 0-30.068 4.146-4.145 9.589-6.217 15.033-6.217s10.89,2.072 15.033,6.217c8.29,8.289 8.29,21.777 0.001,30.067zm-18.763-102.577c1.143-2.432 2.429-4.593 3.729-6.478 1.104,1.6 2.197,3.397 3.198,5.387 5.573,11.068 6.27,23.712 2.15,37.683-3.557-0.37-7.143-0.37-10.7,0-3.981-13.508-3.458-25.785 1.623-36.592zm-49.525,34.288c0.306-0.123 1.429-0.317 3.395,0.324 2.268,0.739 8.622,3.693 15.889,14.554-0.773,0.685-1.536,1.389-2.276,2.13-0.741,0.741-1.445,1.503-2.131,2.277-10.863-7.268-13.815-13.621-14.554-15.89-0.64-1.967-0.447-3.086-0.323-3.395zm-46.205,53.255c9.929-5.317 25.961-9.718 48.341-3.305-0.141,2.201-0.141,4.408 0,6.609-22.381,6.412-38.412,2.013-48.341-3.304zm49.599,52.931c-1.967,0.643-3.087,0.447-3.395,0.324-0.124-0.309-0.317-1.428 0.323-3.396 0.739-2.268 3.691-8.622 14.554-15.89 0.686,0.774 1.39,1.537 2.131,2.277 0.74,0.74 1.503,1.444 2.276,2.13-7.266,10.862-13.62,13.816-15.889,14.555zm53.589,34.612c-1.143,2.432-2.43,4.594-3.729,6.479-1.3-1.885-2.587-4.047-3.729-6.479-5.083-10.807-5.605-23.083-1.623-36.593 1.779,0.185 3.565,0.286 5.352,0.286s3.573-0.101 5.352-0.286c3.982,13.51 3.459,25.786-1.623,36.593zm49.526-34.288c-0.309,0.122-1.426,0.318-3.396-0.324-2.268-0.739-8.622-3.693-15.889-14.553 0.773-0.685 1.536-1.389 2.276-2.13l.001-.001c0.74-0.74 1.444-1.503 2.13-2.277 10.862,7.267 13.814,13.621 14.553,15.889 0.642,1.968 0.448,3.088 0.325,3.396zm-2.138-49.95c0.141-2.201 0.141-4.408 0-6.609 22.381-6.414 38.412-2.014 48.343,3.304-9.929,5.317-25.961,9.719-48.343,3.305z\"/></svg>','<svg version=\"1.1\" class=\"icons\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 250.14 250.14\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" enable-background=\"new 0 0 250.14 250.14\" style=\"enable-background:new 0 0 490 490;fill:#0f57ff;\"><path d=\"M178.497,78.143L125.069,0L71.642,78.144L9.739,34.495V134.81c0,63.593,51.737,115.33,115.33,115.33  c63.594,0,115.331-51.737,115.331-115.33V34.495L178.497,78.143z M125.069,53.154l28.907,42.279l-28.907,20.382L96.163,95.433  L125.069,53.154z M210.4,134.81c0,47.051-38.279,85.33-85.331,85.33c-47.051,0-85.33-38.279-85.33-85.33V92.356l85.33,60.166  L210.4,92.356V134.81z\"/></svg>','<svg version=\"1.1\" class=\"icons\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 262.1 262.1\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" enable-background=\"new 0 0 262.1 262.1\" style=\"enable-background:new 0 0 490 490;fill:#dbdddd;\"><path d=\"M192.646,57.343v-4.99c3.168-3.556,5.112-8.225,5.112-13.351c0-11.09-9.022-20.111-20.112-20.111  s-20.112,9.021-20.112,20.111c0,5.126,1.944,9.795,5.112,13.351v37.611l-16.596,21.145V33.463c3.168-3.556,5.112-8.225,5.112-13.351  C151.162,9.022,142.14,0,131.05,0s-20.111,9.022-20.111,20.112c0,5.126,1.943,9.795,5.111,13.351v77.646L99.455,89.965V52.353  c3.168-3.556,5.111-8.225,5.111-13.351c0-11.09-9.021-20.111-20.111-20.111s-20.112,9.021-20.112,20.111  c0,5.126,1.944,9.795,5.112,13.351v4.99H13.941v87.648c0,64.574,52.534,117.108,117.108,117.108s117.108-52.534,117.108-117.108  V57.343H192.646z M218.158,144.991c0,48.031-39.076,87.108-87.108,87.108s-87.108-39.077-87.108-87.108V87.343H59.26l71.79,91.469  l71.79-91.469h15.318V144.991z\"/></svg>','<svg version=\"1.1\" id=\"Capa_1\" class=\"icons\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"viewBox=\"0 0 490.361 490.361\" enable-background=\"new 0 0 490.361 490.361\" xml:space=\"preserve\" style=\"enable-background:new 0 0 490 490;fill:#c26dff;\"><g><g><g><path d=\"M490.008,387.934c-7.7-42.6-39.8-104.5-90.6-143.8c53.3-45.6,85.5-101.8,90.6-143.8c2.4-19.1-15.6-25.6-27.1-21.9l-80.2,28.1l28.1-79.2c6.2-15.9-7.1-28.7-21.9-27.1c-43,4.8-101.4,39.5-143.7,90.7c-36-46.2-102-84.4-143.8-90.6c-17.7-2.6-27.7,15.9-22.9,27.1l28.1,79.2l-79.2-28.2c-15.4-5.2-29.7,9.6-27.1,23c8.4,42.5,37.2,99.3,90.6,143.8c-56.1,51.5-83.9,103.1-90.6,144.8c-2.1,13.2,9,27.1,27.1,21.9l80.2-28.1l-28.1,79.2c-7,14.8,9.2,28.8,18.8,27.1c83.3-14.8,141.7-84.7,146.9-91.7c3.9,7,68.3,79.2,146.9,90.6c16.5,2.9,24.6-18.6,18.8-30.2l-27.1-77.1l79.2,28.1C476.308,415.534,493.008,404.434,490.008,387.934z M356.608,330.634c-18.1-5.7-31.6,11.8-26,26l29.2,81.3c-24-11.5-64.3-36.4-97.9-83.3c-11-15.7-26.1-9.2-33.3,0c-28,40.5-74,71.9-97.9,83.3l30.2-81.3c5.8-16.9-12.4-31.8-27.1-26l-81.3,29.2c11.5-24,32.6-60.2,83.3-97.9c17.3-11,8.8-30.1,0-33.3c-41.9-27.8-71.9-74-83.3-97.9l81.3,29.2c15.3,4.6,31.8-10.2,26-26l-29.2-81.3c24,11.5,74.4,46.1,97.9,83.3c2.7,6.6,19.2,18.9,33.3,0c37.8-50.6,74-71.9,97.9-83.3l-29.2,81.3c-5.6,16.3,11.8,32.8,26,26l81.3-29.2c-11.5,24-32.2,58.6-83.3,97.9c-15.4,9.5-8.5,27.4,0,33.3c46,32.9,71.9,74,83.3,97.9L356.608,330.634z\"/><path d=\"M245.208,170.134c-41.4,0-75,33.6-75,75s33.6,75,75,75s75-33.6,75-75S286.608,170.134,245.208,170.134z M245.208,279.134c-18.8,0-34-15.2-34-34s15.2-34,34-34s34,15.2,34,34S263.908,279.134,245.208,279.134z\"/></g></g></g></svg>','<svg version=\"1.1\" id=\"Capa_1\" class=\"icons\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"viewBox=\"0 0 489.2 489.2\" style=\"enable-background:new 0 0 489.2 489.2;fill:#f7e309;\" xml:space=\"preserve\"><g><g><g><g><path d=\"M244.55,337.9c-50.8,0-93.3-41.5-93.3-93.3c0-50.8,41.5-93.3,93.3-93.3c50.8,0,93.3,41.5,93.3,93.3C337.85,295.4,295.35,337.9,244.55,337.9z M244.55,192.8c-29,0-51.8,23.8-51.8,51.8c0,29,23.8,51.8,51.8,51.8c29,0,51.8-23.8,51.8-51.8C296.35,215.6,273.55,192.8,244.55,192.8z\"/></g><g><path d=\"M417.65,71.5c25.9,25.9,30.1,67.4,10.4,97.4c35.2,7.3,61.1,38.3,61.1,75.7s-25.9,68.4-61.1,75.7c19.7,30.1,15.5,70.5-10.4,97.4c-26.9,26.4-67.4,29.7-97.4,10.4c-7.3,35.2-38.3,61.1-75.7,61.1s-68.4-25.9-75.7-61.1c-30.7,19.8-70,15.2-97.4-10.4c-24.7-24.1-30.8-66.1-10.3-97.4c-35.2-7.3-61.1-38.3-61.1-75.7s25.9-68.4,61.1-75.7c-20.1-30.8-15.2-70.3,10.3-97.4c26.1-25.6,65.6-30.8,97.4-10.4c7.3-35.2,38.3-61.1,75.7-61.1s68.4,25.9,75.7,61.1C351.75,40.9,388.85,45.6,417.65,71.5z M100.45,386.6c13.5,13.5,38.3,13.5,51.8,0l14.8-14.8c15.2-15.5,41.2-9.3,41.2,10.7v27.3c0,20.5,16.3,37.7,36.8,37.9c21,0.3,37.8-16.4,37.8-37.3v-28c0.5-18.1,20.6-26.4,34.2-14.5l19.2,19.2c14,14,37.5,14.7,51.8,1c15.1-14.5,15.2-38.7,0.5-52.4l-19.7-19.7c-12.8-10.2-4.5-33.9,14.5-34.2h27.3c20.5,0,37.7-16.3,37.9-36.8c0.3-21-16.4-37.8-37.3-37.8h-28c-14.3,2-28.7-19.9-14.5-34.2l19.7-19.7c14.5-14.5,14.5-38.3,0-51.8c-13.5-13.5-38.3-13.5-51.8,0l-20.7,18.7c-16.5,13.2-32.9,1.9-34.2-14.5V78.4c0-20.5-16.3-37.7-36.8-37.9c-21-0.3-37.8,16.4-37.8,37.3v28c0.2,18.6-22.5,26.3-34.2,14.5l-19.7-19.7c-13.5-13.5-38.3-13.5-51.8,0c-14.5,14.8-12.7,37.2,0,51.8l19.7,19.7c12.6,11.5,3.8,34.3-14.5,34.2h-28.3c-20.5,0-37.7,16.3-37.9,36.8c-0.3,21,16.4,37.8,37.3,37.8h28c15.9-0.1,27.6,18.3,14.5,34.2l-19.7,19.7C87.05,349,86.55,371.8,100.45,386.6z\"/></g></g></g></g></svg>','<svg version=\"1.1\" id=\"Capa_1\" class=\"icons\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"viewBox=\"0 0 43.72 43.72\" style=\"enable-background:new 0 0 43.72 43.72;fill:#95fc41;\" xml:space=\"preserve\"><g><path d=\"M43.716,10.739c-0.047-1.583-1.327-2.857-2.91-2.91l-0.291-0.003c-1.19,0-5.908,0.154-10.53,2.248c-2.009-5.346-5.849-9.031-6.066-9.237c-1.156-1.089-2.96-1.09-4.116,0c-0.219,0.207-4.059,3.892-6.068,9.238C9.112,7.98,4.395,7.826,3.205,7.826L2.914,7.829c-1.583,0.053-2.863,1.327-2.91,2.91c-0.012,0.408-0.226,10.064,5.827,16.117c4.007,4.007,9.597,5.263,13.029,5.653v8.189c0,1.657,1.343,3,3,3s3-1.343,3-3V32.51c3.435-0.393,9.022-1.646,13.029-5.654C43.942,20.803,43.729,11.147,43.716,10.739z M21.859,7.625c1.1,1.498,2.337,3.583,2.948,5.924c-0.038,0.038-0.08,0.069-0.118,0.107c-1.16,1.159-2.085,2.452-2.831,3.785c-0.745-1.333-1.671-2.626-2.831-3.785c-0.038-0.038-0.079-0.07-0.117-0.107C19.522,11.208,20.76,9.123,21.859,7.625z M6.257,14.085c1.833,0.282,4.188,0.881,6.277,2.106c0,0.054-0.008,0.107-0.008,0.162c0,3.491,1.165,6.658,2.56,9.216c-1.767-0.603-3.58-1.521-5.014-2.956C7.628,20.168,6.649,16.629,6.257,14.085z M33.646,22.613c-1.434,1.435-3.246,2.354-5.013,2.956c1.395-2.559,2.56-5.725,2.56-9.216c0-0.055-0.007-0.107-0.008-0.162c2.089-1.225,4.444-1.824,6.276-2.106C37.069,16.631,36.091,20.168,33.646,22.613z\"/></g><g></svg>'];let plantesNoms=[\"Rien\",\"Pourpier Cooper\",\"Campanula\",\"Gazon d'Espagne\",\"Thyms\",\"Alyssum saxatile\",\"Artemisia stelleriana\"];let caseActuelle=0;let caseData=["+String(plantSelect[0])+","+String(plantSelect[1])+","+String(plantSelect[2])+","+String(plantSelect[3])+","+String(plantSelect[4])+","+String(plantSelect[5])+"];let humi=["+humidityLevel[0]+","+humidityLevel[1]+","+humidityLevel[2]+","+humidityLevel[3]+","+humidityLevel[4]+","+humidityLevel[5]+"];let currentPlant=caseData[caseActuelle];function showBox(){document.getElementById(\"main\").style.filter=\"blur(20px)\";document.getElementById(\"main\").style.transitionDuration=\"200ms\";document.getElementById(\"dialog\").style.display=\"block\";document.getElementById(\"pourcentage\").innerHTML=humi[caseActuelle]+\"%\";document.getElementById(\"caseNumber\").innerHTML=caseActuelle+1;document.querySelector(\".waves\").style.height=humi[caseActuelle]*1.8+\"px\";document.getElementById(\"plantesIcones\").innerHTML=plantesIcones[caseData[caseActuelle]];document.getElementById(\"plantesNoms\").innerHTML=plantesNoms[caseData[caseActuelle]];currentPlant=caseData[caseActuelle]}function plantList(a){if(a==1){currentPlant=currentPlant+1;if(currentPlant==7){currentPlant=0}}if(a==2){currentPlant=currentPlant-1;if(currentPlant==-1){currentPlant=6}}document.getElementById(\"plantesIcones\").innerHTML=plantesIcones[currentPlant];document.getElementById(\"plantesNoms\").innerHTML=plantesNoms[currentPlant];if(currentPlant!=caseData[caseActuelle]){document.getElementById(\"apply\").style.fill=\"#8ffc0a\"}}function applyPlant(){caseData[caseActuelle]=currentPlant;document.getElementById(\"apply\").style.fill=\"white\";document.getElementById(caseActuelle).innerHTML=plantesIcones[caseData[caseActuelle]]}function quit(){document.getElementById(\"main\").style.filter=\"blur(0px)\";document.getElementById(\"dialog\").style.display=\"none\"}function post(){const a=new XMLHttpRequest();a.open(\"GET\",\"/\");a.setRequestHeader(\"Case\",String(caseActuelle));a.setRequestHeader(\"ValeurCase\",String(caseData[caseActuelle]));a.send()}function loadIcons(){for(let i=0;i!=6;i++){document.getElementById(i).innerHTML=plantesIcones[caseData[i]]}};</script> <style>.background{background-color:black}.text{color:white;font-weight:900;font-family:Arial,Helvetica,sans-serif;position:absolute;transform:translate(-50%,-50%);font-size:30px;text-align:center;vertical-align:top}.iconsList{height:190px;width:190px;transform:translate(-50%,-50%);top:47%;left:65%;position:absolute}.base{width:515px;height:345px;transform:translate(-50%,-50%) skew(20deg);background:#fff;border-radius:25px;position:absolute;top:50vh;bottom:50vh;left:50vw;right:50vw}.case{width:167.5px;height:160px;border:50px double black;transform:translate(-51%,-49%);background:white;border-radius:25px;position:absolute;cursor:pointer;box-shadow:0}.case:hover{background:#000;border:50px double white;transition-duration:200ms;transform:translate(-51%,-47%);box-shadow:-2px 2px 5px rgba(121,121,121,0.575)}.boite-dialogue{width:600px;height:400px;transform:translate(-50%,-50%);background:#000;border:4px solid #fff;border-radius:25px;position:absolute;top:50vh;bottom:50vh;left:50vw;right:50vw;display:none;transition-duration:200ms}.cadran-humidity{height:180px;width:180px;top:120px;left:120px;border-radius:50%;border:10px solid white;background-color:rgba(0,0,0,0);display:inline-block;position:absolute;transform:translate(-50%,-50%);overflow:hidden}.waves{width:180px;left:0;bottom:0;background-color:turquoise;position:absolute}</style> <body id=background class=background onload=loadIcons()> <div id=main class=base> <button id=0 class=\"case\"; style=\"top:90px;left:90px\"; onclick=\"caseActuelle=0;showBox()\"></button> <button id=1 class=\"case\"; style=\"top:90px;left:260px\"; onclick=\"caseActuelle=1;showBox()\"></button> <button id=2 class=\"case\"; style=\"top:90px;left:430px\"; onclick=\"caseActuelle=2;showBox()\"></button> <button id=3 class=\"case\"; style=\"top:255px;left:90px\"; onclick=\"caseActuelle=3;showBox()\"></button> <button id=4 class=\"case\"; style=\"top:255px;left:260px\"; onclick=\"caseActuelle=4;showBox()\"></button> <button id=5 class=\"case\"; style=\"top:255px;left:430px\"; onclick=\"caseActuelle=5;showBox()\"></button> </div> <div id=dialog class=boite-dialogue> <div class=cadran-humidity> <div id=pourcentage style=color:#fff;font-weight:900;font-size:30px;font-family:Arial,Helvetica,sans-serif;text-align:center;top:50%;left:50%;position:absolute;transform:translate(-50%,-50%);z-index:1;user-select:none></div> <div class=waves></div> </div> <div id=caseNumber style=color:white;font-weight:900;font-size:35px;text-align:center;z-index:2;font-family:Arial,Helvetica,sans-serif;top:1%;left:1%;position:absolute;user-select:none></div> <div id=quit onclick=quit() style=top:2.5%;right:2%;position:absolute><svg version=1.1 id=Capa_1 xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink width=45px height=45px viewBox=\"0 0 500 500\" style=fill:#f00 xml:space=preserve><g><path d=\"M76.563,490h336.875C455.547,490,490,455.547,490,413.438V76.563C490,34.453,455.547,0,413.437,0H76.563C34.453,0,0,34.453,0,76.563v336.875C0,455.547,34.453,490,76.563,490z M124.835,175.445l50.61-50.611L245,194.39l69.555-69.555l50.61,50.611L295.611,245l69.555,69.555l-50.61,50.611L245,295.611l-69.555,69.555l-50.61-50.61L194.389,245L124.835,175.445z\"/></g></svg></div> <div id=plantesIcones class=iconsList></div> <div id=plantesNoms class=text style=user-select:none;top:80%;left:65%>Plantipus</div> <div id=flèches> <div onclick=plantList(1)><svg version=1.1 id=Capa_1 xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink x=0px y=0px viewBox=\"0 0 490 490\" style=\"enable-background:new 0 0 490 490;top:80%;left:85%;transform:translate(-50%,-50%);position:absolute;fill:white;width:30px;height:30px\" xml:space=preserve><polygon style=\"transform-origin:50% 50%;transform:rotate(90deg)\" points=\"0,332.668 245.004,82.631 490,332.668 413.507,407.369 245.004,235.402 76.493,407.369\"/></svg></div> <div onclick=plantList(2)><svg version=1.1 id=Capa_1 xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink x=0px y=0px viewBox=\"0 0 490 490\" style=\"enable-background:new 0 0 490 490;top:80%;left:45%;transform:translate(-50%,-50%);position:absolute;fill:white;width:30px;height:30px\" xml:space=preserve><polygon style=\"transform-origin:50% 50%;transform:rotate(-90deg)\" points=\"0,332.668 245.004,82.631 490,332.668 413.507,407.369 245.004,235.402 76.493,407.369\"/></svg></div> </div> <div onclick=applyPlant();post()><svg version=1.1 id=apply xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink x=0px y=\"0px\"viewBox=\"0 0 330 330\" style=\"enable-background:new 0 0 330 330;position:absolute;fill:#8ffc0a;width:100px;height:100px;top:77%;left:20%;transform:translate(-50%,-50%)\" xml:space=preserve><g><path d=\"M165,0C74.019,0,0,74.019,0,165s74.019,165,165,165s165-74.019,165-165S255.981,0,165,0z M165,300c-74.44,0-135-60.561-135-135S90.56,30,165,30s135,60.561,135,135S239.439,300,165,300z\"/><path d=\"M226.872,106.664l-84.854,84.853l-38.89-38.891c-5.857-5.857-15.355-5.858-21.213-0.001c-5.858,5.858-5.858,15.355,0,21.213l49.496,49.498c2.813,2.813,6.628,4.394,10.606,4.394c0.001,0,0,0,0.001,0c3.978,0,7.793-1.581,10.606-4.393l95.461-95.459c5.858-5.858,5.858-15.355,0-21.213C242.227,100.807,232.73,100.806,226.872,106.664z\"/></g></svg></div> </div> </body> </html>";

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