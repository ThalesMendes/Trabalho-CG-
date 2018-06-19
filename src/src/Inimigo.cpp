#include "Inimigo.h"
#define HELICOPTERO 1 //esfera
#define SUBMARINO 2   //retangulo 'deitado'
#define AVIAO 3       //quadrado
#define COMBUSTIVEL 4 //retangulo 'em pé'
#define PONTE 5       //retangulo maior
#define NUM_OBJECTS 5

static Objeto helicoptero;
static Objeto tubarao;
static glcTexture *textureManager = NULL;
static glcWavefrontObject *objectManager = NULL;

Inimigo::Inimigo(){
    this->raio = 10;
    this->ladoA = 72;
    this->ladoB = 15;
}

Inimigo::~Inimigo()
{
    //dtor
}

void Inimigo::leInimigo(){

    helicoptero.LerPly("../data/obj/helicoptero.ply");
    helicoptero.v_max.x += 35;
    helicoptero.v_min.x += 35;
    helicoptero.v_min.y -= 50;
    helicoptero.v_max.y -= 50;
    tubarao.LerPly("../data/obj/tubarao.ply");

    char objectFiles[NUM_OBJECTS][50] =
    {
        "./../data/texturedObj/littleCow.obj",
        "./../data/texturedObj/duck.obj",
        "./../data/texturedObj/Mi_24.obj",
        "./../data/texturedObj/Wood_Boat.obj",
        "./../data/texturedObj/plane.obj"
    };

    char textureFiles[NUM_OBJECTS][50] =
    {
        "./../data/texturedObj/littleCow.png",
        "./../data/texturedObj/duck.png",
        "./../data/texturedObj/L200.png",
        "./../data/texturedObj/TextureBoat.png",
        "./../data/texturedObj/plane.png"

    };


    textureManager = new glcTexture();
    textureManager->SetNumberOfTextures(NUM_OBJECTS);
    textureManager->SetWrappingMode(GL_REPEAT);
    for(int i = 0; i < NUM_OBJECTS; i++)
        textureManager->CreateTexture( textureFiles[i], i);

    // LOAD OBJECTS
    objectManager = new glcWavefrontObject();
    objectManager->SetNumberOfObjects(NUM_OBJECTS);
    for(int i = 0; i < NUM_OBJECTS; i++)
    {
        objectManager->SelectObject(i);
        objectManager->ReadObject(objectFiles[i]);
        objectManager->Unitize();
        objectManager->FacetNormal();
        objectManager->VertexNormals(90.0);
        objectManager->Scale(5);
    }

}

