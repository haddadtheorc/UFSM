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
#include "Image.h"
#define CHECKBOX_MAX 5

//TELA
int screenWidth = 750, screenHeight = 750;
//MOUSE
int mouseX, mouseY;
//IMAGENS
std::vector<Image*> imgVector;
//WIDGETS
std::vector<Checkbox*> checkboxVector;
//AUXILIARES
int current_image = 0;


// VERIFICANDO ATIVIDADE COM WIGETS
void widget_check(char _id){
    for(int i = 0; i < checkboxVector.size(); i++){
        if(checkboxVector[i]->id == _id)
            checkboxVector[i]->check = !checkboxVector[i]->check;
    }
}

// RENDERIZACAO DAS CHECKBOXES
void show_widget_checkbox(){
    for(int i = 0; i < checkboxVector.size(); i++){
        checkboxVector[i]->Render();
    }

}


// RENDERIZAÇÃO DOS WIDGETS NA TELA
// -> percorre o vetor de widgets renderizando cada um
void show_widgets(){
    show_widget_checkbox();
}

// RENDERIZAÇÃO DAS IMAGENS NA TELA
void show_images(){
    imgVector[current_image]->showImage(mouseX, mouseY, current_image);
}

// FUNCAO PRINCIPAL DE RENDER
void render(){
    CV::clear(0,0,0);
    show_images();
    show_widgets();
}

// TECLADO - pressionado
void keyboard(int key){
    //printf("\nPressinou tecla: %d" , key);

    switch(key){
        case 27:
            exit(0);

        //ROTACAO DA IMAGEM
        case 200:
            imgVector[current_image]->filter->rotation_mod -=90;
            if(imgVector[current_image]->filter->rotation_mod<0)
                imgVector[current_image]->filter->rotation_mod = 270;
        break;
        case 202:
            imgVector[current_image]->filter->rotation_mod +=90;
            if(imgVector[current_image]->filter->rotation_mod==360)
                imgVector[current_image]->filter->rotation_mod = 0;
        break;

        //ESCALA DA IMAGEM
        case 201:
            if(imgVector[current_image]->filter->print_mod >= 1){
                imgVector[current_image]->filter->print_mod --;
            }
        break;
        case 203:
            if(imgVector[current_image]->filter->print_mod <= 1){
                imgVector[current_image]->filter->print_mod ++;
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
            imgVector[current_image]->filter->r_channel = !imgVector[current_image]->filter->r_channel;
            widget_check('R');
        break;
        case 103:
            //canal verde (G)
            imgVector[current_image]->filter->g_channel = !imgVector[current_image]->filter->g_channel;
            widget_check('G');
        break;
        case 98:
            //canal azul (B)
            imgVector[current_image]->filter->b_channel = !imgVector[current_image]->filter->b_channel;
            widget_check('B');
        break;
        case 120:
            //escala de cinza (X)
            imgVector[current_image]->filter->grayscale = !imgVector[current_image]->filter->grayscale;
            widget_check('X');
        break;
        case 122:
            //cor invertida (Z)
            imgVector[current_image]->filter->reverse_rgb = !imgVector[current_image]->filter->reverse_rgb;
            widget_check('Z');
        break;
    }
}

// TECLADO - solto
void keyboardUp(int key){
    //printf("\nLiberou tecla: %d" , key);
}

//MOUSE
void mouse(int button, int state, int wheel, int direction, int x, int y){
    //printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);
    mouseX = x;
    mouseY = y;
}


// CRIA E INICIALIZA IMAGENS E WIDGETS
// -> vetores de imagens e widgets
void initialize(){

    imgVector.push_back(new Image(".\\ghvieira_t1_v2\\resources\\haddad.bmp"));
    imgVector.push_back(new Image(".\\ghvieira_t1_v2\\resources\\normal_1.bmp"));
    imgVector.push_back(new Image(".\\ghvieira_t1_v2\\resources\\img1.bmp"));

    checkboxVector.push_back(new Checkbox(60, screenHeight-50, 15, 15, 1, 0, 0, 'R'));
    checkboxVector.push_back(new Checkbox(90, screenHeight-50, 15, 15, 0, 1, 0, 'G'));
    checkboxVector.push_back(new Checkbox(120, screenHeight-50, 15, 15, 0, 0, 1, 'B'));
    checkboxVector.push_back(new Checkbox(150, screenHeight-50, 15, 15, 1, 1, 1, 'X'));
    checkboxVector.push_back(new Checkbox(180, screenHeight-50, 15, 15, 0.5, 0, 0.5, 'Z'));
}

int main(void){
    initialize();
    CV::init(&screenWidth, &screenHeight, "Trabalho 1 - Manipulacaoo de imagens");
    CV::run();
}
