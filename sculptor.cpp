#include "sculptor.h"
#include "stdlib.h"
#include <fstream>

//Função construtora da classe Sculptor, alocando espaço dinamicamente para a matriz 3D que representará o espaço onde os voxels serão ativados para formar o desenho.
//Primeiramente, aloca-se um ponteiro para ponteiros para ponteiros(x->y->z).
//Esse primeiro ponteiro guardará ponteiros para ponteiros (y->z).
//Por fim, serão armazenados os ponteiros dos elementos z.
Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;

    v = new Voxel**[nx];
    for(int x=0; x<nx; x++){
        v[x] = new Voxel*[ny];
        for(int y=0; y<ny; y++){
            v[x][y]=new Voxel[nz];
        }
    }
    for(int x=0; x<nx; x++){
        for(int y=0; y<ny; y++){
            for(int z=0; z<nz; z++){
                cutVoxel(x,y,z);
            }
        }
    }
}

//Função destrutora da classe Sculptor, liberando os espaços alocados dinamicamente de trás para frente.
//Nesse sentido, apaga-se primeiro os elementos de z que precisam dos ponteiros de x e y. Em seguida, apaga-se os ponteiros de y que precisam somente da dimensão x.
//Por fim, deleta-se o ponteiro do eixo x.
Sculptor::~Sculptor(){
    for (int x = 0; x < nx; x++) {
        for (int y = 0; y < ny; y++) {
         delete[] v[x][y];
       }
    }
    for (int x = 0; x < nx; x++) {
        delete[] v[x];
    }
    delete[] v;
}

//Coloca as cores que serão passadas para o voxel específico!
void Sculptor::setColor (float _r, float _g, float _b, float _a){
    r = _r;
    g = _g;
    b = _b;
    a = _a;
}

//Método que cria um determinado voxel nas coordenadas x, y e z, passando-lhe sua cor, sua transparência e seu estado!
void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
    v[x][y][z].isOn = true;
}

//Método para desativar um determinado voxel, de coordenadas x, y e z!
void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn = false;
}

//Método utilizado para criar voxels em massa, desse modo, deve-se utilizar laços de repetição para percorrer essa grande matriz 3D!
//Funcionamento similar a função "putVoxel".
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int x=x0; x<=x1; x++){
        for(int y=y0; y<=y1; y++){
            for(int z=z0; z<=z1; z++){
                putVoxel(x, y, z);
            }
        }
    }
}

//Método utilizado para apagar voxels em massa, sendo assim, utiliza-se iterações para percorrer e desativar todos os cubos da matriz 3D!
//Funcionamento similar a função "cutVoxel".
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int x=x0; x<=x1; x++){
        for(int y=y0; y<=y1; y++){
            for(int z=z0; z<=z1; z++){
                cutVoxel(x, y, z);
            }
        }
    }
}

//Método para criar regiões aproximadamente esféricas. Desse modo, varre-se toda a matriz 3D e verifica-se quais voxels estão dentro do raio passado, ativando-os.
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int x=0; x<=nx; x++){
        for(int y=0; y<=ny; y++){
            for(int z=0; z<=nz; z++){
                if(((x-xcenter)*(x-xcenter)+(y-ycenter)*(y-ycenter)+(z-zcenter)*(z-zcenter))<=radius*radius){
                    putVoxel(x, y, z);
                }
            }
        }
    }
}

//Método para desativar regiões aproximadamente esféricas. Sendo assim, o algoritmo percorre a região de forma análoga ao método "putSphere", desativando-os.
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int x=0; x<=nx; x++){
        for(int y=0; y<=ny; y++){
            for(int z=0; z<=nz; z++){
                if(((x-xcenter)*(x-xcenter)+(y-ycenter)*(y-ycenter)+(z-zcenter)*(z-zcenter))<=radius*radius){
                    cutVoxel(x, y ,z);
                }
            }
        }
    }
}

//De forma análoga à região esférica, o elipsoide será criado ao se percorrer toda a matriz 3D e verificar a equação do elipsoide.
//Deve-se atentar também para as divisões.
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    if(rx!=0 && ry!=0 && rz!=0){
        for(int x=0; x<=nx; x++){
            for(int y=0; y<=ny; y++){
                for(int z=0; z<=nz; z++){
                    if((float)((((x-xcenter)*(x-xcenter))/(rx*rx))+(((y-ycenter)*(y-ycenter))/(ry*ry))+(((z-zcenter)*(z-zcenter))/(rz*rz)))<=1){
                        putVoxel(x, y ,z);
                    }
                }
            }
        }
    } else if(rx==0){
        for(int y=0; y<=ny; y++){
            for(int z=0; z<=nz; z++){
                if((float)((((y-ycenter)*(y-ycenter))/(ry*ry))+(((z-zcenter)*(z-zcenter))/(rz*rz)))<=1){
                    putVoxel(xcenter, y, z);
                }
            }
        }
    } else if(ry==0){
        for(int x=0; x<=nx; x++){
            for(int z=0; z<=nz; z++){
                if((float)((((x-xcenter)*(x-xcenter))/(rx*rx))+(((z-zcenter)*(z-zcenter))/(rz*rz)))<=1){
                    putVoxel(x, ycenter, z);
                }
            }
        }
    } else if(rz==0){
        for(int x=0; x<=nx; x++){
            for(int y=0; y<=ny; y++){
                if((float)((((x-xcenter)*(x-xcenter))/(rx*rx))+(((y-ycenter)*(y-ycenter))/(ry*ry)))<=1){
                    putVoxel(x, y, zcenter);
                }
            }
        }
    }
}

