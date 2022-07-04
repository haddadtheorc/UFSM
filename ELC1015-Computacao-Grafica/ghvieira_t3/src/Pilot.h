#ifndef PILOT_H
#define PILOT_H
#include "gl_canvas2d.h"
#include <vector>
using namespace std;
/*
########################################
- Classe para controle do Piloto

void initialize() -> preenchendo todas as informações base para criação do personagem
void renderCloak() -> renderização da capa do personagem
void renderUpper() -> renderização da cintura pra cima do personagem -> auxiliada pelas funções void renderCloak() e renderPilotTorso() para, respectivamente, capa e torso do personagem
Vector2 calculateKnee() -> cálculo da posição correta do joelho, baseado no tamanho da perna e na posição do pedal e do banco
void renderLeg() -> renderização de cada perna por vez, recebe como argumento qual irá renderizar
####################################
*/
class Pilot{
public:

    vector <Vector2> cloak;
    Vector2 cloakTransform;
    Vector2 headCenter = Vector2(pilotRatio*0.350, pilotRatio*0.350);
    float speed;
    int cloakMod = 1;
    int pilotRatio;
    float shinSize;
    float thighSize;
    bool controlPoints = false;
    Vector2 seatCenter;
    Vector2 abdomen;
    vector <Vector2> pedalCoords;

    void initialize(Vector2 _seatCenter, vector<Vector2> _pedalCoords, int screenWidth){
        pilotRatio = screenWidth;
        shinSize = pilotRatio * 0.080;
        thighSize = shinSize;
        headCenter = Vector2(pilotRatio*0.350, pilotRatio*0.350);
        seatCenter = _seatCenter;
        abdomen = Vector2(seatCenter.x - pilotRatio*0.042, seatCenter.y - pilotRatio*0.005);
        pedalCoords = _pedalCoords;
        cloak.push_back(Vector2(pilotRatio*0.145, pilotRatio*0.310));
        cloak.push_back(Vector2(pilotRatio*0.245, pilotRatio*0.260));
        cloak.push_back(Vector2(pilotRatio*0.245, pilotRatio*0.360));
        cloak.push_back(Vector2(pilotRatio*0.345, pilotRatio*0.310));
    }

    //bezier with 4 control points
    void renderCloak(){
        for(float t = 0; t < 1; t += 0.0001){
            cloakTransform = ( cloak[0] * (1-t) * (1-t) * (1-t) ) + ( cloak[1] * 3 * t * ((1-t) * (1-t))) + ( cloak[2] * 3 * t * t *  (1-t)) + ( cloak[3] * t * t * t);
            CV::color(1, 0.5, 0);
            glPointSize(3);
            CV::point(cloakTransform);
            glPointSize(1);
            //animation
            cloak[1].y += speed * 0.005 * cloakMod;
            cloak[2].y -= speed * 0.005 * cloakMod;
            if(cloak[1].y > pilotRatio*0.360)
                cloakMod*= -1;
            if(cloak[1].y < pilotRatio*0.260)
                cloakMod*= -1;
        }
        if(controlPoints){
            CV::color(1, 0, 0);
            for(int i = 0; i < cloak.size(); i++){
                CV::circleFill(cloak[i], 5, 100);
            }
        }
    }

    void renderPilotTorso(){
        CV::color(0, 0, 0);
        CV::circleFill(headCenter, pilotRatio*0.025, 100);
        glLineWidth(7);
        //torso
        CV::line(headCenter.x, headCenter.y, seatCenter.x - pilotRatio*0.042, seatCenter.y - pilotRatio*0.005);
        CV::circleFill(seatCenter.x - pilotRatio*0.042, seatCenter.y - pilotRatio*0.005, 2, 100);
        //lArm
        CV::line(pilotRatio*0.343, pilotRatio*0.300, pilotRatio*0.367, pilotRatio*0.215);
        //lHand
        CV::line(pilotRatio*0.365, pilotRatio*0.215, pilotRatio*0.400, pilotRatio*0.215);
        //rArm
        CV::line(pilotRatio*0.346, pilotRatio*0.300, pilotRatio*0.402, pilotRatio*0.235);
        //rHand
        CV::line(pilotRatio*0.400, pilotRatio*0.235, pilotRatio*0.435, pilotRatio*0.235);
        glLineWidth(1);
    }

    void renderUpper(bool _controlPoints, vector<Vector2> _pedalCoords, float _speed){
        controlPoints = _controlPoints;
        speed = _speed;
        pedalCoords = _pedalCoords;
        renderCloak();
        renderPilotTorso();
    }

    Vector2 calculateKnee(Vector2 a, Vector2 b, float aRadius, float bRadius){
        float d = sqrt( pow( (a.x-b.x), 2 ) +  pow( (a.y-b.y), 2 ));
        float l = (pow(aRadius, 2) - pow(bRadius, 2) + pow(d, 2) ) / (2*d);
        float h = sqrt(pow(aRadius, 2) - pow(l, 2));
        float x = l/d * (b.x - a.x) - h/d * (b.y - a.y) + a.x;
        float y = l/d * (b.y - a.y) + h/d * (b.x - a.x) + a.y;
        return Vector2(x, y);
    }

    void renderLeg(char* leg){
        Vector2 knee;
        CV::color(0, 0, 0);
        glLineWidth(7);
        if(leg == "right"){
            knee = calculateKnee(abdomen, pedalCoords[0], thighSize, shinSize);
            CV::line(pedalCoords[0].x, pedalCoords[0].y, knee.x, knee.y);
        }
        else{
            knee = calculateKnee(abdomen, pedalCoords[1], thighSize, shinSize);
            CV::line(pedalCoords[1].x, pedalCoords[1].y, knee.x, knee.y);
        }
        CV::circleFill(knee.x, knee.y, 3, 100);
        CV::line(abdomen.x, abdomen.y, knee.x, knee.y);
        glLineWidth(1);
        if(controlPoints){
            CV::color(1, 0, 0);
            CV::circleFill(knee.x, knee.y, 5, 100);
            CV::circle(abdomen.x, abdomen.y, thighSize, 100);
            CV::circle(pedalCoords[0].x, pedalCoords[0].y, shinSize, 100);
            CV::circle(pedalCoords[1].x, pedalCoords[1].y, shinSize, 100);
        }
    }
};
#endif
