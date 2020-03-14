
void setupRoot(){ 
  

      /* Formulaire Activation des messages */
      
      if ( server.hasArg("NOM") )        // si reception 
              { 
              reception=server.arg("NOM"); 
              int c = reception.length() + 1;                               
              if ( c>20){Serial.println(F("Nom trop long"));return;} 
              reception.toCharArray(name_module, c); 
              for (int i = 0; i < c; i++) { 
                                            EEPROM.write((i+MEM_NAME_MODULE),reception[i]);  // save adresse IP in EEPROM
                                            }  
              } 

      if ( server.hasArg("IP") )        // if empty server is not use
              {      
              reception=server.arg("IP");
              int c = reception.length() + 1;         // longueur de la chaîne de caractéres                    
              if ( c>15){ Serial.println(F("adresse ip invalide")); return;}
              reception.toCharArray(ip_server, c); 
              for (int i = 0; i < c; i++) { 
                                            EEPROM.write((i+MEM_ADRESS_SERVER),reception[i]);  // save adresse IP in EEPROM
                                            }  
              }

         

      if ( server.hasArg("PORT") ) {       // si reception
              reception = server.arg("PORT");
              int c =reception.toInt();
              port_server= c;      
              for (int a=0;a<2;a++){EEPROM.write(MEM_PORT_SERVER+a ,c);c=c>>8;} 
               }

       
               
       EEPROM.commit();     // Enregistrement dnas la mémoire flash
       server.send ( 200, "text/html", setupPage() );   // envoi de la page

    }
  


String setupPage(){
  String page =F("<!DOCTYPE html> <html lang=fr-FR> <head> <meta charset='utf-8'><link rel='stylesheet'type='text/css'href='style.css'><title>Afficheur</title></head>"); 
         page +=F("<body>");
         
         page += F("<nav><ul id='menu'>");
         page += F("<li><a href='index.html'> Accueil </a></li>");
         page += F("<li><a href='setup.html'> Setup </a></li>");
         page += F("<li><a href='/firmware'> Update </a></li></nav>");
         
         page +=F("<div id='page'>");
         page +=F("<header><h1>Afficheur ");
         page +=ref_module;
         page +=F("</h1></header>");
         page +=F("<div id='corp'>");
         page +=F("<section id='datedujour'><h2>");
         page +=NTP.getDateStr();
         page +=F("</h2><h3>");
         page +=NTP.getTimeStr();
         page +=F("</h3></section>");

         page +=F("<section id='configuration'>");
         page +=F("<h2> Configuration de l'afficheur</h2>"); 
         page +=F("<form method='get' accept='' >");
         
         page +=F("<br/>");
         page +=F("<br/>");
                  
         page += F("<label>Nom de l'afficheur: </label><br/>");
         page += F("<input type='texte' name='NOM' id='NOM' maxlength='20' value='");page +=name_module;
         page +=F("' />");
         
         page +=F("<br/>");
         page +=F("<br/>"); 
                 
         page += F("<label>Adresse IP du serveur:<br/></label>");
         page += F("<input type='texte' name='IP' id='IP' maxlength='15' value='");page +=ip_server; page +=F("' />"); 
         
         page +=F("<br/>");
         page +=F("<br/>"); 
                 
         page += F("<label>Port du serveur:<br/></label>");
         page += F("<input type='texte' name='PORT' id='PORT' maxlength='15' value='");page +=port_server; page +=F("' />");   
              
         page +=F("<br/>");
         page +=F("<br/>");  

        
         page += F("<br/>");
         page += F("<br/>");
         
         page += F("<input type='submit'  value='Envoi'>");
         page += F("</p>");
         page += F("</form>");
         page += F("</section>");
     
         
         page +=F("</div>");
         page +=F("<footer><table><tr><td><a href='http://innogreentech.fr'>InnoGreenTech  </a></td><td></td><td><a href='mailto: info@innogreentech.fr'> Contactez moi</a></td></tr></table></footer>");
         page +=F("</body></html>"); 

return page;
}
