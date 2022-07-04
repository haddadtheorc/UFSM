#ifndef BIKE_H
#define BIKE_H
#include "gl_canvas2d.h"
#include <vector>
using namespace std;
/*
########################################
- Classe para controle da Bicicleta

void initialize() -> preenchendo todas as informações base para criação da bicicleta
void renderWheels() -> renderização das rodas -> auxiliada pela função void renderSpokes() para criação renderização dos aros
void renderFrame() / renderPedals() -> renderização de, respectivamente, quadro e pedais da bicicleta
void rotatePedals() / void rotateWheels() -> rotação de, respectivamente, pedais e rodas(aros) da bicicleta
####################################
*/
class Bike{
public:

    vector<Vector2> spokeCoords;
    vector<Vector2> spokeCoordsTransform;
    vector<Vector2> pedalCoords;
    vector<Vector2> pedalCoordsTransform;
    float frame;
    float wheelRadius;
    int bikeRatio;
    float angulo = 0.0;
    float speed = 0.000;
    Vector2 wheelCenter;
    Vector2 pedalCenter;
    Vector2 seatCenter;
    bool controlPoints = false;

    void initialize(int screenWidth){
        bikeRatio = screenWidth;
        //bkeSize
        frame = bikeRatio*0.255;
        wheelRadius = frame*0.25;
        wheelCenter = Vector2(bikeRatio * 0.250, bikeRatio * 0.050 + wheelRadius);
        pedalCenter = Vector2(wheelCenter.x + frame/2, wheelCenter.y - (bikeRatio * 0.010));
        seatCenter = Vector2(pedalCenter.x, pedalCenter.y + (bikeRatio*0.115));
        //Raios
        spokeCoords.push_back(Vector2(wheelCenter.x - wheelRadius, wheelCenter.y));
        spokeCoords.push_back(Vector2(wheelCenter.x + wheelRadius, wheelCenter.y));
        spokeCoords.push_back(Vector2(wheelCenter.x, wheelCenter.y - wheelRadius));
        spokeCoords.push_back(Vector2(wheelCenter.x, wheelCenter.y + wheelRadius));
        spokeCoords.push_back(Vector2(wheelCenter.x - wheelRadius + frame, wheelCenter.y));
        spokeCoords.push_back(Vector2(wheelCenter.x + wheelRadius + frame, wheelCenter.y));
        spokeCoords.push_back(Vector2(wheelCenter.x + frame, wheelCenter.y - wheelRadius));
        spokeCoords.push_back(Vector2(wheelCenter.x + frame, wheelCenter.y + wheelRadius));
        //Pedais
        pedalCoords.push_back(Vector2(pedalCenter.x, pedalCenter.y - (bikeRatio * 0.040)));
        pedalCoords.push_back(Vector2(pedalCenter.x, pedalCenter.y + (bikeRatio * 0.040)));
    }

    void renderSpokes(){
        CV::color(0, 0, 0);
        //backWheel
        CV::line(spokeCoordsTransform[0], spokeCoordsTransform[1]);
        CV::line(spokeCoordsTransform[2], spokeCoordsTransform[3]);
        //frontWheel
        CV::line(spokeCoordsTransform[4], spokeCoordsTransform[5]);
        CV::line(spokeCoordsTransform[6], spokeCoordsTransform[7]);

        if(controlPoints){
            CV::color(1, 0, 0);
            for(int i = 0; i < spokeCoordsTransform.size(); i++){
                CV::circleFill(spokeCoordsTransform[i].x, spokeCoordsTransform[i].y, 5, 100);
            }
        }
    }

    void rotateWheels(){
        spokeCoordsTransform.clear();
        float x, y;
        //backWheel
        float offsetX = spokeCoords[0].x + ((spokeCoords[1].x - spokeCoords[0].x)/2);
        float offsetY = spokeCoords[2].y + ((spokeCoords[3].y - spokeCoords[2].y)/2);
        for(int i = 0; i < spokeCoords.size() / 2; i++){
            spokeCoords[i].x = spokeCoords[i].x - offsetX;
            spokeCoords[i].y = spokeCoords[i].y - offsetY;
            x = spokeCoords[i].x*cos(angulo) - spokeCoords[i].y*sin(angulo);
            y = spokeCoords[i].x*sin(angulo) + spokeCoords[i].y*cos(angulo);
            x+=offsetX;
            y+=offsetY;
            spokeCoords[i].x = spokeCoords[i].x + offsetX;
            spokeCoords[i].y = spokeCoords[i].y + offsetY;
            spokeCoordsTransform.push_back(Vector2(x, y));
        }
        //frontWheel
        offsetX = spokeCoords[4].x + ((spokeCoords[5].x - spokeCoords[4].x)/2);
        offsetY = spokeCoords[6].y + ((spokeCoords[7].y - spokeCoords[6].y)/2);
        for(int i = spokeCoords.size()/2; i < spokeCoords.size(); i++){
            spokeCoords[i].x = spokeCoords[i].x - offsetX;
            spokeCoords[i].y = spokeCoords[i].y - offsetY;
            x = spokeCoords[i].x*cos(angulo) - spokeCoords[i].y*sin(angulo);
            y = spokeCoords[i].x*sin(angulo) + spokeCoords[i].y*cos(angulo);
            x+=offsetX;
            y+=offsetY;
            spokeCoords[i].x = spokeCoords[i].x + offsetX;
            spokeCoords[i].y = spokeCoords[i].y + offsetY;
            spokeCoordsTransform.push_back(Vector2(x, y));
        }

        angulo -= speed;
    }

