void envoimessage(){

/*Traitement de la ligne1*/


       matrix.setTextSize(1); 
       int curseur= ((64-(ligne1.length()*6))/2);
       matrix.setTextColor(couleur1,0);
       matrix.setCursor(curseur, 1);
       matrix.print(ligne1);  
         

 
       curseur= ((64-(ligne2.length()*6))/2);
       matrix.setTextColor(couleur2,0);
       matrix.setCursor(curseur, 9);
       matrix.print(ligne2);  
       

      if (ligne3.length()<6){
      curseur= ((64-(ligne3.length()*12))/2);
      matrix.setTextColor(couleur3,0);
      matrix.setTextSize(2);  
      matrix.setCursor(curseur, 17);
      matrix.print(ligne3);
      }

      else{
      alignement=3;
      }
      
      
 }

      
  
