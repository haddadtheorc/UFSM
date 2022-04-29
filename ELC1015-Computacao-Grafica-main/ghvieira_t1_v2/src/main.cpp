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


//TELA
int screenWidth = 750, screenHeight = 750;
//MOUSE
int mouseX, mouseY;
//IMAGENS
Images images;
//WIDGETS
Widget widgets;


void render(){
    CV::clear(0,0,0);
    images.show(mouseX, mouseY);
    widgets.show();
}

void keyboard(int key){
    //printf("\nPressinou tecla: %d" , key);
    switch(key){
        case 27:
            exit(0);
        case 49:
            images.current_image = 0;
        break;
        case 50:
            images.current_image = 1;
        break;
        case 51:
            images.current_image = 2;
        break;
        case 200:
            images.rotateLeft();
        break;
        case 202:
            images.rotateRight();
        break;
        case 201:
            images.scaleUp();
        break;
        case 203:
            images.scaleDown();
        break;
        case 114:
            images.filterRChannel();
            widgets.checkCheckboxes('R');
        break;
        case 103:
            images.filterGChannel();
            widgets.checkCheckboxes('G');
        break;
        case 98:
            images.filterBChannel();
            widgets.checkCheckboxes('B');
        break;
        case 120:
            images.filterGrayScale();
            widgets.checkCheckboxes('X');
        break;
        case 122:
            images.filterReverseColor();
            widgets.checkCheckboxes('Z');
        break;
    }
}

void keyboardUp(int key){
    //printf("\nLiberou tecla: %d" , key);
}

void mouse(int button, int state, int wheel, int direction, int x, int y){
    //printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);
    mouseX = x;
    mouseY = y;
}

void initialize(){
    images.initialize();
    widgets.initialize(screenWidth, screenHeight);
}

int main(void){
    initialize();
    CV::init(&screenWidth, &screenHeight, "Trabalho 1 - Manipulacao de imagens");
    CV::run();
}
