#ifndef OBJETO_H
#define OBJETO_H
//#include "glcWavefrontObject.h"
#include <string>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>



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
        void DesenhaObjeto(bool wireframe, int num_objeto);
        void DesenharBoundingBox();
        void SetMaterial();
        void SetMaterial2();
        void SetMaterial3();
        void SetMaterial4();
        void SetMaterial5();
        void CalculaNormal(Vertice v1, Vertice v2, Vertice v3, Vertice *vn);
        Vertice v_max;
        Vertice v_min;
        float media_dist;
        int num_faces;
    private:
        Vertice *vertices;

        int *faces;
        int num_vertices;
        float sum_dist;

};

#endif // OBJETO_H
