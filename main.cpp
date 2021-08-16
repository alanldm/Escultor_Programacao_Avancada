#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "sculptor.h"

using namespace std;

int main(){
    Sculptor aruco(100, 100, 100);

    //-----------------------------------------------Gerador do Aruco --------------------------------------------------------
    aruco.setColor(255, 255, 255, 1);
    aruco.putBox(0, 18, 0, 18, 0 , 0);

    aruco.setColor(0, 0, 0, 1);
    aruco.putBox(1, 5, 1, 5, 0 ,0);
    aruco.putBox(7, 11, 1, 5, 0 ,0);
    aruco.putBox(13, 17, 1, 5, 0 ,0);
    aruco.putBox(1, 5, 7, 11, 0 ,0);
    aruco.putBox(7, 11, 7, 11, 0 ,0);
    aruco.putBox(13, 17, 7, 11, 0 ,0);
    aruco.putBox(1, 5, 13, 17, 0 ,0);
    aruco.putBox(7, 11, 13, 17, 0 ,0);
    aruco.putBox(13, 17, 13, 17, 0 ,0);

    srand(time(NULL));

    int i, inicio=2, fim=4;
    for(int k=0; k<3; k++){
        for(i=inicio; i<=fim; i++){
            for(int j=2; j<=4; j++){
                int cor = rand() % 2;
                if(cor==1){
                    cor = 255;
                }
                aruco.setColor(cor, cor, cor, 1);
                aruco.putVoxel(i, j, 0);
            }
        }
        inicio=inicio+6;
        fim=fim+6;
    }

    inicio=2, fim=4;
    for(int k=0; k<3; k++){
        for(i=inicio; i<=fim; i++){
            for(int j=8; j<=10; j++){
                int cor = rand() % 2;
                if(cor==1){
                    cor = 255;
                }
                aruco.setColor(cor, cor, cor, 1);
                aruco.putVoxel(i, j, 0);
            }
        }
        inicio=inicio+6;
        fim=fim+6;
    }

    inicio=2, fim=4;
    for(int k=0; k<3; k++){
        for(i=inicio; i<=fim; i++){
            for(int j=14; j<=16; j++){
                int cor = rand() % 2;
                if(cor==1){
                    cor = 255;
                }
                aruco.setColor(cor, cor, cor, 1);
                aruco.putVoxel(i, j, 0);
            }
        }
        inicio=inicio+6;
        fim=fim+6;
    }

    //--------------------------------------------------------------------------------------------------------------------------------------------



    int c = 20;

    aruco.setColor(79, 79, 79, 1);
    aruco.putBox(c+0, c+3, c+0, c+1, 1, 2);

    aruco.setColor(75, 0, 130, 1);
    aruco.putBox(c, c+3, c+0, c+1, 3, 8);

    aruco.setColor(0, 255, 255, 1);
    aruco.putBox(c-2, c+5, c+0, c+1, 9, 14);

    aruco.setColor(222, 184, 135, 1);
    aruco.putBox(c-2, c-1, c+0, c+1, 9, 12);
    aruco.putBox(c+4, c+5, c+0, c+1, 9, 12);

    aruco.setColor(222, 184, 135, 1);
    aruco.putBox(c-1, c+4, c+0, c+1, 15, 20);

    aruco.setColor(139, 69, 19, 1);
    aruco.putBox(c-1, c+4, c+0, c+1, 20, 20);

    aruco.setColor(139, 69, 19, 1);
    aruco.putBox(c-1, c+4, c+1, c+1, 17, 19);

    aruco.setColor(139, 69, 19, 1);
    aruco.putVoxel(c-1, c, c-1);
    aruco.putVoxel(c+4, c, c-1);

    aruco.setColor(205,133,63, 1);
    aruco.putVoxel(c+1, c, c-4);
    aruco.putVoxel(c+2, c, c-4);

    aruco.setColor(0, 0, 0, 1);
    aruco.putVoxel(c+1, c, c-2);
    aruco.putVoxel(c+3, c, c-2);

    aruco.setColor(255, 255, 255, 1);
    aruco.putVoxel(c, c, c-2);
    aruco.putVoxel(c+2, c, c-2);

    aruco.writeOFF((char*)"D:/aruco.off");
    return 0;
}
