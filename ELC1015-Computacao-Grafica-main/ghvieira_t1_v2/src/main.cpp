#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include "gl_canvas2d.h"
#include "Bmp.h"
#include "Widget.h"
#include "Filter.h"



//TELA
int screenWidth, screenHeight = 1000;
//MOUSE
int mouseX, mouseY;

//IMAGENS
std::vector<Bmp*> imageVector;
Bmp *img, *img2, *img3;
Filter *color_filter;
unsigned char *data;
int image_rotation_mod, image_scale_mod, image_print_mod, current_image = 0;



//CRIA E CARREGA IMAGENS
//-> agrupa num vetor de imagens
void loadImages(){
    img = new Bmp(".\\ghvieira_t1_v2\\resources\\haddad.bmp");
    img->convertBGRtoRGB();
    imageVector.push_back(img);

    img2 = new Bmp(".\\ghvieira_t1_v2\\resources\\normal_1.bmp");
    img2->convertBGRtoRGB();
    imageVector.push_back(img2);

    img3 = new Bmp(".\\ghvieira_t1_v2\\resources\\img1.bmp");
    img3->convertBGRtoRGB();
    imageVector.push_back(img3);
}



//COR DO PR�XIMO PIXEL A SER PINTADO
//-> o color_filter aplica qualquer transforma��o necess�ria no RBG
void show_image_pixel_color(int cont){
    color_filter->filter(data[cont]/255.0, data[cont+1]/255.0, data[cont+2]/255.0);
    CV::color(color_filter->r, color_filter->g, color_filter->b);
}



//POSI��O DO PR�XIMO PIXEL A SER PRINTADO
//-> o point_mod e scale_mod aplicam transforma��o de tamanho ou orienta��o
void show_image_pixel_point(int j, int i, Bmp* image){
    switch (image_rotation_mod){
        case 0:
            CV::point(mouseX - (image->getWidth()/2)/image_scale_mod + j, mouseY - (image->getHeight()/2)/image_scale_mod + i);
        break;
        case 90:
            CV::point(mouseX - (image->getWidth()/2)/image_scale_mod + i, mouseY + (image->getHeight()/2)/image_scale_mod - j);
        break;
        case 180:
            CV::point(mouseX + (image->getWidth()/2)/image_scale_mod - j, mouseY + (image->getHeight()/2)/image_scale_mod - i);
        break;
        case 270:
            CV::point(mouseX + (image->getWidth()/2)/image_scale_mod - i, mouseY - (image->getHeight()/2)/image_scale_mod + j);
        break;
    }
}



//IMPRESSAO DE IMAGEM NA TELA
//-> recebe a imagem como argumento e chama suas fun��es auxiliares
void show_image(Bmp* image){

    data = image->getImage();

    if(image_print_mod == 0){
        image_scale_mod = 1;
    }
    else if(image_print_mod == 1){
        image_scale_mod = 2;
    }
    else if(image_print_mod == 2){
        image_scale_mod = 4;
    }

    int cont = 0;
    for(int i = 0; i < image->getHeight()/image_scale_mod; i++){
        for(int j = 0; j < image->getWidth()/image_scale_mod; j++){
            show_image_pixel_color(cont);
            show_image_pixel_point(j, i, image);
            cont += 3 * pow(2,image_print_mod);
        }
        if(image_print_mod!=0){
            cont += image->getWidth() * pow(3,image_print_mod);
        }
    }
}



//FUNCAO PRINCIPAL DE RENDER
void render(){
    CV::clear(0,0,0);
    show_image(imageVector[current_image]);
}



//TECLADO - pressionado
void keyboard(int key){
    printf("\nPressinou tecla: %d" , key);

    switch(key){
        case 27:
            exit(0);

        //ROTACAO DA IMAGEM
        case 200:
            image_rotation_mod -=90;
            if(image_rotation_mod<0)
                image_rotation_mod = 270;
        break;
        case 202:
            image_rotation_mod +=90;
            if(image_rotation_mod==360)
                image_rotation_mod = 0;
        break;

        //ESCALA DA IMAGEM
        case 201:
            if(image_print_mod >= 1){
                image_print_mod --;
            }
        break;
        case 203:
            if(image_print_mod <= 1){
                image_print_mod ++;
            }
        break;

        //TOGGLE DA IMAGEM ATUAL
        case 49:
            current_image = 0;
        break;
        case 50:
            current_image = 1;
        break;
        case 51:
            current_image = 2;
        break;

        //TOGGLE DOS EFEITOS DE COR
        case 114:
            //canal vermelho (R)
            color_filter->r_channel = !color_filter->r_channel;
        break;
        case 103:
            //canal verde (G)
            color_filter->g_channel = !color_filter->g_channel;
        break;
        case 98:
            //canal azul (B)
            color_filter->b_channel = !color_filter->b_channel;
        break;
        case 120:
            //escala de cinza (X)
            color_filter->grayscale = !color_filter->grayscale;
        break;
        case 122:
            //cor invertida (Z)
            color_fil ter->reverse_rgb = !color_filter->reverse_rgb;
        break;
    }
}

//TECLADO - solto
void keyboardUp(int key){
    printf("\nLiberou tecla: %d" , key);
}

//MOUSE
void mouse(int button, int state, int wheel, int direction, int x, int y){
    mouseX = x;
    mouseY = y;
    printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);
}


int main(void){
    printf("lel");
    color_filter = new Filter();
    loadImages();
    CV::init(&screenWidth, &screenHeight, "Trabalho 1 � Manipula��o de imagens");
    CV::run();
}
