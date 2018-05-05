#ifndef OBJETO_H
#define OBJETO_H
#include "glcWavefrontObject.h"
#include <string>

typedef struct{
    float x;
    float y;
    float z;
    float nx;
    float ny;
    float nz;
}Pontos;

class Objeto
{
    public:
        Objeto();
        virtual ~Objeto();
        void ReadPly(char *arquivo);
    private:
        Pontos *pontos;
};

#endif // OBJETO_H
