#include "Objeto.h"
#include <iostream>

Objeto::Objeto()
{

}

Objeto::~Objeto()
{
    //dtor
}



void Objeto::ReadPly(char *arquivo){

    //abrindo o arquivo
    FILE *file = fopen(arquivo, "r");
    char buff[255];

    if(!file){
        printf("ERRO NA LEITURA DO ARQUIVO");
    }

    //contador para saber se estou na terceira palavra, que é o numero que eu quero
    int cont = 0;

    //flag para saber se estou vendo o numero de vertices (0) ou de faces (1)
    int vertice_face = 0;

    //o numero total de vertices e faces
    int num_vertices;
    int num_faces;
    int cont_vertices = 0;
    int cont_faces = 0;

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

        this->pontos = new Pontos[num_vertices];

        //se estou na linha do "end_header", começo a ler as faces e vertices
        if(buff[0] == 'e' && buff[1] == 'n'){

            float *vetor_vertices = new float[num_vertices*num_propriedades];

            int pos_linha = 0;

            while(fgets(buff, sizeof(buff), file)){

                if(cont_vertices < num_vertices){

                    if(num_propriedades > 6)
                        sscanf(buff, "%f %f %f", &pontos[cont_vertices].x, &pontos[cont_vertices].y, &pontos[cont_vertices].z);
                    else
                        sscanf(buff, "%f %f %f %f %f %f", &pontos[cont_vertices].x, &pontos[cont_vertices].y,
                               &pontos[cont_vertices].z, &pontos[cont_vertices].nx, &pontos[cont_vertices].ny,
                               &pontos[cont_vertices].nz );

                    cont_vertices++;

                }

                if(cont_vertices >= num_vertices && cont_faces < num_faces){

                }
            }

            fclose(file);
            return;

        }


    }

}
