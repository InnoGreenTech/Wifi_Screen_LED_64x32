// définition des couleurs (mot clé en anglais)
#define BLACK    0x0000 // noir
#define BLUE     0x000F // Bleu
#define RED      0x0F00 // Rouge 
#define GREEN    0x00F0 // Vert
#define CYAN     0x00FF // Cyan 
#define MAGENTA  0x0F0F // Magenta
#define YELLOW   0x0FF0 // Jaune
#define WHITE    0x0FFF // Blanc





uint16_t color(String transformcouleur){

  if (transformcouleur=="BLANC"){return WHITE;}
  if (transformcouleur=="BLEU"){return BLUE;}
  if (transformcouleur=="ROUGE"){return RED;}
  if (transformcouleur=="VERT"){return GREEN;}
  if (transformcouleur=="CYAN"){return CYAN;}
  if (transformcouleur=="MAGENTA"){return MAGENTA;}
  if (transformcouleur=="JAUNE"){return YELLOW;}
  if (transformcouleur=="BLANC"){return WHITE;}
  
}

int aligne(String transformalignement){
  if (transformalignement=="FIXE"){return 1;}
  if (transformalignement=="SCROLL"){return 2;}
  if (transformalignement=="3LIGNE"){return 3;}
  if (transformalignement=="4LIGNE"){return 4;}
}
