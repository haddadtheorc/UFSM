#include "Vetor.h"
#include <vector>
#define DEFAULT_SPEED 10
#define DEFAULT_CIRCLE_POINTS 100



// A classe da engrenagem para armazenar todos seus ponntos e informações pertinentes à classe
// Tem as funções que desenham a engrenagem em 2d, 3d, bem como a rotacionam

class gear
{
    public:
        vetor center;
        vetor ang;
        std::vector <vetor> points;
        std::vector <vetor> inner_circle_points;
        std::vector <vetor> outer_circle_points;
        std::vector <vetor> gear_teeth_points;
        float gear_size;
        float speed;
        float teeth_number;

        gear(vetor _center,  float _gear_size, float _teeth_number)
        {
            center = _center;
            gear_size = _gear_size;
            teeth_number = _teeth_number;
            speed = DEFAULT_SPEED;
            float m = gear_size/2;

            //criação dos pontos de controle do círculo interno, externo e dentes da engrenagem
            float ang1 = 0;
            float inc = PI_2/DEFAULT_CIRCLE_POINTS;
            for(int i = 0; i <= DEFAULT_CIRCLE_POINTS; i++)
            {
                this->inner_circle_points.push_back(vetor((cos(ang1)*(m/5)), (sin(ang1)*(m/5)), 0));
                this->outer_circle_points.push_back(vetor((cos(ang1)*(m)), (sin(ang1)*(m)), 0));
                ang1 = ang1 + inc;
            }
            ang1 = 0;
            for(int i = 0; i <= DEFAULT_CIRCLE_POINTS; i++)
            {
                this->inner_circle_points.push_back(vetor((cos(ang1)*(m/5)), (sin(ang1)*(m/5)), -25));
                this->outer_circle_points.push_back(vetor((cos(ang1)*(m)), (sin(ang1)*(m)), -25));
                ang1 = ang1 + inc;
            }

            float teeth_divisions = 360/(teeth_number*2);
            ang1 = teeth_divisions * 3.14159265/180;
            float ang2 = ang1;
            for(float i = 0.0f; i < teeth_number*2; i+=2)
            {
                this->gear_teeth_points.push_back(vetor((cos(i*ang1 - (ang1/6))*(m)), (sin(i * ang1 - (ang1/6))*(m)), 0));
                this->gear_teeth_points.push_back(vetor((cos((i*ang1) + (ang1/3))*(m*1.5)), (sin((i*ang1) + (ang1/3))*(m*1.5)), 0));
                this->gear_teeth_points.push_back(vetor((cos((i*ang1) - (ang1/3) + ang1)*(m*1.5)), (sin((i*ang1) - (ang1/3) + ang1)*(m*1.5)), 0));
                this->gear_teeth_points.push_back(vetor((cos(i*ang1 + ang2+ (ang1/6))*(m)), (sin(i*ang1 + ang2+ (ang1/6))*(m)), 0));

            }
            for(float i = 0.0f; i < teeth_number*2; i+=2)
            {
                this->gear_teeth_points.push_back(vetor((cos(i*ang1 - (ang1/6))*(m)), (sin(i * ang1 - (ang1/6))*(m)), -25));
                this->gear_teeth_points.push_back(vetor((cos((i*ang1) + (ang1/3))*(m*1.5)), (sin((i*ang1) + (ang1/3))*(m*1.5)), -25));
                this->gear_teeth_points.push_back(vetor((cos((i*ang1) - (ang1/3) + ang1)*(m*1.5)), (sin((i*ang1) - (ang1/3) + ang1)*(m*1.5)), -25));
                this->gear_teeth_points.push_back(vetor((cos(i*ang1 + ang2+ (ang1/6))*(m)), (sin(i*ang1 + ang2+ (ang1/6))*(m)), -25));
            }
        }

        void draw_gear_2d()
        {
            CV::color(0,0,0);
            for (int i = 0; i < DEFAULT_CIRCLE_POINTS; i++)
            {
                CV::line(inner_circle_points[i].x + center.x, inner_circle_points[i].y + center.y, inner_circle_points[i+1].x + center.x, inner_circle_points[i+1].y + center.y);
            }

            for (int i = 0; i < DEFAULT_CIRCLE_POINTS; i++)
            {
                CV::line(outer_circle_points[i].x + center.x, outer_circle_points[i].y + center.y, outer_circle_points[i+1].x + center.x, outer_circle_points[i+1].y + center.y);
            }

            for(int i = 0; i < teeth_number*4; i+=4)
            {
                CV::line(gear_teeth_points[i].x + center.x, gear_teeth_points[i].y + center.y, gear_teeth_points[i+1].x + center.x, gear_teeth_points[i+1].y + center.y);
                CV::line(gear_teeth_points[i+1].x + center.x, gear_teeth_points[i+1].y + center.y, gear_teeth_points[i+2].x + center.x, gear_teeth_points[i+2].y + center.y);
                CV::line(gear_teeth_points[i+2].x + center.x, gear_teeth_points[i+2].y + center.y, gear_teeth_points[i+3].x + center.x, gear_teeth_points[i+3].y + center.y);
            }
        }

