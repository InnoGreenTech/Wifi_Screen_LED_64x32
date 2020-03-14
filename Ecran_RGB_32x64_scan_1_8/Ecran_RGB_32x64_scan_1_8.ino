
#include <EEPROM.h> // Gestion de la mémoire de type eeprom pour la sauvegarde des choix

#define MEM_NAME_MODULE     1   //Name of module
#define MEM_ADRESS_SERVER   22  // adress of server php
#define MEM_PORT_SERVER     43  // Port of server
#define MEM_PERIOD          50  // Period to send datas in seconds
#define MEM_ID   53     // Identifiant de l'afficheur

#define MEM_ERREUR   150 // Message lors de la perte de connexion wifi
#define MEM_SSID     200 // SSID of connection
#define MEM_PASSWORD 251 // Password wifi connection



// Paramétrage du WIfi

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <wchar.h> 
#include <WString.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266Ping.h>
#include <ESP8266HTTPClient.h>
#include <TimeLib.h>              // To handle time
#include <NtpClientLib.h>

String ssid="";
String password="";
int    config_mode=0;
unsigned long delay_reboot;       // delay during the page of connection is open befor reboot
#define DELAY_REBOOT 120000 

unsigned long ntp_refrech;       
#define NTP_REFRECH  36000000   // 
ESP8266WebServer server(80);

/* setting to update server */

#include <ESP8266HTTPUpdateServer.h>
const char* update_path = "/firmware";
const char* update_username = "innogreentech";
const char* update_password = "innogreentech";
 
ESP8266HTTPUpdateServer httpUpdater;

uint16_t port ;          // port de communication du client
uint16_t id ; 
String host = "";       //intra.lepal.local"; // ip or dns du client
String lienrequette=""; //Lien de la requette
String nomafficheur="";  // Nom de l'afficheur
String messageerreur=""; // Message d'erreur lors de probléme de connexion


byte statut_serveur=0; 
byte nb_cycle_cycle_lose_wifi=0; 
 
#define SERVEUR_SUCCES  0  //   Drapeau de connexion au serveur réussis
#define SERVEUR_DESABLE     1  //   Permet de désactiver le serveur
#define PREMIER_CYCLE   2 // Premier passage 
#define DEUXIEME_TENTATIVE 3// Second tentative tu send the message



unsigned long  time_out_serveur=0;               // Si le serveur ne répond pas une requette sera renvoyée
#define       TIME_OUT_SERVEUR  300000        // durée de consultation en millisecondes de cette requette

// Variables des 3 messages:

String ligne1="";         //Message 1
String ligne2="";         //Message 2
String ligne3="";        //Message 3

String ligne1message1="";
String ligne2message1="";
String ligne3message1="";

String ligne1message2="";
String ligne2message2="";
String ligne3message2="";

String ligne1message3="";
String ligne2message3="";
String ligne3message3="";

String message;

uint16_t couleur1;
uint16_t couleur2;
uint16_t couleur3;

uint16_t ligne1couleur1=0x0FFF;         //Couleurs du message 1
uint16_t ligne2couleur1=0x0FFF;         
uint16_t ligne3couleur1=0x0FFF;

uint16_t ligne1couleur2=0x0FFF;         //Couleurs du message 2
uint16_t ligne2couleur2=0x0FFF;
uint16_t ligne3couleur2=0x0FFF;

uint16_t ligne1couleur3=0x0FFF;         //Couleurs du message 3
uint16_t ligne2couleur3=0x0FFF;
uint16_t ligne3couleur3=0x0FFF;

int alignement1=1;      //ajustement du texte 1
int alignement2=1;      //ajustement du texte 2
int alignement3=1;      //ajustement du texte 3

int alignement=1;       //

#define FIXE 1         // Alignement fixe
#define SCROLL 2       // Texte en mouvement
#define SCROLL_AUTO 3  // Scroll pour 3° ligne
#define VITESSE    20  // vitesse de défilement en milliseconde

byte duree=7;           // Durée d'affichage des messages en secondes
String reception;               // Variable pour la réception sur le port série
unsigned long millisecondes=30;     // Durée d'affichage en millisecondes
unsigned long derniermessage=0;    // Temps du dernier envoi de message
unsigned long time_scroll;         // 
int wd;
int i;

