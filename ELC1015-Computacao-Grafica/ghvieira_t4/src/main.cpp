#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "gl_canvas2d.h"
#include <math.h>
#include <stdio.h>
#include "Vector3.h"
#include "Bezier.h"
#include "3D.h"

using namespace std;
int screenWidth = 1200, screenHeight = 750;
int ang = 0;
Bezier bezier;
_3D object;

void renderGrid(){
    for(float i = 0; i < screenWidth/3; i+=50){
        CV::line(i, 0, i, screenHeight);
    }
    for(float i = 0; i <= screenHeight; i+=50)
    {
        CV::line(0, i, screenWidth/3, i);
    }
    CV::color(1, 0, 0);
    CV::line(screenWidth/3, 0, screenWidth/3, screenHeight);
}

void render() {
        CV::color(0, 0, 0);
        renderGrid();
        bezier.draw();
        object.draw(bezier.controlPoints, screenHeight);
}

void keyboard(int key){
}

void keyboardUp(int key){
    switch(key){
            break;
        //tecla M -> toggle ORTHO/PERSP
        case 109:
            object.ortho = !object.ortho;
            break;
        //tecla S -> toggle SPRING
        case 115:
            object.spring = !object.spring;
            break;
        //tecla delete -> remove o último/selecionado ponto de controle
        case 127:
            bezier.removeControlPoint();
            break;
        //tecla I -> aumenta o número de voltas na mola
        case 105:
            object.changeRounds(1);
            break;
        //tecla K -> diminui o número de voltas na mola
        case 107:
            object.changeRounds(-1);
            break;
        // Seta p cima -> aumenta  a quntidade de lados
        case 201:
            object.changeMatrixSize(1);
            break;
        // Seta p baixo -> diminui a quntidade de lados
        case 203:
           object.changeMatrixSize(-1);
           break;
         // Seta p esquerda -> diminui o número de pontos da curva
        case 202:
            object.changeBezierIncrement(1);
            break;
        // Seta p direita -> aumenta o número de pontos da curva
        case 200:
            object.changeBezierIncrement(-1);
            break;
    }
}

void checkEditArea(float x, float y){
    if(x >= screenWidth/3 - 5 || x < 5){
        bezier.unbind();
    }
    if(y >= screenHeight - 5 || y < 5){
        bezier.unbind();
    }
}

void mouse(int button, int state, int wheel, int direction, int x, int y){
    checkEditArea(x, y);
    bezier.setMouse(x, y);
    object.setMouse(x, y);

    // Scroll do mouse altera a distância do objeto
    if(wheel == 0){
        object.changeD(direction);
    }
    // Clicou com o mouse, adiciona novo ponto ou move o selecionado;
    if(state == 0){
        if(!bezier.collide(x, y) && x < screenWidth/3)
            bezier.addControlPoint(Vector3(x, y, screenWidth));
    }
    // Soltou o mouse, solta qualquer ponto selecionado
    if(state == 1)
        bezier.unbind();
}

int main(void){
    CV::init(&screenWidth, &screenHeight, "Trabalho 4 - Geracao Objeto 3D com Sweep e Curvas");
    CV::run();
}