    void renderWheels(){
        glLineWidth(5);
        CV::color(0, 0, 0);
        CV::circle(wheelCenter.x, wheelCenter.y, wheelRadius, 100);
        CV::circle(wheelCenter.x + frame, wheelCenter.y, wheelRadius, 100);
        glLineWidth(1);
        renderSpokes();
    }

    void rotatePedals(){
        pedalCoordsTransform.clear();

        float x, y;
        float offsetX = pedalCoords[0].x + ((pedalCoords[1].x - pedalCoords[0].x)/2);
        float offsetY = pedalCoords[0].y + ((pedalCoords[1].y - pedalCoords[0].y)/2);

        for(int i = 0; i < pedalCoords.size(); i++){
            pedalCoords[i].x = pedalCoords[i].x - offsetX;
            pedalCoords[i].y = pedalCoords[i].y - offsetY;

            x = pedalCoords[i].x*cos(angulo) - pedalCoords[i].y*sin(angulo);
            y = pedalCoords[i].x*sin(angulo) + pedalCoords[i].y*cos(angulo);

            x+=offsetX;
            y+=offsetY;

            pedalCoords[i].x = pedalCoords[i].x + offsetX;
            pedalCoords[i].y = pedalCoords[i].y + offsetY;

            pedalCoordsTransform.push_back(Vector2(x, y));
        }

    }

    void renderPedals(){
        //backPedal
        glLineWidth(3);
        CV::color(0, 0, 0);
        CV::line(pedalCoordsTransform[1], pedalCenter);
        CV::color(0.5,0.5,0.5);
        CV::line(pedalCoordsTransform[1].x - bikeRatio*0.010, pedalCoordsTransform[1].y, pedalCoordsTransform[1].x + bikeRatio*0.010, pedalCoordsTransform[1].y);
        glLineWidth(1);
        renderFrame();
        //outerRim
        CV::color(1, 0.5, 0);
        CV::circleFill(pedalCenter.x, pedalCenter.y, bikeRatio*0.020 + bikeRatio*0.003, 100);
        //innerRim
        CV::color(0.5,0.5,0.5);
        CV::circleFill(pedalCenter.x, pedalCenter.y, bikeRatio*0.020, 100);
        //frontPedal
        glLineWidth(3);
        CV::color(0, 0, 0);
        CV::line(pedalCoordsTransform[0], pedalCenter);
        CV::color(0.5,0.5,0.5);
        CV::line(pedalCoordsTransform[0].x - bikeRatio*0.010, pedalCoordsTransform[0].y, pedalCoordsTransform[0].x + bikeRatio*0.010, pedalCoordsTransform[0].y);
        glLineWidth(1);

        if(controlPoints){
            CV::color(1, 0, 0);
            CV::circleFill(pedalCoordsTransform[0].x, pedalCoordsTransform[0].y, 5, 100);
            CV::circleFill(pedalCoordsTransform[1].x, pedalCoordsTransform[1].y, 5, 100);
        }
    }

    void renderFrame(){
        glLineWidth(5);
        CV::color(0.41, 0.37, 0.92);
        CV::line(wheelCenter, pedalCenter);
        CV::line(wheelCenter.x, wheelCenter.y, pedalCenter.x - (bikeRatio * 0.025), pedalCenter.y + (bikeRatio * 0.065));
        CV::line(pedalCenter.x - (bikeRatio * 0.025), pedalCenter.y + (bikeRatio * 0.065), pedalCenter.x + (bikeRatio * 0.075), pedalCenter.y + (bikeRatio * 0.075));
        CV::line(pedalCenter.x + (bikeRatio * 0.075), pedalCenter.y + (bikeRatio * 0.075), pedalCenter.x, pedalCenter.y);
        CV::line(wheelCenter.x + frame, wheelCenter.y, pedalCenter.x + (bikeRatio * 0.075), pedalCenter.y + (bikeRatio * 0.075));
        CV::line(pedalCenter.x - (bikeRatio * 0.045), pedalCenter.y + (bikeRatio * 0.115), pedalCenter.x, pedalCenter.y);
        CV::line(pedalCenter.x + (bikeRatio * 0.075), pedalCenter.y + (bikeRatio * 0.075), pedalCenter.x + (bikeRatio * 0.045), pedalCenter.y + (bikeRatio * 0.125));
        CV::color(0.8,0.8,0.8);
        CV::circleFill(wheelCenter.x, wheelCenter.y, bikeRatio*0.020, 100);
        CV::circleFill(wheelCenter.x + frame, wheelCenter.y, bikeRatio*0.020, 100);
        CV::color(0.5,0.5,0.5);
        CV::line(pedalCenter.x + (bikeRatio * 0.020), pedalCenter.y + (bikeRatio * 0.110), pedalCenter.x + (bikeRatio * 0.060), pedalCenter.y + (bikeRatio * 0.130));
        CV::circleFill(wheelCenter.x, wheelCenter.y, bikeRatio*0.015, 100);
        CV::circleFill(wheelCenter.x + frame, wheelCenter.y, bikeRatio*0.015, 100);
        CV::color(1, 0.5, 0);
        CV::line(seatCenter.x - (bikeRatio * 0.065), seatCenter.y, seatCenter.x - (bikeRatio * 0.040), seatCenter.y);
        glLineWidth(1);
    }

    void render(float _speed, bool _controlPoints){
        speed = _speed;
        controlPoints = _controlPoints;
        rotateWheels();
        renderWheels();
        rotatePedals();
        renderPedals();
    }

    Vector2 getSeatCenter(){
        return seatCenter;
    }

    vector<Vector2> getPedalCoords(){
        if(pedalCoordsTransform.size()!=0)
            return pedalCoordsTransform;
        return pedalCoords;
    }

};
#endif