Inimigo* Inimigo::instanciaInimigo() {
    Inimigo *inimigos = new Inimigo[124];


    inimigos[0].tipo = SUBMARINO;
    inimigos[0].x = 480;
    inimigos[0].y = 400;
    inimigos[0].movel = false;
    inimigos[0].pontos = 30;

    inimigos[1].tipo = HELICOPTERO;
    inimigos[1].x = 380;
    inimigos[1].y = 600;
    inimigos[1].movel = false;

    inimigos[2].tipo = COMBUSTIVEL;
    inimigos[2].x = 620;
    inimigos[2].y = 450;
    inimigos[2].movel = false;
    inimigos[2].ladoA = 50;
    inimigos[2].ladoB = 100;
    inimigos[2].pontos = 110;

    inimigos[3].tipo = COMBUSTIVEL;
    inimigos[3].x = 550;
    inimigos[3].y = 650;
    inimigos[3].movel = false;
    inimigos[3].ladoA = 50;
    inimigos[3].ladoB = 100;
    inimigos[3].pontos = 110;

    inimigos[4].tipo = COMBUSTIVEL;
    inimigos[4].x = 660;
    inimigos[4].y = 770;
    inimigos[4].movel = false;
    inimigos[4].ladoA = 50;
    inimigos[4].ladoB = 100;
    inimigos[4].pontos = 110;

    inimigos[5].tipo = COMBUSTIVEL;
    inimigos[5].x = 600;
    inimigos[5].y = 1200;
    inimigos[5].movel = false;
    inimigos[5].ladoA = 50;
    inimigos[5].ladoB = 100;
    inimigos[5].pontos = 110;

    inimigos[6].tipo = HELICOPTERO;
    inimigos[6].x = 350;
    inimigos[6].y = 1350;
    inimigos[6].movel = false;

    inimigos[7].tipo = COMBUSTIVEL;
    inimigos[7].x = 360;
    inimigos[7].y = 1410;
    inimigos[7].movel = false;
    inimigos[7].ladoA = 50;
    inimigos[7].ladoB = 100;
    inimigos[7].pontos = 110;

    inimigos[8].tipo = HELICOPTERO;
    inimigos[8].x = 530;
    inimigos[8].y = 1550;
    inimigos[8].movel = false;

    inimigos[9].tipo = COMBUSTIVEL;
    inimigos[9].x = 640;
    inimigos[9].y = 1650;
    inimigos[9].movel = false;
    inimigos[9].ladoA = 50;
    inimigos[9].ladoB = 100;
    inimigos[9].pontos = 110;

    inimigos[10].tipo = SUBMARINO;
    inimigos[10].x = 640;
    inimigos[10].y = 1900;
    inimigos[10].movel = false;
    inimigos[10].pontos = 30;

    inimigos[11].tipo = HELICOPTERO;
    inimigos[11].x = 400;
    inimigos[11].y = 2000;
    inimigos[11].movel = false;

    inimigos[12].tipo = SUBMARINO;
    inimigos[12].x = 480;
    inimigos[12].y = 2150;
    inimigos[12].movel = false;
    inimigos[12].pontos = 30;

    inimigos[13].tipo = PONTE;
    inimigos[13].x = 350;
    inimigos[13].y = 2250;
    inimigos[13].movel = false;
    inimigos[13].ladoA = 300;
    inimigos[13].ladoB = 100;
    inimigos[13].pontos = 500;

    inimigos[14].tipo = SUBMARINO;
    inimigos[14].x = 610;
    inimigos[14].y = 2520;
    inimigos[14].movel = false;
    inimigos[14].pontos = 30;

    inimigos[15].tipo = SUBMARINO;
    inimigos[15].x = 710;
    inimigos[15].y = 2770;
    inimigos[15].movel = false;
    inimigos[15].pontos = 30;

    inimigos[16].tipo = HELICOPTERO;
    inimigos[16].x = 370;
    inimigos[16].y = 2870;
    inimigos[16].movel = true;
    inimigos[16].maxMovimentoX = 530;

    inimigos[17].tipo = COMBUSTIVEL;
    inimigos[17].x = 700;
    inimigos[17].y = 2950;
    inimigos[17].movel = false;
    inimigos[17].ladoA = 50;
    inimigos[17].ladoB = 100;
    inimigos[17].pontos = 110;

    inimigos[18].tipo = HELICOPTERO;
    inimigos[18].x = 420;
    inimigos[18].y = 3120;
    inimigos[18].movel = true;
    inimigos[18].maxMovimentoX = 530;

    inimigos[19].tipo = COMBUSTIVEL;
    inimigos[19].x = 800;
    inimigos[19].y = 3350;
    inimigos[19].movel = false;
    inimigos[19].ladoA = 50;
    inimigos[19].ladoB = 100;
    inimigos[19].pontos = 110;

    inimigos[20].tipo = HELICOPTERO;
    inimigos[20].x = 320;
    inimigos[20].y = 3580;
    inimigos[20].movel = true;
    inimigos[20].maxMovimentoX = 400;

    inimigos[21].tipo = COMBUSTIVEL;
    inimigos[21].x = 310;
    inimigos[21].y = 3650;
    inimigos[21].movel = false;
    inimigos[21].ladoA = 50;
    inimigos[21].ladoB = 100;
    inimigos[21].pontos = 110;

    inimigos[22].tipo = SUBMARINO;
    inimigos[22].x = 290;
    inimigos[22].y = 3800;
    inimigos[22].movel = false;
    inimigos[22].pontos = 30;

    inimigos[23].tipo = SUBMARINO;
    inimigos[23].x = 670;
    inimigos[23].y = 3900;
    inimigos[23].movel = false;
    inimigos[23].pontos = 30;

    inimigos[24].tipo = HELICOPTERO;
    inimigos[24].x = 120;
    inimigos[24].y = 4300;
    inimigos[24].movel = false;

    inimigos[25].tipo = COMBUSTIVEL;
    inimigos[25].x = 240;
    inimigos[25].y = 4350;
    inimigos[25].movel = false;
    inimigos[25].ladoA = 50;
    inimigos[25].ladoB = 100;
    inimigos[25].pontos = 110;

    inimigos[26].tipo = SUBMARINO;
    inimigos[26].x = 400;
    inimigos[26].y = 4550;
    inimigos[26].movel = true;
    inimigos[26].maxMovimentoX = 100;
    inimigos[26].pontos = 30;

    inimigos[27].tipo = SUBMARINO;
    inimigos[27].x = 700;
    inimigos[27].y = 4650;
    inimigos[27].movel = false;
    inimigos[27].pontos = 30;

    inimigos[28].tipo = COMBUSTIVEL;
    inimigos[28].x = 800;
    inimigos[28].y = 4750;
    inimigos[28].movel = false;
    inimigos[28].ladoA = 50;
    inimigos[28].ladoB = 100;
    inimigos[28].pontos = 110;

    inimigos[29].tipo = HELICOPTERO;
    inimigos[29].x = 180;
    inimigos[29].y = 5200;
    inimigos[29].movel = true;
    inimigos[29].maxMovimentoX = 80;

    inimigos[30].tipo = COMBUSTIVEL;
    inimigos[30].x = 200;
    inimigos[30].y = 5300;
    inimigos[30].movel = false;
    inimigos[30].ladoA = 50;
    inimigos[30].ladoB = 100;
    inimigos[30].pontos = 110;

    inimigos[31].tipo = HELICOPTERO;
    inimigos[31].x = 650;
    inimigos[31].y = 5850;
    inimigos[31].movel = true;
    inimigos[31].maxMovimentoX = 100;

    inimigos[32].tipo = COMBUSTIVEL;
    inimigos[32].x = 820;
    inimigos[32].y = 5900;
    inimigos[32].movel = false;
    inimigos[32].ladoA = 50;
    inimigos[32].ladoB = 100;
    inimigos[32].pontos = 110;

    inimigos[33].tipo = HELICOPTERO;
    inimigos[33].x = 200;
    inimigos[33].y = 6050;
    inimigos[33].movel = true;
    inimigos[33].maxMovimentoX = 100;

    inimigos[34].tipo = SUBMARINO;
    inimigos[34].x = 220;
    inimigos[34].y = 6150;
    inimigos[34].movel = true;
    inimigos[34].maxMovimentoX = 100;
    inimigos[34].pontos = 30;

    inimigos[35].tipo = COMBUSTIVEL;
    inimigos[35].x = 790;
    inimigos[35].y = 6450;
    inimigos[35].movel = false;
    inimigos[35].ladoA = 50;
    inimigos[35].ladoB = 100;
    inimigos[35].pontos = 110;

    inimigos[36].tipo = PONTE;
    inimigos[36].x = 350;
    inimigos[36].y = 7050;
    inimigos[36].movel = false;
    inimigos[36].ladoA = 300;
    inimigos[36].ladoB = 100;
    inimigos[36].pontos = 500;

    inimigos[37].tipo = SUBMARINO;
    inimigos[37].x = 600;
    inimigos[37].y = 7400;
    inimigos[37].movel = false;
    inimigos[37].pontos = 30;

    inimigos[38].tipo = HELICOPTERO;
    inimigos[38].x = 650;
    inimigos[38].y = 7550;
    inimigos[38].movel = false;

    inimigos[39].tipo = HELICOPTERO;
    inimigos[39].x = 650;
    inimigos[39].y = 7650;
    inimigos[39].movel = false;

    inimigos[40].tipo = HELICOPTERO;
    inimigos[40].x = 450;
    inimigos[40].y = 7800;
    inimigos[40].movel = true;
    inimigos[40].maxMovimentoX = 60;

    inimigos[41].tipo = COMBUSTIVEL;
    inimigos[41].x = 500;
    inimigos[41].y = 7900;
    inimigos[41].movel = false;
    inimigos[41].ladoA = 50;
    inimigos[41].ladoB = 100;
    inimigos[41].pontos = 110;

    inimigos[42].tipo = HELICOPTERO;
    inimigos[42].x = 420;
    inimigos[42].y = 8050;
    inimigos[42].movel = true;
    inimigos[42].maxMovimentoX = 50;

    inimigos[43].tipo = HELICOPTERO;
    inimigos[43].x = 450;
    inimigos[43].y = 8150;
    inimigos[43].movel = true;
    inimigos[43].maxMovimentoX = 100;

    inimigos[44].tipo = SUBMARINO;
    inimigos[44].x = 600;
    inimigos[44].y = 8200;
    inimigos[44].movel = true;
    inimigos[44].pontos = 30;
    inimigos[44].maxMovimentoX = 100;

    inimigos[45].tipo = SUBMARINO;
    inimigos[45].x = 500;
    inimigos[45].y = 8300;
    inimigos[45].movel = true;
    inimigos[45].pontos = 30;
    inimigos[45].maxMovimentoX = 100;

    inimigos[46].tipo = AVIAO;
    inimigos[46].x = 750;
    inimigos[46].y = 8400;
    inimigos[46].ladoA = 30;
    inimigos[46].movel = true;
    inimigos[46].pontos = 100;
    inimigos[46].maxMovimentoX = 500;

    inimigos[47].tipo = HELICOPTERO;
    inimigos[47].x = 700;
    inimigos[47].y = 8500;
    inimigos[47].movel = false;

    inimigos[48].tipo = SUBMARINO;
    inimigos[48].x = 650;
    inimigos[48].y = 8600;
    inimigos[48].movel = true;
    inimigos[48].pontos = 30;
    inimigos[48].maxMovimentoX = 100;

    inimigos[49].tipo = AVIAO;
    inimigos[49].x = 750;
    inimigos[49].y = 8700;
    inimigos[49].ladoA = 30;
    inimigos[49].movel = true;
    inimigos[49].pontos = 100;
    inimigos[49].maxMovimentoX = 500;

    inimigos[50].tipo = COMBUSTIVEL;
    inimigos[50].x = 300;
    inimigos[50].y = 8800;
    inimigos[50].movel = false;
    inimigos[50].ladoA = 50;
    inimigos[50].ladoB = 100;
    inimigos[50].pontos = 110;

    inimigos[51].tipo = HELICOPTERO;
    inimigos[51].x = 350;
    inimigos[51].y = 8950;
    inimigos[51].movel = true;
    inimigos[51].maxMovimentoX = 100;

    inimigos[52].tipo = COMBUSTIVEL;
    inimigos[52].x = 450;
    inimigos[52].y = 9000;
    inimigos[52].movel = false;
    inimigos[52].ladoA = 50;
    inimigos[52].ladoB = 100;
    inimigos[52].pontos = 110;

    inimigos[53].tipo = SUBMARINO;
    inimigos[53].x = 500;
    inimigos[53].y = 9150;
    inimigos[53].movel = false;
    inimigos[53].pontos = 30;

    inimigos[54].tipo = PONTE;
    inimigos[54].x = 350;
    inimigos[54].y = 9300;
    inimigos[54].movel = false;
    inimigos[54].ladoA = 300;
    inimigos[54].ladoB = 100;
    inimigos[54].pontos = 500;

    inimigos[55].tipo = COMBUSTIVEL;
    inimigos[55].x = 690;
    inimigos[55].y = 9600;
    inimigos[55].movel = false;
    inimigos[55].ladoA = 50;
    inimigos[55].ladoB = 100;
    inimigos[55].pontos = 110;

    inimigos[56].tipo = COMBUSTIVEL;
    inimigos[56].x = 650;
    inimigos[56].y = 9900;
    inimigos[56].movel = false;
    inimigos[56].ladoA = 50;
    inimigos[56].ladoB = 100;
    inimigos[56].pontos = 110;

    inimigos[57].tipo = SUBMARINO;
    inimigos[57].x = 600;
    inimigos[57].y = 10650;
    inimigos[57].movel = false;
    inimigos[57].pontos = 30;

    inimigos[58].tipo = HELICOPTERO;
    inimigos[58].x = 700;
    inimigos[58].y = 11200;
    inimigos[58].movel = true;
    inimigos[58].maxMovimentoX = 100;

    inimigos[59].tipo = SUBMARINO;
    inimigos[59].x = 350;
    inimigos[59].y = 11350;
    inimigos[59].movel = false;
    inimigos[59].pontos = 30;

    inimigos[60].tipo = AVIAO;
    inimigos[60].x = 600;
    inimigos[60].y = 11700;
    inimigos[60].ladoA = 30;
    inimigos[60].movel = true;
    inimigos[60].pontos = 100;
    inimigos[60].maxMovimentoX = 500;

    inimigos[61].tipo = SUBMARINO;
    inimigos[61].x = 750;
    inimigos[61].y = 12150;
    inimigos[61].movel = false;
    inimigos[61].pontos = 30;

    inimigos[62].tipo = SUBMARINO;
    inimigos[62].x = 100;
    inimigos[62].y = 12400;
    inimigos[62].movel = true;
    inimigos[62].pontos = 30;
    inimigos[62].maxMovimentoX = 40;

    inimigos[63].tipo = COMBUSTIVEL;
    inimigos[63].x = 150;
    inimigos[63].y = 12500;
    inimigos[63].movel = false;
    inimigos[63].ladoA = 50;
    inimigos[63].ladoB = 100;
    inimigos[63].pontos = 110;

    inimigos[64].tipo = AVIAO;
    inimigos[64].x = 100;
    inimigos[64].y = 12700;
    inimigos[64].ladoA = 30;
    inimigos[64].movel = true;
    inimigos[64].pontos = 100;
    inimigos[64].maxMovimentoX = 500;

    inimigos[65].tipo = COMBUSTIVEL;
    inimigos[65].x = 600;
    inimigos[65].y = 12850;
    inimigos[65].movel = false;
    inimigos[65].ladoA = 50;
    inimigos[65].ladoB = 100;
    inimigos[65].pontos = 110;

    inimigos[66].tipo = HELICOPTERO;
    inimigos[66].x = 130;
    inimigos[66].y = 13250;
    inimigos[66].movel = true;
    inimigos[66].maxMovimentoX = 50;

    inimigos[67].tipo = COMBUSTIVEL;
    inimigos[67].x = 200;
    inimigos[67].y = 13400;
    inimigos[67].movel = false;
    inimigos[67].ladoA = 50;
    inimigos[67].ladoB = 100;
    inimigos[67].pontos = 110;

    inimigos[68].tipo = AVIAO;
    inimigos[68].x = 180;
    inimigos[68].y = 13700;
    inimigos[68].ladoA = 30;
    inimigos[68].movel = true;
    inimigos[68].pontos = 100;
    inimigos[68].maxMovimentoX = 500;

    inimigos[69].tipo = COMBUSTIVEL;
    inimigos[69].x = 720;
    inimigos[69].y = 13900;
    inimigos[69].movel = false;
    inimigos[69].ladoA = 50;
    inimigos[69].ladoB = 100;
    inimigos[69].pontos = 110;

    inimigos[70].tipo = COMBUSTIVEL;
    inimigos[70].x = 150;
    inimigos[70].y = 14050;
    inimigos[70].movel = false;
    inimigos[70].ladoA = 50;
    inimigos[70].ladoB = 100;
    inimigos[70].pontos = 110;

    inimigos[71].tipo = COMBUSTIVEL;
    inimigos[71].x = 220;
    inimigos[71].y = 14150;
    inimigos[71].movel = false;
    inimigos[71].ladoA = 50;
    inimigos[71].ladoB = 100;
    inimigos[71].pontos = 110;

    inimigos[72].tipo = AVIAO;
    inimigos[72].x = 700;
    inimigos[72].y = 14350;
    inimigos[72].ladoA = 30;
    inimigos[72].movel = true;
    inimigos[72].pontos = 100;
    inimigos[72].maxMovimentoX = 500;

    inimigos[73].tipo = SUBMARINO;
    inimigos[73].x = 800;
    inimigos[73].y = 14480;
    inimigos[73].movel = true;
    inimigos[73].pontos = 30;
    inimigos[73].maxMovimentoX = 30;

    inimigos[74].tipo = COMBUSTIVEL;
    inimigos[74].x = 750;
    inimigos[74].y = 14600;
    inimigos[74].movel = false;
    inimigos[74].ladoA = 50;
    inimigos[74].ladoB = 100;
    inimigos[74].pontos = 110;

    inimigos[75].tipo = SUBMARINO;
    inimigos[75].x = 420;
    inimigos[75].y = 15130;
    inimigos[75].movel = true;
    inimigos[75].pontos = 30;
    inimigos[75].maxMovimentoX = 30;

    inimigos[76].tipo = PONTE;
    inimigos[76].x = 350;
    inimigos[76].y = 15350;
    inimigos[76].movel = false;
    inimigos[76].ladoA = 300;
    inimigos[76].ladoB = 100;
    inimigos[76].pontos = 500;

    inimigos[77].tipo = SUBMARINO;
    inimigos[77].x = 380;
    inimigos[77].y = 15750;
    inimigos[77].movel = false;
    inimigos[77].pontos = 30;

    inimigos[78].tipo = HELICOPTERO;
    inimigos[78].x = 450;
    inimigos[78].y = 15850;
    inimigos[78].movel = true;
    inimigos[78].maxMovimentoX = 50;

    inimigos[79].tipo = HELICOPTERO;
    inimigos[79].x = 750;
    inimigos[79].y = 15950;
    inimigos[79].movel = true;
    inimigos[79].maxMovimentoX = 15;

    inimigos[80].tipo = HELICOPTERO;
    inimigos[80].x = 700;
    inimigos[80].y = 16000;
    inimigos[80].movel = true;
    inimigos[80].maxMovimentoX = 25;

    inimigos[81].tipo = AVIAO;
    inimigos[81].x = 300;
    inimigos[81].y = 16100;
    inimigos[81].ladoA = 30;
    inimigos[81].movel = true;
    inimigos[81].pontos = 100;
    inimigos[81].maxMovimentoX = 500;

    inimigos[82].tipo = HELICOPTERO;
    inimigos[82].x = 300;
    inimigos[82].y = 16200;
    inimigos[82].movel = true;
    inimigos[82].maxMovimentoX = 50;

    inimigos[83].tipo = COMBUSTIVEL;
    inimigos[83].x = 310;
    inimigos[83].y = 16300;
    inimigos[83].movel = false;
    inimigos[83].ladoA = 50;
    inimigos[83].ladoB = 100;
    inimigos[83].pontos = 110;

    inimigos[84].tipo = HELICOPTERO;
    inimigos[84].x = 400;
    inimigos[84].y = 16450;
    inimigos[84].movel = true;
    inimigos[84].maxMovimentoX = 50;

    inimigos[85].tipo = HELICOPTERO;
    inimigos[85].x = 700;
    inimigos[85].y = 16550;
    inimigos[85].movel = true;
    inimigos[85].maxMovimentoX = 20;

    inimigos[86].tipo = AVIAO;
    inimigos[86].x = 600;
    inimigos[86].y = 16650;
    inimigos[86].ladoA = 30;
    inimigos[86].movel = true;
    inimigos[86].pontos = 100;
    inimigos[86].maxMovimentoX = 300;

    inimigos[87].tipo = COMBUSTIVEL;
    inimigos[87].x = 500;
    inimigos[87].y = 16900;
    inimigos[87].movel = false;
    inimigos[87].ladoA = 50;
    inimigos[87].ladoB = 100;
    inimigos[87].pontos = 110;

    inimigos[88].tipo = HELICOPTERO;
    inimigos[88].x = 700;
    inimigos[88].y = 17100;
    inimigos[88].movel = true;
    inimigos[88].maxMovimentoX = 20;

    inimigos[89].tipo = HELICOPTERO;
    inimigos[89].x = 680;
    inimigos[89].y = 17200;
    inimigos[89].movel = true;
    inimigos[89].maxMovimentoX = 30;

    inimigos[90].tipo = AVIAO;
    inimigos[90].x = 400;
    inimigos[90].y = 17350;
    inimigos[90].ladoA = 30;
    inimigos[90].movel = true;
    inimigos[90].pontos = 100;
    inimigos[90].maxMovimentoX = 300;

    inimigos[91].tipo = COMBUSTIVEL;
    inimigos[91].x = 700;
    inimigos[91].y = 17450;
    inimigos[91].movel = false;
    inimigos[91].ladoA = 50;
    inimigos[91].ladoB = 100;
    inimigos[91].pontos = 110;

    inimigos[92].tipo = HELICOPTERO;
    inimigos[92].x = 700;
    inimigos[92].y = 17570;
    inimigos[92].movel = false;

    inimigos[93].tipo = SUBMARINO;
    inimigos[93].x = 700;
    inimigos[93].y = 17650;
    inimigos[93].movel = false;
    inimigos[93].pontos = 30;

    inimigos[94].tipo = HELICOPTERO;
    inimigos[94].x = 650;
    inimigos[94].y = 17750;
    inimigos[94].movel = false;

    inimigos[95].tipo = HELICOPTERO;
    inimigos[95].x = 600;
    inimigos[95].y = 17900;
    inimigos[95].movel = true;
    inimigos[95].maxMovimentoX = 30;

    inimigos[96].tipo = HELICOPTERO;
    inimigos[96].x = 350;
    inimigos[96].y = 18000;
    inimigos[96].movel = true;
    inimigos[96].maxMovimentoX = 30;

    inimigos[97].tipo = HELICOPTERO;
    inimigos[97].x = 650;
    inimigos[97].y = 18100;
    inimigos[97].movel = true;
    inimigos[97].maxMovimentoX = 30;

    inimigos[98].tipo = HELICOPTERO;
    inimigos[98].x = 500;
    inimigos[98].y = 18200;
    inimigos[98].movel = false;

    inimigos[99].tipo = SUBMARINO;
    inimigos[99].x = 480;
    inimigos[99].y = 18300;
    inimigos[99].movel = false;
    inimigos[99].pontos = 30;

    inimigos[100].tipo = PONTE;
    inimigos[100].x = 350;
    inimigos[100].y = 18450;
    inimigos[100].movel = false;
    inimigos[100].ladoA = 300;
    inimigos[100].ladoB = 100;
    inimigos[100].pontos = 500;

    inimigos[101].tipo = HELICOPTERO;
    inimigos[101].x = 170;
    inimigos[101].y = 18850;
    inimigos[101].movel = true;
    inimigos[101].maxMovimentoX = 50;

    inimigos[102].tipo = HELICOPTERO;
    inimigos[102].x = 170;
    inimigos[102].y = 18900;
    inimigos[102].movel = true;
    inimigos[102].maxMovimentoX = 80;

    inimigos[103].tipo = COMBUSTIVEL;
    inimigos[103].x = 850;
    inimigos[103].y = 19270;
    inimigos[103].movel = false;
    inimigos[103].ladoA = 50;
    inimigos[103].ladoB = 100;
    inimigos[103].pontos = 110;

    inimigos[104].tipo = HELICOPTERO;
    inimigos[104].x = 100;
    inimigos[104].y = 19350;
    inimigos[104].movel = false;

    inimigos[105].tipo = COMBUSTIVEL;
    inimigos[105].x = 130;
    inimigos[105].y = 19450;
    inimigos[105].movel = false;
    inimigos[105].ladoA = 50;
    inimigos[105].ladoB = 100;
    inimigos[105].pontos = 110;

    inimigos[106].tipo = AVIAO;
    inimigos[106].x = 400;
    inimigos[106].y = 19600;
    inimigos[106].ladoA = 30;
    inimigos[106].movel = true;
    inimigos[106].pontos = 100;
    inimigos[106].maxMovimentoX = 300;

    inimigos[107].tipo = HELICOPTERO;
    inimigos[107].x = 100;
    inimigos[107].y = 19800;
    inimigos[107].movel = false;

    inimigos[108].tipo = HELICOPTERO;
    inimigos[108].x = 900;
    inimigos[108].y = 20000;
    inimigos[108].movel = false;

    inimigos[109].tipo = HELICOPTERO;
    inimigos[109].x = 900;
    inimigos[109].y = 20500;
    inimigos[109].movel = true;
    inimigos[109].maxMovimentoX = 5;

    inimigos[110].tipo = COMBUSTIVEL;
    inimigos[110].x = 850;
    inimigos[110].y = 21100;
    inimigos[110].movel = false;
    inimigos[110].ladoA = 50;
    inimigos[110].ladoB = 100;
    inimigos[110].pontos = 110;

    inimigos[111].tipo = HELICOPTERO;
    inimigos[111].x = 220;
    inimigos[111].y = 21350;
    inimigos[111].movel = false;

    inimigos[112].tipo = COMBUSTIVEL;
    inimigos[112].x = 230;
    inimigos[112].y = 21500;
    inimigos[112].movel = false;
    inimigos[112].ladoA = 50;
    inimigos[112].ladoB = 100;
    inimigos[112].pontos = 110;

    inimigos[113].tipo = AVIAO;
    inimigos[113].x = 250;
    inimigos[113].y = 21650;
    inimigos[113].ladoA = 30;
    inimigos[113].movel = true;
    inimigos[113].pontos = 100;
    inimigos[113].maxMovimentoX = 500;

    inimigos[114].tipo = SUBMARINO;
    inimigos[114].x = 650;
    inimigos[114].y = 21900;
    inimigos[114].movel = false;
    inimigos[114].pontos = 30;

    inimigos[115].tipo = SUBMARINO;
    inimigos[115].x = 350;
    inimigos[115].y = 22000;
    inimigos[115].movel = true;
    inimigos[115].pontos = 30;
    inimigos[115].maxMovimentoX = 60;

    inimigos[116].tipo = SUBMARINO;
    inimigos[116].x = 300;
    inimigos[116].y = 22450;
    inimigos[116].movel = true;
    inimigos[116].pontos = 30;
    inimigos[116].maxMovimentoX = 60;

    inimigos[117].tipo = SUBMARINO;
    inimigos[117].x = 800;
    inimigos[117].y = 22700;
    inimigos[117].movel = false;
    inimigos[117].pontos = 30;

    inimigos[118].tipo = COMBUSTIVEL;
    inimigos[118].x = 80;
    inimigos[118].y = 22750;
    inimigos[118].movel = false;
    inimigos[118].ladoA = 50;
    inimigos[118].ladoB = 100;
    inimigos[118].pontos = 110;

    inimigos[119].tipo = COMBUSTIVEL;
    inimigos[119].x = 80;
    inimigos[119].y = 22950;
    inimigos[119].movel = false;
    inimigos[119].ladoA = 50;
    inimigos[119].ladoB = 100;
    inimigos[119].pontos = 110;

    inimigos[120].tipo = COMBUSTIVEL;
    inimigos[120].x = 80;
    inimigos[120].y = 23100;
    inimigos[120].movel = false;
    inimigos[120].ladoA = 50;
    inimigos[120].ladoB = 100;
    inimigos[120].pontos = 110;

    inimigos[121].tipo = HELICOPTERO;
    inimigos[121].x = 80;
    inimigos[121].y = 23500;
    inimigos[121].movel = true;
    inimigos[121].maxMovimentoX = 5;

    inimigos[122].tipo = HELICOPTERO;
    inimigos[122].x = 900;
    inimigos[122].y = 23650;
    inimigos[122].movel = false;

    inimigos[123].tipo = PONTE;
    inimigos[123].x = 350;
    inimigos[123].y = 23950;
    inimigos[123].movel = false;
    inimigos[123].ladoA = 300;
    inimigos[123].ladoB = 100;
    inimigos[123].pontos = 500;

    return inimigos;
}