byte acti_message=1;            //Activation

#define MESS_1 0             //Validation de la diffusion du message 1
#define MESS_2 1             //Validation de la diffusion du message 2
#define MESS_3 2             //Validation de la diffusion du message 3

byte indexmessage=1;                  // indexmessage de lecture du message en cours
byte intensite=1;                       //intensité lumineuse souhaitée
byte nouveau=0;                    // information d'un nouveau message

byte a; 

// Paramétrage pour la gestion de l'écran

#include <Adafruit_GFX.h>   // Core graphics library
#include "ESP8266RGBmatrixPanel.h"   // modifier pour scan 1/8

extern "C" {
            #include "user_interface.h"
            }
//G1  R1 |
//GND B1 |
//G2  R2 |
//GND B2  |
//B   A   |
//D   C  |
//LAT CLK|
//GND OE |
// !!!IMPORTANT for ABCD-Pins see readme IMPORTANT!!!
//CLK MUST BE CONNECTED ON D0!  
//OE connected with LAT

uint8_t CLK = D0;
uint8_t LAT = D1;
uint8_t R1 = D3;
uint8_t G1 = D4;
uint8_t BL1 = D5;
uint8_t R2 = D6;
uint8_t G2 = D7;
uint8_t BL2 = D8;

ESP8266RGBmatrixPanel matrix(R1, G1, BL1, R2, G2, BL2, LAT);


// Version avec timer soft*

os_timer_t updateTimer;

void updateDisplay(void * pArg)
{
  matrix.updateDisplay();
}

    String  date;             
    String  currently_time;         
    String  ip_address;      
    String  gate_way; 
    String  mac_address;  

    char          name_module[20];          // name of module
    String        ref_module;               // référence du module
    String        version_module;           // version of module
    char          ip_server[15];            // adress ip of the module
    int unsigned  port_server;              // port of server
    String        local_mac;                // adress mac of the module
    String        local_ip;                 // adress ip of module

    int           period;                   // period to sent datas at server
    unsigned long delay_sent;               // delay to send a new message in milliseconds
    unsigned long last_message;
    int           index_average;


