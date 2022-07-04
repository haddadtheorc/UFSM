#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "gl_canvas2d.h"
#include "Widget.h"
#include "Image.h"
#include "Histogram.h"

//TELA
int screenWidth = 1000, screenHeight = 1000;
//MOUSE
int mouseX, mouseY;
//IMAGENS
Images images;
//WIDGETS
Widget widgets;
//HISTOGRAMA
Histogram histogram;

void render(){
    CV::clear(0,0,0);
    images.show(mouseX, mouseY);
    widgets.show(images);
    histogram.plot(images, screenWidth, screenHeight);
}

void keyboard(int key){
    if (key == 27)
        exit(0);
    if(images.current_image < 0)
        return;
    switch(key){
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
        case 104:
            histogram.plotMode = !histogram.plotMode;
        break;
    }
}

void keyboardUp(int key){
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