        void draw_gear_3d(float ** mat)
        {
            std::vector <vetor> converted_points_inner;
            std::vector <vetor> converted_points_outer;
            std::vector <vetor> converted_points_teeth;


            for (int n = 0; n < DEFAULT_CIRCLE_POINTS*2; n++){
                float res_inner [4];
                float res_outer [4];
                float res_teeth [4];
                float temp_points_inner[4] = {inner_circle_points[n].x, inner_circle_points[n].y, inner_circle_points[n].z, 1};
                float temp_points_outer [4] = {outer_circle_points[n].x, outer_circle_points[n].y, outer_circle_points[n].z, 1};
                float temp_points_teeth [4] = {gear_teeth_points[n].x, gear_teeth_points[n].y, gear_teeth_points[n].z, 1};

                for (int i = 0; i < 4; i++)
                {
                    res_inner[i] = 0.0f;
                    res_outer[i] = 0.0f;
                    res_teeth[i] = 0.0f;

                    for (int k = 0; k < 4; k++){
                        res_inner[i] += temp_points_inner[k] * mat[i][k];
                        res_outer[i] += temp_points_outer[k] * mat[i][k];
                        res_teeth[i] += temp_points_teeth[k] * mat[i][k];
                    }

                }
                converted_points_inner.push_back (vetor(res_inner[0], res_inner[1], res_inner[2]));
                converted_points_outer.push_back(vetor(res_outer[0], res_outer[1], res_outer[2]));
                converted_points_teeth.push_back(vetor(res_teeth[0], res_teeth[1], res_teeth[2]));
            }

            for (int n = 0; n < DEFAULT_CIRCLE_POINTS*2; n++)
            {
                float res_inner[4] = {converted_points_inner[n].x, converted_points_inner[n].y, converted_points_inner[n].z, 1};
                float res_outer[4] = {converted_points_outer[n].x, converted_points_outer[n].y, converted_points_outer[n].z, 1};
                float res_teeth[4] = {converted_points_teeth[n].x, converted_points_teeth[n].y, converted_points_teeth[n].z, 1};
                converted_points_inner[n] = (vetor(res_inner[0]/res_inner[2], res_inner[1]/res_inner[2], 0));
                converted_points_outer[n] = (vetor(res_outer[0]/res_outer[2], res_outer[1]/res_outer[2], 0));
                converted_points_teeth[n] = (vetor(res_teeth[0]/res_teeth[2], res_teeth[1]/res_teeth[2], 0));
            }

            CV::color (0, 0, 0);
            //desenha a parte de trás da engrenagem
            for (int i = 0; i < DEFAULT_CIRCLE_POINTS; i++)
            {
                CV::line(converted_points_inner[i].x + center.x, converted_points_inner[i].y + center.y, converted_points_inner[i+1].x + center.x, converted_points_inner[i+1].y + center.y);
                CV::line(converted_points_outer[i].x + center.x, converted_points_outer[i].y + center.y, converted_points_outer[i+1].x + center.x, converted_points_outer[i+1].y + center.y);
            }

            //desenha a parte da frente da engrenagem
            for (int j = DEFAULT_CIRCLE_POINTS+1; j < DEFAULT_CIRCLE_POINTS*2 -1; j++)
            {
                CV::line(converted_points_inner[j].x + center.x, converted_points_inner[j].y + center.y, converted_points_inner[j+1].x + center.x, converted_points_inner[j+1].y + center.y);
                CV::line(converted_points_outer[j].x + center.x, converted_points_outer[j].y + center.y, converted_points_outer[j+1].x + center.x, converted_points_outer[j+1].y + center.y);

            }

            CV::line(converted_points_inner[DEFAULT_CIRCLE_POINTS*2-1].x + center.x, converted_points_inner[DEFAULT_CIRCLE_POINTS*2-1].y + center.y, converted_points_inner[DEFAULT_CIRCLE_POINTS+1].x + center.x, converted_points_inner[DEFAULT_CIRCLE_POINTS+1].y + center.y);
            CV::line(converted_points_outer[DEFAULT_CIRCLE_POINTS*2-1].x + center.x, converted_points_outer[DEFAULT_CIRCLE_POINTS*2-1].y + center.y, converted_points_outer[DEFAULT_CIRCLE_POINTS+1].x + center.x, converted_points_outer[DEFAULT_CIRCLE_POINTS+1].y + center.y);

            //desenha a conexão entre as duas engrenagens 2d
            for(int k = 0; k < DEFAULT_CIRCLE_POINTS; k+=10)
            {
                CV::line(converted_points_inner[k].x + center.x, converted_points_inner[k].y + center.y, converted_points_inner[k + (DEFAULT_CIRCLE_POINTS+1)].x + center.x, converted_points_inner[k + (DEFAULT_CIRCLE_POINTS+1)].y + center.y);
                CV::line(converted_points_outer[k].x + center.x, converted_points_outer[k].y + center.y, converted_points_outer[k + (DEFAULT_CIRCLE_POINTS+1)].x + center.x, converted_points_outer[k + (DEFAULT_CIRCLE_POINTS+1)].y + center.y);
            }
//
//            //desenha os raios da engrenagem
//            for(int k = 0; k < DEFAULT_CIRCLE_POINTS*2; k+=10)
//            {
//                CV::line(converted_points_outer[k].x + center.x, converted_points_outer[k].y + center.y, converted_points_inner[k].x + center.x, converted_points_inner[k].y + center.y);
//            }

            //desenha os dentes da engrenagem
            for(int i = 0; i < teeth_number*8; i+=4)
            {
            CV::line(converted_points_teeth[i].x + center.x, converted_points_teeth[i].y + center.y, converted_points_teeth[i+1].x + center.x, converted_points_teeth[i+1].y + center.y);
            CV::line(converted_points_teeth[i+1].x + center.x, converted_points_teeth[i+1].y + center.y, converted_points_teeth[i+2].x + center.x, converted_points_teeth[i+2].y + center.y);
            CV::line(converted_points_teeth[i+2].x + center.x, converted_points_teeth[i+2].y + center.y, converted_points_teeth[i+3].x + center.x, converted_points_teeth[i+3].y + center.y);
            }

            for(int i = 0; i < teeth_number*4; i+=4)
            {
            CV::line(converted_points_teeth[i+1].x + center.x, converted_points_teeth[i+1].y + center.y, converted_points_teeth[i+teeth_number*4 +1].x + center.x, converted_points_teeth[i+teeth_number*4 +1].y + center.y);
            CV::line(converted_points_teeth[i+2].x + center.x, converted_points_teeth[i+2].y + center.y, converted_points_teeth[i+teeth_number*4 +2].x + center.x, converted_points_teeth[i+teeth_number*4 +2].y + center.y);

            }

        }