//Método para desativar regiões elipsoides!
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    if(rx!=0 && ry!=0 && rz!=0){
        for(int x=0; x<=nx; x++){
            for(int y=0; y<=ny; y++){
                for(int z=0; z<=nz; z++){
                    if((float)((((x-xcenter)*(x-xcenter))/(rx*rx))+(((y-ycenter)*(y-ycenter))/(ry*ry))+(((z-zcenter)*(z-zcenter))/(rz*rz)))<=1){
                        cutVoxel(x, y ,z);
                    }
                }
            }
        }
    } else if(rx==0){
        for(int y=0; y<=ny; y++){
            for(int z=0; z<=nz; z++){
                if((float)((((y-ycenter)*(y-ycenter))/(ry*ry))+(((z-zcenter)*(z-zcenter))/(rz*rz)))<=1){
                    cutVoxel(xcenter, y, z);
                }
            }
        }
    } else if(ry==0){
        for(int x=0; x<=nx; x++){
            for(int z=0; z<=nz; z++){
                if((float)((((x-xcenter)*(x-xcenter))/(rx*rx))+(((z-zcenter)*(z-zcenter))/(rz*rz)))<=1){
                   cutVoxel(x, ycenter, z);
                }
            }
        }
    } else if(rz==0){
        for(int x=0; x<=nx; x++){
            for(int y=0; y<=ny; y++){
                if((float)((((x-xcenter)*(x-xcenter))/(rx*rx))+(((y-ycenter)*(y-ycenter))/(ry*ry)))<=1){
                    cutVoxel(x, y, zcenter);
                }
            }
        }
    }
}
/*  Sinais dos vértices
        0   0   0
        0   0   1
        0   1   0
        0   1   1
        1   0   0
        1   0   1
        1   1   0
        1   1   1
 */
void Sculptor::writeOFF(char *filename){
    int contador=0;
    std::ofstream file;
    file.open(filename);
    if(!file.is_open()){
        exit(0);
    }

    file << "OFF" << std::endl;

    for(int x=0; x<nx; x++){
        for(int y=0; y<ny; y++){
            for(int z=0; z<nz; z++){
                if(v[x][y][z].isOn){
                    contador++;
                }
            }
        }
    }

    file << contador*8 << " " << contador*6 << " " << "0 " << std::endl;
    float largura = 0.5;

    for(int x=0; x<nx; x++){
        for(int y=0; y<ny; y++){
            for(int z=0; z<nz; z++){
                if(v[x][y][z].isOn){
                    file << x - largura << " " << y + largura << " " << z - largura << std::endl;
                    file << x - largura << " " << y - largura << " " << z - largura << std::endl;
                    file << x + largura << " " << y - largura << " " << z - largura << std::endl;
                    file << x + largura << " " << y + largura << " " << z - largura << std::endl;
                    file << x - largura << " " << y + largura << " " << z + largura << std::endl;
                    file << x - largura << " " << y - largura << " " << z + largura << std::endl;
                    file << x + largura << " " << y - largura << " " << z + largura << std::endl;
                    file << x + largura << " " << y + largura << " " << z + largura << std::endl;
                }
            }
        }
    }

    int vertice;
    contador=0;

    for(int x=0; x<nx; x++){
        for(int y=0; y<ny; y++){
            for(int z=0; z<nz; z++){
                if(v[x][y][z].isOn){
                    vertice=8*contador;
                    file << "4 " << vertice << " " << vertice+3 << " " << vertice+2 << " " << vertice+1 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << std::endl;
                    file << "4 " << vertice+4 << " " << vertice+5 << " " << vertice+6 << " " << vertice+7 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << std::endl;
                    file << "4 " << vertice << " " << vertice+1 << " " << vertice+5 << " " << vertice+4 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << std::endl;
                    file << "4 " << vertice << " " << vertice+4 << " " << vertice+7 << " " << vertice+3 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << std::endl;
                    file << "4 " << vertice+3 << " " << vertice+7 << " " << vertice+6 << " " << vertice+2 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << std::endl;
                    file << "4 " << vertice+1 << " " << vertice+2 << " " << vertice+6 << " " << vertice+5 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << std::endl;
                    contador++;
                }
            }
        }
    }
}
