
void indexRoot(){ 

      /* Formulaire Activation des messages */

      
      if ( server.hasArg("MESS1")) {       // si reception 
      bitSet(acti_message, MESS_1);}  // Activation du message 1
      else if( !server.hasArg("MESSAGE")) {bitClear(acti_message, MESS_1);}                           // Désactivation du message 1
       
      if ( server.hasArg("MESS2")) {       // si reception 
      bitSet(acti_message, MESS_2);}  // Activation du message 2
      else if( !server.hasArg("MESSAGE")){bitClear(acti_message, MESS_2);}                           // Désactivation du message 2
       
      if ( server.hasArg("MESS3")) {       // si reception 
      bitSet(acti_message, MESS_3);}  // Activation du message 3
      else if( !server.hasArg("MESSAGE")){bitClear(acti_message, MESS_3);}                           // Désactivation du message 3
      
      if ( server.hasArg("DUREE") ) {       // si reception
      reception = server.arg("DUREE");
      duree=reception.toInt(); 
      millisecondes=duree*1000; 
      }
      if ( server.hasArg("INTENSITE") ) {       // si reception
      reception = server.arg("INTENSITE");
      intensite=reception.toInt();
      nouveau=1;
      }      

      /* Fomulaire d'envoi des messages*/

      
       if ( server.hasArg("MESSAGE") ) {       // si reception message1
       reception=server.arg("MESSAGE");
       indexmessage=reception.toInt();}
       
       if ( server.hasArg("LIGNE1") ) {       // si reception message1
       reception=server.arg("LIGNE1");
       convert();
       nouveau=1;
            if (indexmessage==1){ligne1message1=reception;}
            if (indexmessage==2){ligne1message2=reception;}
            if (indexmessage==3){ligne1message3=reception;}}
     
       if ( server.hasArg("COULEUR1") ) {       
       reception=server.arg("COULEUR1");
       couleur1=color(reception);
            if (indexmessage==1){ligne1couleur1=couleur1;}
            if (indexmessage==2){ligne1couleur2=couleur1;}
            if (indexmessage==3){ligne1couleur3=couleur1;}}

       if ( server.hasArg("LIGNE2") ) {       // si reception message1
       reception=server.arg("LIGNE2");
       convert();
            if (indexmessage==1){ligne2message1=reception;}
            if (indexmessage==2){ligne2message2=reception;}
            if (indexmessage==3){ligne2message3=reception;}}
     
       if ( server.hasArg("COULEUR2") ) {       
       reception=server.arg("COULEUR2");
       couleur2=color(reception);
            if (indexmessage==1){ligne2couleur1=couleur2;}
            if (indexmessage==2){ligne2couleur2=couleur2;}
            if (indexmessage==3){ligne2couleur3=couleur2;}}

       if ( server.hasArg("LIGNE3") ) {       // si reception message1
       reception=server.arg("LIGNE3");
       convert();
            if (indexmessage==1){ligne3message1=reception;}
            if (indexmessage==2){ligne3message2=reception;}
            if (indexmessage==3){ligne3message3=reception;}}
     
       if ( server.hasArg("COULEUR3") ) {       
       reception=server.arg("COULEUR3");
       couleur3=color(reception);
            if (indexmessage==1){ligne3couleur1=couleur3;}
            if (indexmessage==2){ligne3couleur2=couleur3;}
            if (indexmessage==3){ligne3couleur3=couleur3;}}     


       
       if ( server.hasArg("ALIGNEMENT") ) {       // si reception message1
       reception=server.arg("ALIGNEMENT");
       alignement=aligne(reception);
            if (indexmessage==1){alignement1=alignement;}
            if (indexmessage==2){alignement2=alignement;}
            if (indexmessage==3){alignement3=alignement;}}    
   
       server.send ( 200, "text/html", indexPage() );   // envoi de la page


    }
  


