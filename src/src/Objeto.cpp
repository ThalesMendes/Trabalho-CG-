#include "Objeto.h"
#include <iostream>
#define VAZIO -1
#define NUM_COLUNAS 5

Objeto::Objeto()
{
    sum_dist = 0;

}

Objeto::~Objeto()
{
    //dtor
}


///Funcao que lê o arquivo
///Entrada: char *arquivo, que é o caminho para o arquivo e o arquivo propriamente dito
///Saida: Vetor de vertices e faces preenhido
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

                    if(num_propriedades < 6)
                        sscanf(buff, "%f %f %f", &vertices[cont_vertices].x, &vertices[cont_vertices].y, &vertices[cont_vertices].z);


                    else
                        sscanf(buff, "%f %f %f %f %f %f", &vertices[cont_vertices].x, &vertices[cont_vertices].y,
                               &vertices[cont_vertices].z, &vertices[cont_vertices].nx, &vertices[cont_vertices].ny,
                               &vertices[cont_vertices].nz );

                    //Esse if else gigante é so para pegar o maior e menor vertices de cada coordenada
                    if(cont_vertices == 0){
                        v_min.x = vertices[cont_vertices].x;
                        v_min.y = vertices[cont_vertices].y;
                        v_min.z = vertices[cont_vertices].z;

                        v_max.x = vertices[cont_vertices].x;
                        v_max.y = vertices[cont_vertices].y;
                        v_max.z = vertices[cont_vertices].z;
                    }
                    else{
                        if(v_min.x > vertices[cont_vertices].x)
                            v_min.x = vertices[cont_vertices].x;
                        if(v_min.y > vertices[cont_vertices].y)
                            v_min.y = vertices[cont_vertices].y;
                        if(v_min.z > vertices[cont_vertices].z)
                            v_min.z = vertices[cont_vertices].z;

                        if(v_max.x < vertices[cont_vertices].x)
                            v_max.x = vertices[cont_vertices].x;
                        if(v_max.y < vertices[cont_vertices].y)
                            v_max.y = vertices[cont_vertices].y;
                        if(v_max.z < vertices[cont_vertices].z)
                            v_max.z = vertices[cont_vertices].z;
                    }
                    cont_vertices++;

                }

                //kek
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

