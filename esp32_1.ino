#include <Arduino.h>
#include <WiFi.h>
#include <SocketIoClient.h>
#include <Servo.h>

const char* ssid     = ""; //"INFINITUMC2A2_2.4"
const char* password = "";        //"Dus2qzqyFC"
const char* server = "201.130.170.2"; //Enter server adress
const uint16_t port = 5001; // Enter server port
int payload_entero;
SocketIoClient socketIO;
#define ONBOARD_LED  2
String str;
int a;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int pinServo1 = 13;
int pinServo2 = 12;
int pinServo3 = 14;
int pinServo4 = 27;
int pinServo5 = 26;

float ANGULO1 = 90;
float ANGULO2 = 90;
float ANGULO3 = 50;
float ANGULO4 = 120;
float ANGULO5 = 100;


void setup() {
  Serial.begin(115200);
  connectWiFi_STA();
  socketIO.begin(server, port);
  socketIO.on("desde_servidor",procesar_mensaje_recibido);

  servo1.attach(pinServo1);
  servo2.attach(pinServo2);
  servo3.attach(pinServo3);
  servo4.attach(pinServo4);
  servo5.attach(pinServo5);

  posicion_inicial();
  
}

void loop() {
  socketIO.loop();
}

void procesar_mensaje_recibido(const char * payload, size_t length) {
  
    //Serial.printf("Mensaje recibido: %s\n", payload);
    a = atoi((char *)payload);
    
    if(a>=0 && a<=180)
    { 
      servo1.write(a);
    }
    else if(a>=1050 && a<=1180)
    {
      servo2.write(a-1000); 
    }
    else if(a>=2000 && a<=2180)
    {
      servo3.write(a-2000);
    }
    else if(a>=3000 && a<=3180)
    {
      servo4.write(a-3000);
    }
    else if(a>=4080 && a<=4180)
    {
      servo5.write(a-4000);
    }
}

void connectWiFi_STA()
{
   delay(10);
   Serial.println("");
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   { 
     delay(100);  
     Serial.print('.'); 
   }
   Serial.println("");
   Serial.print("Iniciado STA:\t");
   Serial.println(ssid);
   Serial.print("IP address:\t");
   Serial.println(WiFi.localIP());
}

void posicion_inicial(void)
{
  servo1.write(ANGULO1);
  servo2.write(ANGULO2);
  servo3.write(ANGULO3);
  servo4.write(ANGULO4);
  servo5.write(ANGULO5);
}
