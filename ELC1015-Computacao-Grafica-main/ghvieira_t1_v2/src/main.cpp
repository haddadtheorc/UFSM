#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "gl_canvas2d.h"
#include "Widget.h"
#include "Image.h"

//TELA
int screenWidth = 1000, screenHeight = 1000;
//MOUSE
int mouseX, mouseY;
//IMAGENS
Images images;
//WIDGETS
Widget widgets;

void render(){
    CV::clear(0,0,0);
    images.show(mouseX, mouseY);
    widgets.show(images);

    CV::color(1, 1, 1);
    CV::rectFill(screenWidth - screenWidth*0.20, screenHeight - screenHeight*0.20, screenWidth, screenHeight);
    CV::color(0.3, 1, 0.4);
    CV::line(screenWidth - screenWidth*0.20, screenHeight - screenHeight*0.20, screenWidth - screenWidth*0.20, screenHeight);
    CV::line(screenWidth - screenWidth*0.20, screenHeight - screenHeight*0.20, screenWidth, screenHeight - screenHeight*0.20);
}

void keyboard(int key){
    if(images.current_image < 0)
        return;
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
        case 97:
            images.rotateLeft();
        break;
        case 100:
            images.rotateRight();
        break;
        case 119:
            images.scaleUp();
        break;
        case 115:
            images.scaleDown();
        break;
        case 114:
            images.filterRChannel();
        break;
        case 103:
            images.filterGChannel();
        break;
        case 98:
            images.filterBChannel();
        break;
        case 120:
            images.filterGrayScale();
        break;
        case 122:
            images.filterReverseColor();
        break;
    }
}

void keyboardUp(int key){
    //printf("\nLiberou tecla: %d" , key);
}

void mouseWheel(int direction){
    if(images.current_image < 0)
        return;
    if(direction == 1)
        images.scaleUp();
    else{
        images.scaleDown();
        }
}

void mouseClick(){
    if(images.current_image < 0){
        images.collide(mouseX, mouseY);
        return;
    }
    char key = widgets.collide(mouseX, mouseY);
    switch(key){
        case 'A':
            images.rotateLeft();
            return;
        case 'D':
            images.rotateRight();
            return;
        case 'R':
            images.filterRChannel();
            return;
        case 'G':
            images.filterGChannel();
            return;
        case 'B':
            images.filterBChannel();
            return;
        case 'X':
            images.filterGrayScale();
            return;
        case 'Z':
            images.filterReverseColor();
            return;
    }
    images.collide(mouseX, mouseY);
}

void mouse(int button, int state, int wheel, int direction, int x, int y){
    printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);
    mouseX = x;
    mouseY = y;
    if(button == 0){
        if (state==0)
            mouseClick();
    }
    if(!wheel){
        mouseWheel(direction);
    }
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
