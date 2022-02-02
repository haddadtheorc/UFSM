
#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "gl_canvas2d.h"


int opcao  = 50;
int screenWidth = 750, screenHeight = 750;
int mouseX, mouseY;

//aqui sao variaveis pra entrar e sair do modo de edicao de pista bem como saber se o usuario esta reposicionando um ponto de controle
bool track_edit = true;
int track_mouse_point = -1;

//vetores para armazenar os pontos de controle bem como os pontos interpolados para a bezier
std::vector<Vector2> track_control_points;
std::vector<Vector2> bezier_final;

//aqui é o quanto eu quero que a bezier seja definida, quando menor mais suave a curva vai ser
float bezier_shift = 0.01;


//funcao que desenha o grafo de controle entre os pontos de controle
void draw_control_graph(){
    for(int i = 0; i < track_control_points.size()-1; i++){
        CV::color(1, 0, 1);
        CV::line(track_control_points[i].x, track_control_points[i].y, track_control_points[i+1].x, track_control_points[i+1].y);
    }
}

//funcao que desenha os pontos de controle
void draw_control_points(){
    for(int i = 0; i < track_control_points.size(); i++){
        CV::color(0, 0, 0);
        if(track_mouse_point == i){
            CV::color(0, 1, 0);
            track_control_points[i].x = mouseX;
            track_control_points[i].y = mouseY;
        }
        CV::circleFill(track_control_points[i].x, track_control_points[i].y, 5, 30);
    }
}

//funcao que testa se o mouse clicou em um ponto de controle existente, para permitir mover esse ponto de controle
bool control_point_collision (int x, int y){
    for(int i = 0; i < track_control_points.size(); i++){
        if(x < track_control_points[i].x + 5 && x > track_control_points[i].x -5  && y < track_control_points[i].y + 5 && y > track_control_points[i].y -5){
            track_mouse_point = i;
            return true;
        }
    }
    track_mouse_point = -1;
    return false;
}

//funcao que preenche o vetor de pontos de controle a medida na qual o usuario clica na tela
void track_fill_vector (int x, int y){
    track_control_points.push_back(Vector2(x, y));
}

//funcao que desenha linhas entre os pontos gerados da bezier
void draw_bezier(){
    CV::color(1, 0, 0);
    for(int i = 0; i < bezier_final.size()-1; i++){
        CV::line(bezier_final[i].x, bezier_final[i].y, bezier_final[i+1].x, bezier_final[i+1].y);
    }
}

//funcao que calcula os pontos de interpolacao para as curvas bezier
void bezier(){
    bezier_final.clear();
    CV::color(0, 0, 0);

    int rep = track_control_points.size()/3;
    int cont = 0;

    for(int i = 0; i < rep; i++){

        for(float t = 0; t <=(1.00+bezier_shift); t+=bezier_shift){
            float xCurva = (1-t)*(1-t)*track_control_points[cont].x + 2.0*t*(1-t)*track_control_points[cont + 1].x + t*t*track_control_points[cont + 2].x;
            float yCurva = (1-t)*(1-t)*track_control_points[cont].y + 2.0*t*(1-t)*track_control_points[cont + 1].y + t*t*track_control_points[cont + 2].y;
            bezier_final.push_back(Vector2(xCurva, yCurva));
        }
        cont +=3;
    }
    int var = track_control_points.size()%3;

    if(var == 0){
        bezier_final.push_back(Vector2(track_control_points[0].x, track_control_points[0].y));
    }
    else if(var == 1){
        bezier_final.push_back(Vector2(track_control_points[track_control_points.size()-1].x, track_control_points[track_control_points.size()-1].y));
        bezier_final.push_back(Vector2(track_control_points[0].x, track_control_points[0].y));
    }
    else{
        bezier_final.push_back(Vector2(track_control_points[track_control_points.size()-2].x, track_control_points[track_control_points.size()-2].y));
        bezier_final.push_back(Vector2(track_control_points[track_control_points.size()-1].x, track_control_points[track_control_points.size()-1].y));
        bezier_final.push_back(Vector2(track_control_points[0].x, track_control_points[0].y));
    }
}


void render(){
    CV::color(1, 1, 1);
    if(track_edit){
        draw_control_points();
    }
    if(track_control_points.size()>2){
        if(track_edit)
            draw_control_graph();
        bezier();
        draw_bezier();
    }
}


void keyboard(int key){
    printf("\nPressinou tecla: %d" , key);
    switch(key){
        case 13:
            if(track_edit){
                track_edit = false;
            }
            else{
                track_edit = true;
            }
        case 27:
            exit(0);
        case 122:
            track_control_points.erase(track_control_points.end());
        break;
    }
}


void keyboardUp(int key){
    printf("\nLiberou tecla: %d" , key);
}

//aqui ele testa se houve a colisao com um ponto de controle, se houve esse ponto fica verde e passa a seguir o mouse ate ser clicado de novo e volta a ser estatico
void mouse(int button, int state, int wheel, int direction, int x, int y){
    mouseX = x;
    mouseY = y;
    if(state == 0 ){
            if(track_edit){
                if (track_mouse_point !=-1){
                    track_control_points[track_mouse_point].x = x;
                    track_control_points[track_mouse_point].y = y;
                    track_mouse_point = -1;
                }
                else if(control_point_collision (x, y)){

                }
                else
                    track_fill_vector(x, y);
                }
    }
}


int main(void){
    CV::init(&screenWidth, &screenHeight, "Trabalho 3 - Transformações Geométricas e Curvas");
    CV::run();
}
