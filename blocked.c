#include"raylib.h"

bool isBlocked(Vector2 pos){
    //AB1
    if(pos.x>=118 && pos.x<=441
        && pos.y>=688 && pos.y<=945)
        return true;
    
    //CDS
    if(pos.x>=1091 && pos.x<=1446
        && pos.y>= 750 && pos.y<= 970)
        return true;
    //Rocket
    if(pos.x>=894 && pos.x<=979
        && pos.y>= 291&& pos.y<= 394)
        return true;

    //AB2
    if(pos.x>=49 && pos.x<=414
        && pos.y>=4  && pos.y<= 194)
        return true;

    return false;
}