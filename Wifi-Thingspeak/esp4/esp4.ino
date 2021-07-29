#include <SoftwareSerial.h>
#define RX 12
#define TX 11
String AP = "Jionet 2G";       // AP NAME
String PASS = "9742959053"; // AP PASSWORD
String API = "GLQK47A0796GU3RK";   // Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";
String field1 = "field1";
String field2 = "field2";
String field3 = "field3";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor1 = 1;
int valSensor2 = 1;
int valSensor3 = 1;
float time_elapsed = 0;
SoftwareSerial esp8266(RX,TX); 
 
  
void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
}

void loop() {

  
 Serial.println(time_elapsed);
 valSensor1 = getSensorData1();
 valSensor2 = getSensorData2();
 valSensor3 = getSensorData3();
 
 String getData = "GET /update?api_key="+ API +"&"+ field1 +"="+String(valSensor1)+"&"+ field2 +"="+String(valSensor2)+"&"+ field3 +"="+String(valSensor3);
sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 esp8266.println(getData);delay(1500);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
}

int getSensorData1(){
  return random(1000); // Replace with your own sensor code
}

int getSensorData2(){
  return random(1000); // Replace with your own sensor code
}

int getSensorData3(){
  return random(1000); // Replace with your own sensor code
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