///Aqui segue os materiais. Um para cada objeto
void Objeto::SetMaterial(){

   // Material do objeto (neste caso, ruby). Parametros em RGBA
   GLfloat objeto_ambient[]   = { .1745, .01175, .01175, 1.0 };
   GLfloat objeto_difusa[]    = { .61424, .04136, .04136, 1.0 };
   GLfloat objeto_especular[] = { .727811, .626959, .626959, 1.0 };
   GLfloat objeto_brilho[]    = { 90.0f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}

void Objeto::SetMaterial2(){
   GLfloat objeto_ambient[]   = { .0518, .09175, .01175, 1.0 };
   GLfloat objeto_difusa[]    = { .5424, .0836, .04136, 1.0 };
   GLfloat objeto_especular[] = { .17811, .99959, .626959, 1.0 };
   GLfloat objeto_brilho[]    = { 90.0f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}

void Objeto::SetMaterial3(){
   GLfloat objeto_ambient[]   = {0.2f, 0.2f, 0.2f, 1.0f};
   GLfloat objeto_difusa[]    = {0.7f, 0.7f, 0.7f, 1.0f};
   GLfloat objeto_especular[] = {0.1f, 0.1f, 0.1f, 1.0f};
   GLfloat objeto_brilho[]    = { 90.0f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}

void Objeto::SetMaterial4(){
   GLfloat objeto_ambient[]   = {0.1515f, 0.21848f, 0.3887f, 1.0f};
   GLfloat objeto_difusa[]    = {0.387f, 0.898f, 0.7488f, 1.0f};
   GLfloat objeto_especular[] = {0.0018f, 0.0489f, 0.7850f, 1.0f};
   GLfloat objeto_brilho[]    = { 90.0f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}

void Objeto::SetMaterial5(){
   GLfloat objeto_ambient[]   = {1.0f, 0.05f, 1.0f, 1.0f};
   GLfloat objeto_difusa[]    = {1.0f, 0.0f, 0.8787f, 1.0f};
   GLfloat objeto_especular[] = {0.0044f, 0.970f, 0.789f, 1.0f};
   GLfloat objeto_brilho[]    = { 90.0f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}

///Funcao que calcula o vetor normal de cada face
///Entrada: Vertice v1, v2,v3: os 3 vertices que compoe a face e Vertice vn que é onde ficará armezado as coordenadas do vetor
///Saida: Vertice vn preenchido com as coordenadas da normal
void Objeto::CalculaNormal(Vertice v1, Vertice v2, Vertice v3, Vertice *vn)
{
    Vertice v1_temp, v2_temp;
	double len;

   /* Encontra vetor v1 */
   v1_temp.x = v2.x - v1.x;
   v1_temp.y = v2.y - v1.y;
   v1_temp.z = v2.z - v1.z;

   /* Encontra vetor v2 */
   v2_temp.x = v3.x - v1.x;
   v2_temp.y = v3.y - v1.y;
   v2_temp.z = v3.z - v1.z;

   /* Calculo do produto vetorial de v1 e v2 */
   vn->x = (v1_temp.y * v2_temp.z) - (v1_temp.z * v2_temp.y);
   vn->y = (v1_temp.z * v2_temp.x) - (v1_temp.x * v2_temp.z);
   vn->z = (v1_temp.x * v2_temp.y) - (v1_temp.y * v2_temp.x);

   /* normalizacao de n */
   len = sqrt(pow(vn->x,2) + pow(vn->y,2) + pow(vn->z,2));

	vn->x /= len;
	vn->y /= len;
	vn->z /= len;
}

///Funcao que desenha o objeto
///Entrada: bool wireframe, que indica que o objeto deve ser desenhado como superficie ou wireframe e
///         int num_objeto, que indica qual objeto está sendo desenhado (para chamar materiais diferentes)
///Saida: a figura é desenhada na tela
void Objeto::DesenhaObjeto(bool wireframe, int num_objeto){

    switch(num_objeto){
    case 0:
        //SetMaterial();
        break;
    case 1:
        //SetMaterial2();
        break;
    case 2:
        //SetMaterial3();
        break;
    case 3:
        //SetMaterial4();
        break;
    case 4:
        //SetMaterial5();
        break;
    default:
        printf("1");
    }

    int primitiva;
    Vertice vertice_normal;
    wireframe? primitiva = GL_LINE_LOOP : primitiva = GL_POLYGON;

    //Translate para a origen
    glTranslatef(-(v_max.x + v_min.x)/2.0, -(v_max.y + v_min.y)/2.0, -(v_max.z + v_min.z)/2.0);

    //Para todas as faces
    for(int i = 0; i < this->num_faces; i++ ){

        glBegin(primitiva);

        if(faces[i*NUM_COLUNAS + 0] == 4){

            glNormal3f(vertices[faces[i*NUM_COLUNAS+1]].nx, vertices[faces[i*NUM_COLUNAS+1]].ny, vertices[faces[i*NUM_COLUNAS+1]].nz);

            //Para todos os vertices
            for(int j = 1; j < 5; j++){
                //Desenhamos os vertices na tela
                glVertex3f(vertices[faces[i*NUM_COLUNAS+j]].x, vertices[faces[i*NUM_COLUNAS+j]].y,
                           vertices[faces[i*NUM_COLUNAS+j]].z);
                }
        }

        if(faces[i*NUM_COLUNAS + 0] == 3){

            CalculaNormal(vertices[faces[i*NUM_COLUNAS+1]], vertices[faces[i*NUM_COLUNAS+2]], vertices[faces[i*NUM_COLUNAS+3]],
                &vertice_normal);
            glNormal3f(vertice_normal.x, vertice_normal.y, vertice_normal.z);

            for(int j = 1; j < 4; j++){
                glVertex3f(vertices[faces[i*NUM_COLUNAS+j]].x, vertices[faces[i*NUM_COLUNAS+j]].y,
                           vertices[faces[i*NUM_COLUNAS+j]].z);
            }
        }

        glEnd();
    }

}

void Objeto::DesenharBoundingBox(){

    glBegin(GL_LINE_LOOP);
        glVertex3f(v_min.x, v_min.y, 0);
        glVertex3f(v_max.x, v_min.y, 0);
        glVertex3f(v_max.x, v_max.y, 0);
        glVertex3f(v_min.x, v_max.y, 0);
    glEnd();
}

void Objeto::DesenharBoundingBoxAviao(){

    glBegin(GL_LINE_LOOP);
        glVertex3f(v_min.x-4.5, v_min.y-3.8, 0);
        glVertex3f(v_max.x-10.9, v_min.y-3.8, 0);
        glVertex3f(v_max.x-10.9, v_max.y-0.3, 0);
        glVertex3f(v_min.x-4.5, v_max.y-0.3, 0);
    glEnd();

}


