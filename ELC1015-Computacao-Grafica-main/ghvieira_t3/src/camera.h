#include "Vetor.h"
#include <cmath>


class camera{

    public:
    vetor pos;
    vetor up;
    vetor target;
    vetor right;
    bool follow;
    vetor mouse;
    vetor angles;

    camera (vetor _pos, vetor _up, vetor _target, vetor _right)
    {
        pos = _pos;
        up = _up;
        target = _target;
        right = _right;
        follow = false;
        angles = vetor(0,0,0);
    }

    void toggle_mouse(float mx, float my)
    {
        if(follow){
            follow = false;

            //pos = moving_pos;
        }else{
            follow = true;
            mouse.x = mx;
            mouse.y = my;
            }

    }

    void rotate_camera(float mx, float my)
    {
        if(follow){
            //calcula a diferença entre onde o mouse foi clicado e onde ele esta agora
            float ang_y = ((mouse.y-my)* 3.1415/180*0.5);
            mouse.y = my;
            float ang_x = ((mouse.x-mx)* 3.1415/180*0.5);
            mouse.x = mx;

            //Monta o vetor correspondente a rotação horizontal da camera
            float q[4] = {sin(ang_x/2)*up.x, sin(ang_x/2)*up.y, sin(ang_x/2)*up.z, cos(ang_x/2)};

            //Rotaciona a camera
            vetor novo = rotate_quartenion(this->pos, q);
            this->pos = novo;

            //Calcula o vetor Frente
            vetor v = target - pos;
            v = v.normalize();

            //Calcula o vetor Direita
            vetor r = v^up;
            r = r.normalize();

            //Monta o vetor correspondente a rotação vertical da camera
            float k[4] = {sin(ang_y/2)*r.x, sin(ang_y/2)*r.y, sin(ang_y/2)*r.z, cos(ang_y/2)};
            novo = rotate_quartenion(this->pos, k);
            this->pos = novo;
            //Rotaciona o vetor Cima
            novo = rotate_quartenion(this->up, k);
            this->up = novo;
        }
    }

    vetor rotate_quartenion(vetor v, float* q)
    {

        vetor u = vetor(q[0],q[1], q[2]);
        float s = q[3];

        //result = 2 * u*v * u + (s*s - u*u) * v + 2 * s * u^v;
        vetor result;
        vetor vaux1, vaux2, vaux3;
        float aux1, aux2, aux3;

        //2 * u*v * u
        aux1 = u * v;
        aux1 = 2.0f * aux1;
        vaux1 = u * aux1;

        //(s*s - u*u) * v
        aux2 = (s*s - u*u);
        vaux2 = v * aux2;

        //2 * s * u^v
        vaux3 = u^v;
        vaux3 = vaux3 * s * 2;
        result = vaux1 + vaux2 + vaux3;

        return result;
    }


    void transformation(float ** res)
    {

        // Descobre o vetor da camera até o alvo
        vetor vtarget = pos - target;
        vtarget = vtarget.normalize();

        // Normaliza o vetor Cima
        vetor vup = up;
        vup = vup.normalize();

        // Calcula o vetor que aponta para a Direita da camera
        vetor vright = vtarget^vup;
        vright = vright.normalize();

        // Recalcula o vetor Cima para ficar em 90 graus
        vup = vright ^ vtarget;
        vup = vup.normalize();

        // Monta a matriz da camera
        float camera_matrix[4][4] = {
                                   vright.x, vright.y, vright.z, 0,
                                    vup.x, vup.y, vup.z, 0,
                                   vtarget.x, vtarget.y, vtarget.z, 0,
                                   0, 0, 0, 1};


        // Monta a matriz de translação da camera para enquadrar o objeto
        float translation_matrix[4][4] = {1, 0, 0, -pos.x,
                                          0, 1, 0, -pos.y,
                                          0, 0, 1, -pos.z,
                                          0, 0, 0, 1};

        // Monta a matriz para ajustar o tamanho do objeto na tela
        float dist_to_screen = 200.0;
        float scale_matrix[4][4] = {dist_to_screen, 0, 0, 0,
                                    0, dist_to_screen, 0, 0,
                                    0,   0, 1, 0,
                                    0,   0, 0, 1};

        // Calcula a Matriz de transformação auxiliar
        float res_aux[4][4];
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res_aux[i][j] = 0;
                for (int k = 0; k < 4; k++)
                {
                    res_aux[i][j] += camera_matrix[k][j] * scale_matrix[i][k];
                }
            }
        }

        // Calcula a Matriz de transformação final
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res[i][j] = 0;
                for (int k = 0; k < 4; k++)
                {
                    res[i][j] += translation_matrix[k][j] * res_aux[i][k];
                }
            }
        }

    }

};

