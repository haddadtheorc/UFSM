#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "gl_canvas2d.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;
/*
########################################
- Classe para controle do Fundo

void initialize() -> preenchendo todas as informações base para criação do fundo
void renderClouds() -> renderização das nuvens -> auxiliada pela função void addCloud() para criação das nuvens
void renderMountains() -> renderização das montanhas -> auxiliada pela função void addMountain() para criação das montanhas
void renderSky() -> renderização do céu
void renderBack() -> renderização da planície até as montanhas
void renderFloor() -> renderização da estrada
####################################
*/
class Background{
public:

    int screenWidth, screenHeight;
    bool controlPoints;
    float speed;
    float mountainHeight = 200;
    float mountainWidth = 400;
    Vector2 seatCenter;
    vector<Vector2> mountains;
    vector<Vector2> clouds;

    void initialize(int _screenHeight, int _screenWidth, Vector2 _seatCenter){
        srand (time(NULL));
        seatCenter = _seatCenter;
        screenHeight = _screenHeight;
        screenWidth = _screenWidth;
        addMountain();
        addCloud();
    }

    void renderClouds(){
        CV::color(1, 1, 1);
        for(int i = 0; i < clouds.size(); i++){
            clouds[i].x -= speed*20;
            CV::circleFill(clouds[i].x, clouds[i].y, screenHeight*0.045, 100);
        }
        if(clouds.back().x <= screenWidth){
            addCloud();
        }
        if(controlPoints){
            for(int i = 0; i < clouds.size(); i++){
                CV::color(1, 0, 0);
                CV::circleFill(clouds[i], screenWidth*0.005, 100);
            }
        }
    }

    void addCloud(){
        float cloudHeight = rand() %(int(screenHeight*0.275)) + screenHeight*0.6;
        clouds.push_back(Vector2(screenWidth + screenWidth*0.225, cloudHeight));
        clouds.push_back(Vector2(screenWidth + screenWidth*0.275, cloudHeight - 25));
        clouds.push_back(Vector2(screenWidth + screenWidth*0.325, cloudHeight - 25));
        clouds.push_back(Vector2(screenWidth + screenWidth*0.275, cloudHeight + 25));
        clouds.push_back(Vector2(screenWidth + screenWidth*0.325, cloudHeight + 25));
        clouds.push_back(Vector2(screenWidth + screenWidth*0.375, cloudHeight));
    }

    void addMountain(){
        mountainHeight = rand() %150 + 125;
        mountainWidth = rand() %150 + 325;
        mountains.push_back(Vector2(screenWidth, seatCenter.y));
        mountains.push_back(Vector2(screenWidth + mountainWidth/2, seatCenter.y + mountainHeight));
        mountains.push_back(Vector2(screenWidth + mountainWidth, seatCenter.y));
    }

    void renderMountains(){
        vector<Vector2> mountain;
        for(int i = 0; i < mountains.size(); i ++){
            mountains[i].x -= speed*50;
        }
        CV::color(0.54, 0.27, 0.07);
        for (int i = 0; i < mountains.size(); i++){
            mountain.clear();
            mountain.push_back(mountains[i]);
            mountain.push_back(mountains[i+1]);
            mountain.push_back(mountains[i+2]);
            i+=2;
            CV::polygonFill(mountain);
        }
        if(mountains.back().x <= screenWidth){
            addMountain();
        }
        if(controlPoints){
            for(int i = 0; i < mountains.size(); i++){
                CV::color(1, 0, 0);
                CV::circleFill(mountains[i], 5, 100);
            }
        }
    }

    void renderSky(){
        CV::color(0, 1, 1);
        CV::rectFill(0, seatCenter.y, screenWidth, screenHeight);
    }

    void renderBack(){
        CV::color(0.56, 0.93, 0.3);
        CV::rectFill(0, screenWidth*0.050, screenWidth, seatCenter.y);
    }

    void renderFloor(){
        CV::color(0.5, 0.5, 0.5);
        CV::rectFill(0, 0, screenWidth, screenWidth*0.050);
    }

    void render(float _speed, bool _controlPoints){
        controlPoints = _controlPoints;
        speed = _speed;
        renderSky();
        renderBack();
        renderClouds();
        renderMountains();
        renderFloor();
    }
};
#endif
