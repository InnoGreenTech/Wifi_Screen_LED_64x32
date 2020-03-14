uint16_t   convert_intensite(uint16_t couleur){

uint16_t  couleurrouge=couleur& 0b0000111100000000;
uint16_t  couleurverte= couleur&0b0000000011110000;
uint16_t  couleurbleu= couleur& 0b0000000000001111;


if (intensite<4){
                for (a=intensite;a<4;a++){
                couleurrouge=couleurrouge>>1;
                couleurverte=couleurverte>>1;
                couleurbleu=couleurbleu>>1;
                }
                
                couleurrouge=couleurrouge& 0b0000111100000000;
                couleurverte= couleurverte&0b0000000011110000;
                 couleurbleu= couleurbleu&  0b0000000000001111;

                couleur=couleurrouge|couleurverte|couleurbleu;
                }



return couleur;
                
}