void setup() {
    system_update_cpu_freq(160);
  
  /*initiailisation du timer de rafraichissement d'écrans */


    system_timer_reinit ();
    ets_timer_setfn(&updateTimer, updateDisplay, NULL);


    matrix.setTextWrap(false);


    matrix.fillScreen(0);

    matrix.updateDisplay();
    Serial.begin(115200);
    Serial.println("");
    Serial.println("Rafraichissement de l'écran");
    
  
  
  reception.reserve(60);
  




  
  EEPROM.begin(512);                              // allocations  de 128 adresses Mémoires

              char carac='1';   // Name of module
              int a=0;
              String read_mem="";
              while (!(carac=='\0')&&a<20){carac=char (EEPROM.read(MEM_NAME_MODULE+a));read_mem+= carac; a++;} 
              if (read_mem!='\0'||a==20){read_mem=F("InnoGreenTech");}
              int c = read_mem.length() + 1;                               // longueur de la chaîne de caractéres
              read_mem.toCharArray(name_module, c); 
             // Serial.println(name_module);        
              
              read_mem="";    // read memory ip adress server
              carac='1';
              a=0;
              while (!(carac=='\0')&&a<20){carac=char (EEPROM.read(MEM_ADRESS_SERVER+a));read_mem+= carac; a++;}
              if (read_mem!='\0'||a==20){read_mem=F("InnoGreenTech");} 
              c = read_mem.length() + 1;       
              read_mem.toCharArray(ip_server, c);
              Serial.println(ip_server);     

                         
              byte mem[2];
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(MEM_PORT_SERVER+a);}     // load the port server         
              port_server= mem[0]|mem[1]<<8;
              
              for (int a=0;a<3;a++){mem[a]= EEPROM.read(MEM_PERIOD+a);}          // load the time period
              period= mem[0]|mem[1]<<8;
              delay_sent=period*1000;

              carac='1';                
              a=0;
              while (!(carac=='\0')&&a<100){carac=char (EEPROM.read(MEM_SSID+a));
              if (!(carac=='\0')){ssid +=carac;} a++;}  //récupération du lien d'information
              if (ssid=='\0'||a>50){ssid=F("");}
            
              carac='1';
              a=0;
              while (!(carac=='\0')&&a<100){carac=char (EEPROM.read(MEM_PASSWORD+a));
              if (!(carac=='\0')){password +=carac;} a++;}  //récupération du lien d'information
              if (password=='\0'||a>50){password=F("");}
  


   /*Connexion wifi*/
   WiFi.mode(WIFI_STA);
   
   c =ssid.length()+1;
   char char_ssid[50];
   ssid.toCharArray(char_ssid, c);

   c =password.length()+1;
   char char_password[50];
   password.toCharArray(char_password, c);

   WiFi.begin(char_ssid,char_password);

              WiFi.begin(char_ssid,char_password);
           
             unsigned long time_out_connection = millis();
              while (WiFi.status() != WL_CONNECTED)
              {
                if (millis() - time_out_connection > 20000)
                {
                  Serial.println F("");
                  Serial.println F ("connection Wifi fail !");
            
                  break;
                }
                delay(100);
                Serial.print('-');
              }
   
   
   if ( WiFi.status()!= WL_CONNECTED)

      {
        Serial.println F ("Open setting gate !");
        WiFi.disconnect();
        WiFi.mode(WIFI_AP); 
        config_mode=1;
        delay(200);
        WiFi.softAP("InnoGreenTech", "innogreentech");
        server.on ( "/index.html", handleRoot );    // go to set up wifi page
        delay(100);
        server.on ("/style.css", cssRoot);     // envoi au fichier de configuration de style
        local_mac = WiFi.macAddress();
        delay(100);
        server.begin();
        delay_reboot=millis();

        ets_timer_arm_new(&updateTimer,1250, true,0);  // true 1250*/
        matrix.setTextWrap(false);      // Préparation du message avec l'adresse ip de connexion
      
        ligne1=F("Inno");
        ligne2=F("GreenTech");
       
        ligne3=F("Non connecté");
        
        couleur1=0x0030;
        couleur2=0x0030;
        couleur3=0x0110;
        
        envoimessage();  
        
      }

   
   else
    {             
    
      /*Configuration de la synchronisation de l'heure */

     NTP.begin("pool.ntp.org", 1, true);  //configuration de la récupération de la date,  Serveur+1 heure, Heure été/hivers
     NTP.stop ();
     // NTP.setInterval(360000);                // Toutes les 10 heures
  

    /*information of module*/

     local_ip=WiFi.localIP().toString().c_str();              
     local_mac=WiFi.macAddress();//.toString().c_str();
     gate_way=WiFi.gatewayIP().toString().c_str();
     ref_module="RGB_32x64_screen";
     version_module="V1";

     Serial.print(F("référence:"));Serial.println(ref_module);
     Serial.print(F("Version:"));Serial.println(version_module);
     Serial.print(F("Adresse IP:"));Serial.println(local_ip);
     Serial.print(F("Adresse MAC:"));Serial.println(local_mac); 
     Serial.println(WiFi.gatewayIP());
     Serial.println(WiFi.dnsIP(1)); 
       
     delay(100);

      /* Configuration du serveur Web*/
      
      server.on ( "/index.html", indexRoot );    // Renvoi à la page de index
       delay(100);
      server.on ( "/", indexRoot );    // Renvoi à la page de index
       delay(100);
      server.on ("/style.css", cssRoot);     // envoi au fichier de configuration de style
       delay(100);
      server.on ("/setup.html", setupRoot);     // envoi au fichier de configuration de style
      delay(100);
      server.on ( "/add_module.csv", add_module );    // Page for add or modify  module by php server 
              delay(100);
      
      httpUpdater.setup(&server, update_path, update_username, update_password);
      
      // on commence à écouter les requettes venant de l'exterieur
      server.begin();
       delay(100); 

      Serial.println(WiFi.macAddress());
      Serial.println("Numero de serie: AF 03/2018 16");
      Serial.println("Version: V6.");   // Change update OTA methode


/*Activation du rafraîchissement d'écran 50/secondes */


        ets_timer_arm_new(&updateTimer,1250, true,0);  // true 1250*/
        matrix.setTextWrap(false);      // Préparation du message avec l'adresse ip de connexion
      
        ligne1=F("Inno");
        ligne2=F("GreenTech");
       
        ligne3=WiFi.localIP().toString().c_str();
        
        couleur1=0x0030;
        couleur2=0x0030;
        couleur3=0x0110;
        
        envoimessage();        

       }

}

