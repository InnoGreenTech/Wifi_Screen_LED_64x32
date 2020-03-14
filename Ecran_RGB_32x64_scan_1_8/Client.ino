void requet(){

 Serial.println("requete");

    
    if ( WiFi.status()!= WL_CONNECTED)
    
        {
        if (nb_cycle_cycle_lose_wifi<2)       // send message message if wifi is lose more two time  
                      {
                      nb_cycle_cycle_lose_wifi++;
                      time_out_serveur= time_out_serveur+30000;
                      bitClear(statut_serveur, SERVEUR_SUCCES);
                      return;              
                      }  
        if (nb_cycle_cycle_lose_wifi<5)         // Use for a new test in 20 secondes
                      {
                      nb_cycle_cycle_lose_wifi++;
                      ligne1message1="";ligne2message1="";ligne3message1=messageerreur;alignement1=2;acti_message=1;
                      time_out_serveur= time_out_serveur+30000;
                      nouveau=1;
                      bitClear(statut_serveur, SERVEUR_SUCCES);
                      return;  

                      }
        ESP.reset();  // if the lost of wifi is to long reset modul

        }
 
    if (bitRead(statut_serveur,SERVEUR_DESABLE)){time_out_serveur= millis();return;} // if adress server is empty
 
    ets_timer_disarm(&updateTimer);                              // désactivation du rafraîchissement d'écran           
    WiFiClient client;                                          // Connexion au serveur

      

      if (!client.connect(host, port))  // Si la connexion n'est pas établie Création d'un message permettant de connaître le probléme
          {                  
        
           if(!bitRead(statut_serveur,PREMIER_CYCLE)){bitSet(statut_serveur,PREMIER_CYCLE);}   // On maintien l'adresse Ip jusqu'à la seconde requette
          
           else 
             {
              if (nb_cycle_cycle_lose_wifi<5)                                                 // Use for a new test in 20 secondes
                      {
                      nb_cycle_cycle_lose_wifi++;
                      client.stop();
                      time_out_serveur= time_out_serveur+30000;
                      ets_timer_arm_new(&updateTimer,1250, true,0);
                      return;
                      }
              ligne1message1=NTP.getDateStr();ligne2message1="";ligne3message1=messageerreur;alignement1=1;nouveau=1;
             }
         
           acti_message=1;                                        
           bitClear(statut_serveur, SERVEUR_SUCCES);
           client.stop(); 
           time_out_serveur= time_out_serveur+30000;
           ets_timer_arm_new(&updateTimer,1250, true,0);
           return;
          }


      
      client.print("GET ");
      client.print(lienrequette);
      client.print("?select_attraction=");
      client.print(id);
      client.print("&ip_afficheur=");
      client.print(WiFi.localIP());
      client.print("&statut=");
              if (bitRead (statut_serveur,SERVEUR_SUCCES)){ client.println("alive HTTP/1.1");}
              else {client.println("connect HTTP/1.1");}
              
     // client.println("GET /reglage.html?TMAX=30&&TMIN=5 HTTP/1.1");
      client.print("Host:");
      client.println(nomafficheur);
      client.println("Connection: close");
      client.println();                                              //fin de la requet
      client.stop();      //déconnexion
      bitSet(statut_serveur, SERVEUR_SUCCES);                       // Enregistre que le serveur est bien connecté
      bitClear(statut_serveur,DEUXIEME_TENTATIVE);
      nb_cycle_cycle_lose_wifi=0;      
      time_out_serveur= millis();
      ets_timer_arm_new(&updateTimer,1250, true,0);

  
}