String indexPage(){
  String page =F("<!DOCTYPE html> <html lang=fr-FR> <head> <meta charset='utf-8'><link rel='stylesheet'type='text/css'href='style.css'><title>Afficheur</title></head>"); 
         page +=F("<body>");
         
         page += F("<nav><ul id='menu'>");
         page += F("<li><a href='index.html'> Accueil </a></li>");
         page += F("<li><a href='setup.html'> Setup </a></li>");
         page += F("<li><a href='/firmware'> Update </a></li></nav>");
         
         page +=F("<div id='page'>");
         page +=F("<header><h1>Afficheur ");
         page +=name_module;
         page +=F("</h1></header>");
         page +=F("<div id='corp'>");
         page +=F("<section id='datedujour'><h2>");
         page +=NTP.getDateStr();
         page +=F("</h2><h3>");
         page +=NTP.getTimeStr();
         page +=F("</h3></section>");

         page +=F("<section id='configuration'>");
         page +=F("<h2> Configuration des messages</h2>"); 
         page +=F("<form method='post' accept='' >");
         page +=F("<p>");
         page +=F("<label>Activation du message 1</label>");
         page +=F("<input type='radio' name='MESS1'  value='1' />");
  //       page += F("<label>    Désactivation du message 1</label>");
 //        page += F("<input type='radio' name='MESS1'  value='0' />");
         page +=F("<br/>");
         page +=F("<br/>");
         page +=F("<label>Activation du message 2</label>");
         page +=F("<input type='radio' name='MESS2'  value='1'/>");
  //       page +=F("<label>    Désactivation du message 2</label>");
 //        page +=F("<input type='radio' name='MESS2'  value='0' />");
         page +=F("<br/>");
         page +=F("<br/>");
         page +=F("<label>Activation du message 3</label>");
         page +=F("<input type='radio' name='MESS3'  value='1'  />");
  //       page +=F("<label>    Désactivation du message 3</label>");
  //       page +=F("<input type='radio' name='MESS3'  value='0' />");
         page +=F("<br/>");
         page +=F("<br/>");
         page +=F("<label>Durée d'affichage en secondes:<br/></label>");
         page +=F("<input type='number' name='DUREE' id='DUREE' step='1'required  value='");page +=duree; page +=F("'/>");
         page +=F("<br/>");
         page +=F("<br/>");   
         page +=F("<label>Intensité d'affichage de  0 à 4:<br/></label>");
         page +=F("<input type='number' name='INTENSITE' id='INTENSITE' step='1' max='4' required value='");page +=intensite; page +=F("'/>");
         page +=F("<br/>");
         page +=F("<br/>");      
         page +=F("<input type='submit'  value='Envoi'>");        
         page +=F("</p>");
         page +=F("</form>");
         page +=F("</section>");

         page += F("<section id='message'>");
         page += F("<h2> Messages</h2>");
         page += F("<form method='post' accept='' >");
         page += F("<p>");
         
         page +=F("<label for='MESSAGE'>Choisir le message à envoyer:<br/></label>");
         page +=F("<select name='MESSAGE' id='MESSAGE'>");
         page +=F("<option value='1'>Message1</option>");
         page +=F("<option value='2'>Message2</option>");
         page +=F("<option value='3'>Message3</option>");
         page +=F("</select>");
         
         page +=F("<br/>");
         page +=F("<br/>");
         
         page += F("<label>Ligne 1:<br/></label>");
         page += F("<input type='texte' name='LIGNE1' id='LIGNE1' ' maxlength='12' />");
         page +=F("<br/>");   
         page +=F("<label for='COULEUR1'>Choisir la couleur:</label>");
         page +=F("<select name='COULEUR1' id='COULEUR1'>");
         page +=F("<option value='BLANC'>Blanc</option>");
         page +=F("<option value='BLEU'>Bleu</option>");
         page +=F("<option value='VERT'>Vert</option>");
         page +=F("<option value='ROUGE'>Rouge</option>");
         page +=F("<option value='CYAN'>Cyan</option>");
         page +=F("<option value='MAGENTA'>Magenta</option>");
         page +=F("<option value='JAUNE'>Jaune</option>");
         page +=F("</select>");
         
         page +=F("<br/>");
         page +=F("<br/>");
         
         page += F("<label>Ligne 2:<br/></label>");
         page += F("<input type='texte' name='LIGNE2' id='LIGNE2' ' maxlength='12' />");
         page +=F("<br/>");
         page +=F("<label for='COULEUR2'>Choisir la couleur:</label>");
         page +=F("<select name='COULEUR2' id='COULEUR2'>");
         page +=F("<option value='BLANC'>Blanc</option>");
         page +=F("<option value='BLEU'>Bleu</option>");
         page +=F("<option value='VERT'>Vert</option>");
         page +=F("<option value='ROUGE'>Rouge</option>");
         page +=F("<option value='CYAN'>Cyan</option>");
         page +=F("<option value='MAGENTA'>Magenta</option>");
         page +=F("<option value='JAUNE'>Jaune</option>");
         page +=F("</select>");
         
         page +=F("<br/>");
         page +=F("<br/>");

         page += F("<label>Ligne 3 (scroll mode):<br/></label>");
         page += F("<input type='texte' name='LIGNE3' id='LIGNE3' ' maxlength='60' />");
         page +=F("<br/>");
         page +=F("<label for='COULEUR3'>Choisir la couleur:</label>");
         page +=F("<select name='COULEUR3' id='COULEUR3'>");
         page +=F("<option value='BLANC'>Blanc</option>");
         page +=F("<option value='BLEU'>Bleu</option>");
         page +=F("<option value='VERT'>Vert</option>");
         page +=F("<option value='ROUGE'>Rouge</option>");
         page +=F("<option value='CYAN'>Cyan</option>");
         page +=F("<option value='MAGENTA'>Magenta</option>");
         page +=F("<option value='JAUNE'>Jaune</option>");
         page +=F("</select>");
         page +=F("<br/>");
         page +=F("<br/>");      
         page +=F("<label for='ALIGNEMENT'>Choisir la mise en forme du texte:</label>");
         page +=F("<select name='ALIGNEMENT' id='ALIGNEMENT'>");
         page +=F("<option value='FIXE'>Fixe</option>");
         page +=F("<option value='SCROLL'>Scroll</option>");
         page +=F("</select>");  
         
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