void loop() {


    server.handleClient();           //Lecture des requettes

    
    if (config_mode==0)             
             {

             /* gestion de l'affichage des message */     
            
               if (nouveau||((acti_message>1)&&(millis()-derniermessage>millisecondes)))  // Traitement des messages
               {
                   matrix.fillScreen(0);      // Effacement de l'affichage
                   i=0;                       // Remise à zéro de l'index
                   
             
                if (bitRead(acti_message,MESS_1)&&indexmessage==1){
                  ligne1=ligne1message1;
                  ligne2=ligne2message1;
                  ligne3=ligne3message1;
                  couleur1=ligne1couleur1;
                  couleur2=ligne2couleur1;
                  couleur3=ligne3couleur1;
                  couleur1=convert_intensite(couleur1);
                  couleur2=convert_intensite(couleur2);
                  couleur3=convert_intensite(couleur3);      
                  alignement=alignement1;      
                  matrix.setTextColor(couleur1,0);
                  if (alignement==1){envoimessage();}
                  indexmessage=2;
                  nouveau=0;
                  derniermessage=millis();
                  goto finif;}
                else if (!bitRead(acti_message,MESS_1)&&indexmessage==1){indexmessage=2;} 
                
            
                else if(bitRead(acti_message,MESS_2)&&indexmessage==2){
                  ligne1=ligne1message2;
                  ligne2=ligne2message2;
                  ligne3=ligne3message2;
                  couleur1=ligne1couleur2;
                  couleur2=ligne2couleur2;
                  couleur3=ligne3couleur2;
                  couleur1=convert_intensite(couleur1);
                  couleur2=convert_intensite(couleur2);
                  couleur3=convert_intensite(couleur3);      
                  alignement=alignement2;
                  matrix.setTextColor(couleur2,0);
                  if (alignement==1){envoimessage();}
                  indexmessage=3;
                  nouveau=0;
                  derniermessage=millis();
                  goto finif;}
                else if (!bitRead(acti_message,MESS_2)&&indexmessage==2){indexmessage=3;}
                
                if(bitRead(acti_message,MESS_3)&&indexmessage==3){
                  ligne1=ligne1message3;
                  ligne2=ligne2message3;
                  ligne3=ligne3message3;
                  couleur1=ligne1couleur3;
                  couleur2=ligne2couleur3;
                  couleur3=ligne3couleur3;
                  couleur1=convert_intensite(couleur1);
                  couleur2=convert_intensite(couleur2);
                  couleur3=convert_intensite(couleur3);
                  alignement=alignement3;
                  matrix.setTextColor(couleur3,0);
                  if (alignement==1){envoimessage();}
                  indexmessage=1;
                  nouveau=0;
                  derniermessage=millis();}
                else if (!bitRead(acti_message,MESS_3)&&indexmessage==3){indexmessage=1;} 
                  finif:
                  indexmessage=indexmessage;    
                  
                }


                 /* Ntp consult */   

                            
                 if (millis()-ntp_refrech>NTP_REFRECH)
                    {
                      ets_timer_disarm(&updateTimer);  // désactivation du rafraîchissement d'écran
                      NTP.begin("pool.ntp.org", 1, true);  //configuration de la récupération de la date,  Serveur+1 heure, Heure été/hivers
                      NTP.stop ();                         // End of synchronisation
                      ets_timer_arm_new(&updateTimer,1250, true,0);            
                      ntp_refrech=millis();
                    }      
            
                
                if ((alignement==2||alignement==3)&millis()-time_scroll>VITESSE){
                wd = ligne3.length()*12;
                matrix.setTextColor(couleur3,0);
                matrix.setTextSize(2);
                if (alignement==2) {matrix.setCursor(63-i,9);}
                if (alignement==3) {matrix.setCursor(63-i,17);}
                matrix.print(ligne3);
                i = (i+1)%(wd+63);  //+1
                time_scroll=millis();              // Régle la vitesse de défilement
               
               } 
              
             }

      else
            {
              if (millis()-delay_reboot>DELAY_REBOOT){ESP.reset();}
            }

}
