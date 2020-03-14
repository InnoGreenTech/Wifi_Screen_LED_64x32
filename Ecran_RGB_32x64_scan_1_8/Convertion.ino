/* Conversion du texte en latin */





void convert(){

unsigned char a;
int i=0;

byte conversion [29]={            // 154 à 180 UTF vers Ascii étendu
     133,  //à  
     160, //a  
     131, //â   
     131, //    
     132, // ä  
     134, // a  
     145, // ae
     135, // ç  
     138, //è   
     130, //é  
     136, // ê 
     137, // ë 
     141, // i  
     161, // i 
     140, //î   
     139, //ï   
     164, //n   
     164, //ñ   
     149, //o   
     162, //o   
     147, //ô   
     147, //o  
     148, //ö  
     148, //    
     155, //    
     151, //ù  
     162, //    
     150, //û  
     129 // ï  
     };
     
  i=reception.length()+1;
  char ligne1[i]; 
  reception.toCharArray(ligne1,i); 

  reception="";
  
  for (int c=0;c<(i-1);c++){
    
               a=ligne1[c];
               if (a<127) {reception +=char(a);}        // conversion en Ascii étendu
               if ((a>159)&&(a<186)) {a=a-160  ;
               a=conversion[a];
               reception +=char(a);} 
               
              }


  
  }
