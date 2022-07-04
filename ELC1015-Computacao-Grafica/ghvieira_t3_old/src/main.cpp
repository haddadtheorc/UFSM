#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "gl_canvas2d.h"

#include "gear.h"
#include "camera.h"


int opcao  = 50;
int screenWidth = 750, screenHeight = 750;
int mouseX, mouseY;

gear* gear1;
camera* cam1;

int spin_orientation = 1;
bool spin_toggle = false;
float default_teeth = 10;
vetor gear1_center = vetor(375, 375, 375);


void render()
{

    float **mat = (float **)malloc(4 * sizeof(float*));
    for(int i = 0; i < 4; i++) mat[i] = (float *)malloc(4 * sizeof(float));
    if(spin_toggle)
        gear1->rotate_gear_3d(spin_orientation);
    cam1->transformation(mat);
    gear1->draw_gear_3d(mat);
    //gear1->draw_gear_2d();

    CV::color(0, 0, 0);
}

// O keyboard foi usado para algumas interações com a engrenagem, como ativar e desativar sua rotação bem como alterar o sentido de rotação
void keyboard(int key)
{
    switch(key)
    {
        case 27:
            exit(0);
        break;

        case 32:
            if(spin_toggle)
            {
                spin_toggle = false;
            }
            else
            {
                spin_toggle = true;
            }
        break;

        case 202:
            spin_orientation = -1;
        break;

        case 200:
            spin_orientation = 1;
        break;


   }
}

// Usado para aumentar e diminuir o número de dentes da engrenagem
void keyboardUp(int key)
{
    printf("\nLiberou tecla: %d" , key);
    switch(key)
    {
        case 201:
            spin_toggle = false;
            default_teeth += 1.00;
            if(default_teeth > 24.0)
            {
                default_teeth -=1.00;
            }
            gear1 = gear1 = new gear(gear1_center, 200.0, default_teeth);
        break;

        case 203:
            spin_toggle = false;
            default_teeth -= 1.00;
            if(default_teeth < 3.00)
            {
                default_teeth +=1.00;
            }
            gear1 = gear1 = new gear(gear1_center, 200.0, default_teeth);
        break;

    }
}

// A interação com mouse aqui é usada para ativar a movimentação da câmera seguindo o mouse com o botão 0 apertado
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if( button == 0 )
    {
        cam1->toggle_mouse(mouseX, mouseY);
    }
    cam1->rotate_camera(mouseX, mouseY);
}

int main(void)
{
    gear1 = new gear(gear1_center, 200.0, default_teeth);
    vetor cam1_pos = vetor(0, 0, -300);
    vetor cam1_up = vetor (0, 1, 0);
    vetor cam1_right = vetor (1, 0, 0);
    vetor cam1_target = vetor (0, 0, 0);
    cam1 = new camera(cam1_pos, cam1_up, cam1_target, cam1_right);

    CV::init(&screenWidth, &screenHeight, "Trabalho 4 - Geração de Engrenagens 3D");
    CV::run();
}
