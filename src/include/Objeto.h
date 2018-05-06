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
        Vertice v_max;
        Vertice v_min;
        float media_dist;
    private:
        Vertice *vertices;

        int *faces;
        int num_vertices;
        int num_faces;
        float sum_dist;

};

#endif // OBJETO_H