        void rotate_gear_3d(int spin_orientation)
        {
            float angulo = 1*3.1415/180;
            float new_x, new_y, new_z;
            float new_x_outer, new_y_outer, new_z_outer, new_x_inner, new_y_inner, new_z_inner, new_x_teeth, new_y_teeth, new_z_teeth;

            //aqui só para controlar a orientação do giro da engrenagem (com base na interação com o teclado e afins)
            if(spin_orientation < 0){
                angulo = angulo * -1;
            }

            //a matriz de rotação para multiplicar os pontos, no caso sendo rotados no eixo Z
            double matriz[3][3] = {cos(angulo),-sin(angulo), 0,
                                   sin(angulo), cos(angulo), 0,
                                    0,           0,          1
                                  };


            for(unsigned int i = 0; i < DEFAULT_CIRCLE_POINTS *2; i++)
            {
                //faz a rotação dos pontos do círculo interior
                new_x_inner = inner_circle_points[i].x*matriz[0][0] + inner_circle_points[i].y*matriz[0][1] + inner_circle_points[i].z*matriz[0][2];
                new_y_inner = inner_circle_points[i].x*matriz[1][0] + inner_circle_points[i].y*matriz[1][1] + inner_circle_points[i].z*matriz[1][2];
                new_z_inner = inner_circle_points[i].x*matriz[2][0] + inner_circle_points[i].y*matriz[2][1] + inner_circle_points[i].z*matriz[2][2];
                inner_circle_points[i].x = new_x_inner;
                inner_circle_points[i].y = new_y_inner;
                inner_circle_points[i].z = new_z_inner;

                //faz a rotação dos pontos do círculo exterior
                new_x_outer = outer_circle_points[i].x*matriz[0][0] + outer_circle_points[i].y*matriz[0][1] + outer_circle_points[i].z*matriz[0][2];
                new_y_outer = outer_circle_points[i].x*matriz[1][0] + outer_circle_points[i].y*matriz[1][1] + outer_circle_points[i].z*matriz[1][2];
                new_z_outer = outer_circle_points[i].x*matriz[2][0] + outer_circle_points[i].y*matriz[2][1] + outer_circle_points[i].z*matriz[2][2];
                outer_circle_points[i].x = new_x_outer;
                outer_circle_points[i].y = new_y_outer;
                outer_circle_points[i].z = new_z_outer;
            }
            for(int i = 0; i < gear_teeth_points.size(); i++){
                //faz a rotação dos pontos dos dentes
                new_x_teeth = gear_teeth_points[i].x*matriz[0][0] + gear_teeth_points[i].y*matriz[0][1] + gear_teeth_points[i].z*matriz[0][2];
                new_y_teeth = gear_teeth_points[i].x*matriz[1][0] + gear_teeth_points[i].y*matriz[1][1] + gear_teeth_points[i].z*matriz[1][2];
                new_z_teeth = gear_teeth_points[i].x*matriz[2][0] + gear_teeth_points[i].y*matriz[2][1] + gear_teeth_points[i].z*matriz[2][2];
                gear_teeth_points[i].x = new_x_teeth;
                gear_teeth_points[i].y = new_y_teeth;
                gear_teeth_points[i].z = new_z_teeth;
            }

        }
};
