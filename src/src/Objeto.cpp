#include "Objeto.h"
#include <iostream>
#define VAZIO -1
#define NUM_COLUNAS 5
Objeto::Objeto()
{

}

Objeto::~Objeto()
{
    //dtor
}



void Objeto::LerPly(char *arquivo){

    //abrindo o arquivo
    FILE *file = fopen(arquivo, "r");
    char buff[255];

    if(!file){
        printf("ERRO NA LEITURA DO ARQUIVO");
        return;
    }

    //contador para saber se estou na terceira palavra, que é o numero que eu quero
    int cont = 0;

    //flag para saber se estou vendo o numero de vertices (0) ou de faces (1)
    int vertice_face = 0;

    //o numero total de vertices e faces

    int cont_vertices = 0;
    int cont_faces = -1;

    //Indica em qual palavra estou na linha
    int indice_linha = 0;

    //numero de vertices por linha. Começa com -1 por causa da "property list uchar uint vertex_indices",
    //que tem em todos os arquivos
    int num_propriedades = -1;

    //loop por cada linha do arquivo
    while(fgets(buff, sizeof(buff), file)){

        //se é a palavra 'element', devo pegar o numero de vertices e faces
        if(buff[0] == 'e' && buff[1] == 'l'){
            cont = 0;
            //divido a linha em cada palavra (token)
            char *token = strtok(buff, " ");

            while(token != NULL){
                //se estou no terceiro token, quer dizer que cheguei no numero
                if(cont == 2){
                    switch(vertice_face){
                        case 0:
                            num_vertices = atoi(token);
                            vertice_face = 1;
                            break;
                        case 1:
                            num_faces = atoi(token);
                            break;
                    }
                }

                token = strtok(NULL, " ");
                cont++;
            }
        }

        //numero de propriedades que vai estar no vetor de vertices
        if(buff[0] == 'p' && buff[1] == 'r'){
            num_propriedades++;
        }

        this->vertices = new Vertice[this->num_vertices];
        this->faces = new int[this->num_faces*5];

        //se estou na linha do "end_header", começo a ler as faces e vertices
        if(buff[0] == 'e' && buff[1] == 'n'){

            //aqui começa a "releitura" do arquivo
            while(fgets(buff, sizeof(buff), file)){

                //se ainda nao li todos os vertices:
                if(cont_vertices < this->num_vertices){

                    if(num_propriedades > 6)
                        sscanf(buff, "%f %f %f", &vertices[cont_vertices].x, &vertices[cont_vertices].y, &vertices[cont_vertices].z);
                    else
                        sscanf(buff, "%f %f %f %f %f %f", &vertices[cont_vertices].x, &vertices[cont_vertices].y,
                               &vertices[cont_vertices].z, &vertices[cont_vertices].nx, &vertices[cont_vertices].ny,
                               &vertices[cont_vertices].nz );

                    cont_vertices++;

                }


                //se li todos os vertices mas ainda nao li todas as facez:
                if(cont_vertices >= num_vertices && cont_faces < num_faces){

                    int num_vertices_por_face;
                    int face1, face2, face3;
                    sscanf(buff, "%d", &num_vertices_por_face);

                    if(num_vertices_por_face == 4){
                        sscanf(buff, "%d %d %d %d %d", &faces[cont_faces*NUM_COLUNAS + 0], &faces[cont_faces*NUM_COLUNAS + 1],
                               &faces[cont_faces*NUM_COLUNAS + 2], &faces[cont_faces*NUM_COLUNAS + 3], &faces[cont_faces*NUM_COLUNAS + 4]);
                    }

                    if(num_vertices_por_face == 3){
                        sscanf(buff, "%d %d %d %d", &faces[cont_faces*NUM_COLUNAS + 0], &faces[cont_faces*NUM_COLUNAS + 1],
                               &faces[cont_faces*NUM_COLUNAS + 2], &faces[cont_faces*NUM_COLUNAS + 3]);

                        faces[cont_faces*NUM_COLUNAS + 4] = VAZIO;
                    }

                cont_faces++;

                }
            }

            fclose(file);
            return;

        }

    }
}

void Objeto::DesenhaObjeto(){

        for(int i = 0; i < this->num_faces; i++ ){
            glBegin(GL_POLYGON);
            if(faces[i*NUM_COLUNAS + 0] == 4){
                for(int j = 1; j < 5; j++){
                    glVertex3f(vertices[faces[i*NUM_COLUNAS+j]].x, vertices[faces[i*NUM_COLUNAS+j]].y,
                               vertices[faces[i*NUM_COLUNAS+j]].z);
                    }
            }

            if(faces[i*NUM_COLUNAS + 0] == 3){
                for(int j = 1; j < 4; j++){
                    glVertex3f(vertices[faces[i*NUM_COLUNAS+j]].x, vertices[faces[i*NUM_COLUNAS+j]].y,
                               vertices[faces[i*NUM_COLUNAS+j]].z);
                }
            }
            glEnd();
        }

}

