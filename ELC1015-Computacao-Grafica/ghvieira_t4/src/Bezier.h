#ifndef __BEZIER_H__
#define __BEZIER_H__

#include <vector>
#include "Vector3.h"

#define pi 3.14159265

/*
- Bezier
  - A classe 'Bezier' contém todas as informações pertintentes a construção e desenho da curva Bezier.
  - Os métodos 'drawControlPoints()' e 'drawCurve()' desenham, respectivamente, os pontos de controle da curva e a curva gerada por esses pontos.
  - Os métodos 'addControlPoint()' e 'removeControlPoint()' respectivamente adicionam e removem um ponto de controle.
*/

using namespace std;

class Bezier
{
public:

    vector<Vector3> controlPoints;
    bool binded = false;
    int bindedPoint = 0;

    // Adiciona um ponto de controle na curva
    void addControlPoint(Vector3 point){
        controlPoints.push_back(point);
    }

    // Remove o ponto de controle selecionado ou o último
    void removeControlPoint(){
        if(binded){
            controlPoints.erase(controlPoints.begin() + bindedPoint);
            binded = false;
        }
        else if(controlPoints.size() > 0){
            controlPoints.pop_back();
        }
    }

    // Atualização da posição atual do mouse
    void setMouse (float x, float y){
       if(binded){
            controlPoints[bindedPoint].x = x;
            controlPoints[bindedPoint].y = y;
       }
    }

    // Desativa o track do ponto de controle com o mouse
    void unbind(){
        binded = false;
    }

    // Verifica colisão entre o mouse e o ponto de controle
    bool collide (int x, int y){
        for(int i = 0; i < controlPoints.size(); i++){
            if(x > controlPoints[i].x -5 &&  x < controlPoints[i].x + 5){
                if(y > controlPoints[i].y -5 &&  y < controlPoints[i].y + 5)
                    binded = true;
                    bindedPoint = i;
                    return binded;
            }
        }
        return false;
    }

    // Desenha a curva bezier (função principal que chama as demais)
    void draw(){
        drawControlPoints();
        if(controlPoints.size() > 1)
            drawCurve();
    }

    // Desenha os pontos de controle usados para a curva
    void drawControlPoints(){
        for(int i = 0; i < controlPoints.size(); i++){
            CV::color(0, 0, 0);
            if(binded && i == bindedPoint) CV::color(0, 1, 0);
            CV::circleFill(controlPoints[i].x, controlPoints[i].y, 5, 100);
        }
    }

    // Calcula uma bezier com N pontos de controle
    Vector2 calculateNBezier (vector<Vector3> controlPoints, float t) {
        vector<Vector3> tmp = controlPoints;
        int i = tmp.size() - 1;
        while (i > 0) {
            for (int k = 0; k < i; k++) {
                tmp[k].x = tmp[k].x + t * (tmp[k+1].x - tmp[k].x);
                tmp[k].y = tmp[k].y + t * (tmp[k+1].y - tmp[k].y);

            }
        i--;
        }
        return Vector2(tmp[0].x, tmp[0].y);
    }

    // Desenha a curva com base nos pontos calculados
    void drawCurve(){
        CV::color(0, 0, 0);
        for(float t = 0; t < 1; t+=0.001){
            CV::point(calculateNBezier(controlPoints, t));
        }
    }
};

#endif
