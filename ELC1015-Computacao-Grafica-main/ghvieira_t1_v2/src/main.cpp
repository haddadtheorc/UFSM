#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "gl_canvas2d.h"
#include "Bmp.h"
#include "Widget.h"
#include "Filter.h"

#include <vector>


//TELA
int screenWidth = 1000, screenHeight = 1000;

//MOUSE
int mouseX, mouseY;


std::vector<Bmp*> imageVector;
Bmp *img, *img2, *img3;
Filter *color_filter;
unsigned char *data;

int image_point_mod = 0;
int image_scale_mod = 0;
int image_print_mod = 0;
int current_image = 1;





//COR DO PRÓXIMO PIXEL A SER PINTADO -> o color_filter aplica qualquer transformação necessária no RBG
void show_image_pixel_color(int cont){
    color_filter->filter(data[cont]/255.0, data[cont+1]/255.0, data[cont+2]/255.0);
    CV::color(color_filter->r, color_filter->g, color_filter->b);
}

void show_image_pixel_point(int j, int i, Bmp* image){
    if(image_point_mod==360)
        image_point_mod = 0;
    if(image_point_mod<0){
        image_point_mod = 270;
    }

    switch (image_point_mod){
        case 0:
            CV::point(mouseX - (image->getWidth()/2)/image_scale_mod + j, mouseY - (image->getHeight()/2)/image_scale_mod + i); //p printar a img no centro da tela
        break;

        case 90:
            CV::point(mouseX - (image->getWidth()/2)/image_scale_mod + i, mouseY + (image->getHeight()/2)/image_scale_mod - j); //p printar a img no centro da tela
        break;

        case 180:
            CV::point(mouseX + (image->getWidth()/2)/image_scale_mod - j, mouseY + (image->getHeight()/2)/image_scale_mod - i); //p printar a img no centro da tela
        break;

        case 270:
            CV::point(mouseX + (image->getWidth()/2)/image_scale_mod - i, mouseY - (image->getHeight()/2)/image_scale_mod + j); //p printar a img no centro da tela
        break;
    }
}

void show_image(Bmp* image){

    data = image->getImage();

    //aqui faz os tratamentos dos modificadores para printar a imagem na escala desejada
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

void render(){
    CV::clear(0,0,0);
    show_image(imageVector[current_image]);
}

void keyboard(int key){
    printf("\nPressinou tecla: %d" , key);


    switch(key){

        case 27:
            exit(0);

        //tratamento de girar a imagem +- 90: seta p/ esquerda e seta p/ direita
        case 200:
            image_point_mod -=90;
        break;
        case 202:
            image_point_mod +=90;
        break;
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
        //canal vermelho
        case 114:
            color_filter->r_channel = !color_filter->r_channel;
        break;
        //canal verde
        case 103:
            color_filter->g_channel = !color_filter->g_channel;
        break;
        //canal azul
        case 98:
            color_filter->b_channel = !color_filter->b_channel;
        break;
        //escala de cinza
        case 120:
            color_filter->grayscale = !color_filter->grayscale;
        break;
        //cor invertida
        case 122:
            color_filter->reverse_rgb = !color_filter->reverse_rgb;
        break;
    }
}

void keyboardUp(int key){
    printf("\nLiberou tecla: %d" , key);
}

void mouse(int button, int state, int wheel, int direction, int x, int y){
    mouseX = x;
    mouseY = y;
    printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);
}

int main(void){

    color_filter = new Filter();

    img = new Bmp(".\\ghvieira_t1_v2\\resources\\haddad.bmp");
    img->convertBGRtoRGB();
    img2 = new Bmp(".\\ghvieira_t1_v2\\resources\\normal_1.bmp");
    img2->convertBGRtoRGB();
    img3 = new Bmp(".\\ghvieira_t1_v2\\resources\\img1.bmp");
    img3->convertBGRtoRGB();

    imageVector.push_back(img);
    imageVector.push_back(img2);
    imageVector.push_back(img3);

    CV::init(&screenWidth, &screenHeight, "Trabalho 1 – Visualizador de Imagens e API de widgets");
    CV::run();
}
