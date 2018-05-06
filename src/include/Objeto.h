#ifndef OBJETO_H
#define OBJETO_H
#include "glcWavefrontObject.h"
#include <string>
#include <GL/glut.h>

typedef struct{
    float x;
    float y;
    float z;
    float nx;
    float ny;
    float nz;
}Vertice;

class Objeto
{
    public:
        Objeto();
        virtual ~Objeto();
        void LerPly(char *arquivo);
        void DesenhaObjeto(bool wireframe);
        void SetMaterial();
        void CalculaNormal(Vertice v1, Vertice v2, Vertice v3, Vertice *vn);
    private:
        Vertice *vertices;
        int *faces;
        int num_vertices;
        int num_faces;
};

#endif // OBJETO_H