void Inimigo::SetMaterial(){
   GLfloat objeto_ambient[]   = {0.0, 0.0, 0.0, 1.0f};
   GLfloat objeto_difusa[]    = {0.0, 0.0, 0.0, 1.0f};
   GLfloat objeto_especular[] = {0.0,	0.0,0.0, 1.0f};
   GLfloat objeto_brilho[]    = { 90.0f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}

void Inimigo::SetMaterial2(){
   GLfloat objeto_ambient[]   = {0.2125,	0.1275,	0.054, 1.0f};
   GLfloat objeto_difusa[]    = {0.714,	0.4284,	0.18144, 1.0f};
   GLfloat objeto_especular[] = {0.393548,	0.271906,	0.166721, 1.0f};
   GLfloat objeto_brilho[]    = { 90.0f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}



void Inimigo::desenhaInimigo(int arrumaRotate2D){
    if(this->vivo){
        if(this->tipo == HELICOPTERO){
             glPushMatrix();
                glTranslated(this->movimento, 0, 0);
                glTranslated(this->x, this->y, 0);
                helicoptero.DesenharBoundingBox();
                glRotatef(arrumaRotate2D, 0, 1, 0);
                glRotatef(90, 1, 0, 0);
                glScalef(14.0, 14.0, 14.0);
                textureManager->Bind(2);
                objectManager->SetColor(1.0, 0.0, 0.0);
                objectManager->SelectObject(2);
                objectManager->SetShadingMode(SMOOTH_SHADING); // Alternative: FLAT_SHADING
                objectManager->SetRenderMode(USE_TEXTURE);
                objectManager->Draw();

                this->maxX = helicoptero.v_max.x;
                this->minX = helicoptero.v_min.x;
                this->minY = helicoptero.v_min.y;
                this->maxY = helicoptero.v_max.y;
                //glutSolidSphere(this->raio, 100, 100);
            glPopMatrix();
        }

        if(this->tipo == SUBMARINO){
            glPushMatrix();
                //glColor3f(1, 1 ,1);

                glTranslated(this->movimento, 0, 0);
                glTranslated(x, y, 0);
                tubarao.DesenharBoundingBox();
                glRotatef(arrumaRotate2D, 0, 1, 0);
                glRotatef(90, 1, 0, 0);
                glRotatef(90, 0, 1, 0);
                glScalef(14.0, 14.0, 14.0);
                textureManager->Bind(3);
                objectManager->SetColor(1.0, 0.0, 0.0);
                objectManager->SelectObject(3);
                objectManager->SetShadingMode(SMOOTH_SHADING); // Alternative: FLAT_SHADING
                objectManager->SetRenderMode(USE_TEXTURE);
                objectManager->Draw();

                this->maxX = tubarao.v_max.x;
                this->minX = tubarao.v_min.x;
                this->minY = tubarao.v_min.y;
                this->maxY = tubarao.v_max.y;

            glPopMatrix();

        }

        if(this->tipo == COMBUSTIVEL){
            glPushMatrix();
                //SetMaterial();
                    glBegin(GL_POLYGON);
                    glVertex3d(this->x, this->y,0);
                    glVertex3d(this->x + this->ladoA, this->y,0);
                    glVertex3d(this->x + this->ladoA, this->y + this->ladoB,0);
                    glVertex3d(this->x, this->y + this->ladoB,0);
                glEnd();

                glBegin(GL_POLYGON);
                    glVertex3d(this->x, this->y,30);
                    glVertex3d(this->x + this->ladoA, this->y,30);
                    glVertex3d(this->x + this->ladoA, this->y + this->ladoB,30);
                    glVertex3d(this->x, this->y + this->ladoB,30);
                glEnd();

                glBegin(GL_POLYGON);
                    glVertex3d(this->x, this->y,0);
                    glVertex3d(this->x + this->ladoA, this->y,0);
                    glVertex3d(this->x + this->ladoA, this->y,30);
                    glVertex3d(this->x, this->y,30);
                glEnd();


                glBegin(GL_POLYGON);
                    glVertex3d(this->x, this->y,0);
                    glVertex3d(this->x, this->y,30);
                    glVertex3d(this->x, this->y + this->ladoB,30);
                    glVertex3d(this->x, this->y + this->ladoB,0);
                glEnd();


                glBegin(GL_POLYGON);
                    glVertex3d(this->x+this->ladoA, this->y,30);
                    glVertex3d(this->x+this->ladoA, this->y,0);
                    glVertex3d(this->x+this->ladoA, this->y + this->ladoB,0);
                    glVertex3d(this->x+this->ladoA, this->y + this->ladoB,30);
                glEnd();

            glPopMatrix();
        }

          if(this->tipo == PONTE){
            glPushMatrix();
                //SetMaterial2();
                glBegin(GL_POLYGON);
                    glVertex3d(this->x, this->y,0);
                    glVertex3d(this->x + this->ladoA, this->y,0);
                    glVertex3d(this->x + this->ladoA, this->y + this->ladoB,0);
                    glVertex3d(this->x, this->y + this->ladoB,0);
                glEnd();

                glBegin(GL_POLYGON);
                    glVertex3d(this->x, this->y,90);
                    glVertex3d(this->x + this->ladoA, this->y,90);
                    glVertex3d(this->x + this->ladoA, this->y + this->ladoB,90);
                    glVertex3d(this->x, this->y + this->ladoB,90);
                glEnd();


                glBegin(GL_POLYGON);
                    glVertex3d(this->x, this->y,0);
                    glVertex3d(this->x + this->ladoA, this->y,0);
                    glVertex3d(this->x + this->ladoA, this->y,90);
                    glVertex3d(this->x, this->y,90);
                glEnd();
            glPopMatrix();
        }

//        if(this->tipo == AVIAO){
//            glPushMatrix();
//                //glColor3f(1, 1 ,1);
//                glTranslated(this->movimento, 0, 0);
//                glTranslated(this->x, this->y, 0);
//                objeto.DesenhaObjeto(false, 1);
////                glBegin(GL_POLYGON);
////                    glVertex2d(this->x, this->y);
////                    glVertex2d(this->x + this->ladoA, this->y);
////                    glVertex2d(this->x + this->ladoA, this->y + this->ladoA);
////                    glVertex2d(this->x, this->y + this->ladoA);
////                glEnd();
//            glPopMatrix();
        //}
    }
}
