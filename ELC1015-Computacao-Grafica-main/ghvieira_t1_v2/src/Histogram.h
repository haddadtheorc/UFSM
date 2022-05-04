#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include "gl_canvas2d.h"
#include <vector>
#include <algorithm>

//HEADER PARA GERENCIAMENTO DO HISTOGRAMA

//Seu método plot() trata da renderização do histograma da imagem na tela
//A imagem a ter seu histograma renderizado, bem como o tamanho da tela são os argumentos necessários para a função
//Foram criados dois histogramas:
//o plotRecurrence() cria o histograma c base na recorrencia daquela cor, de tal forma que o eixo Y é a quantidade de vezes que aquela cor aparece, enquanto o eixo X é o valor da cor
//o plotRecurrence cria o histograma baseado na intensidade de cor, o eixo Y é o valor daquele pixel, enqquanto o eixo X é o pixel em si

class Histogram{
    public:
        bool plotMode = true;

    void plot(Images images, int screenWidth, int screenHeight){
        //EIXOS
        int x1 = screenWidth - screenWidth*0.30, y1 = screenHeight - screenHeight*0.30, x2 = screenWidth, y2 = screenHeight;
        CV::color(1, 1, 1);
        CV::rect(x1 -1, y1 -1, x2 +1, y2 +1);

        if(this->plotMode){
            plotRecurrence(images, screenWidth, screenHeight);
        }
        else{
            plotIntensity(images, screenWidth, screenHeight);
        }
    }

    void plotIntensity(Images images, int screenWidth, int screenHeight){
        if(images.current_image == -1)
            return;

        int x1 = screenWidth - screenWidth*0.30, y1 = screenHeight - screenHeight*0.30, x2 = screenWidth, y2 = screenHeight;
        Image* image = images.imgVector[images.current_image];
        float r1 = -1, r2 = -1, g1 = -1, g2 = -1, b1 = -1, b2=-1, gray1 = -1, gray2 = -1;

        for(int i = 0; i < image->img->getHeight()*image->img->getWidth()*3.0; i +=3){
            if(image->filter->r_channel){
                if(r1 != -1){
                    if(r2 != -1){
                        r1 = r2;
                    }
                    r2 = image->img->data[i]/255.0;
                    if(!image->filter->reverse_rgb)
                        r2 = 1-r2;
                    CV::color(1, 0, 0);
                    CV::line(x1+(i/3.0),y1-(r1*(y1 - y2)),x1+(i/3.0),y1-(r2*(y1 - y2)));
                }
                else if (r1==-1 && r2==-1){
                    r1 = image->img->data[i]/255.0;
                }
            }
            if(image->filter->g_channel){
                if(g1 != -1){
                    if(g2 != -1){
                        g1 = g2;
                    }
                    g2 = image->img->data[i+1]/255.0;
                    if(!image->filter->reverse_rgb)
                        g2 = 1-g2;
                    CV::color(0, 1, 0);
                    CV::line(x1+(i/3.0),y1-(g1*(y1 - y2)),x1+(i/3.0),y1-(g2*(y1 - y2)));
                }
                else if (g1==-1 && g2==-1){
                    g1 = image->img->data[i+2]/255.0;
                }
            }
            if(image->filter->b_channel){
                if(b1 != -1){
                    if(b2 != -1){
                        b1 = b2;
                    }
                    b2 = image->img->data[i+2]/255.0;
                    if(!image->filter->reverse_rgb)
                        b2 = 1-b2;
                    CV::color(0, 0, 1);
                    CV::line(x1+(i/3.0),y1-(b1*(y1 - y2)),x1+(i/3.0),y1-(b2*(y1 - y2)));
                }
                else if (b1==-1 && b2==-1){
                    b1 = image->img->data[i+2]/255.0;
                }
            }
            if(!image->filter->grayscale){
                if(gray1 != -1){
                    if(gray2 != -1){
                        gray1 = gray2;
                    }
                    gray2 = 0.299*(image->img->data[i]/255.0)+0.587*(image->img->data[i+1]/255.0)+0.114*(image->img->data[i+2]/255.0);
                    if(!image->filter->reverse_rgb)
                        gray2 = 1-gray2;
                    CV::color(1, 1, 1);
                    CV::line(x1+(i/3.0),y1-(gray1*(y1 - y2)),x1+(i/3.0),y1-(gray2*(y1 - y2)));
                }
                else if (gray1==-1 && gray2==-1){
                    gray1 = 0.299*(image->img->data[i]/255.0)+0.587*(image->img->data[i+1]/255.0)+0.114*(image->img->data[i+2]/255.0);
                }
            }
        }
    }

    void plotRecurrence(Images images, int screenWidth, int screenHeight){
            if(images.current_image == -1)
                return;

            int x1 = screenWidth - screenWidth*0.30, y1 = screenHeight - screenHeight*0.30, x2 = screenWidth, y2 = screenHeight;
            Image* image = images.imgVector[images.current_image];
            int gray = 0;

            std::vector<int>colorR(256, 0);
            std::vector<int>colorG(256, 0);
            std::vector<int>colorB(256, 0);

            for(int i = 0; i < image->img->getHeight()*image->img->getWidth()*3; i += 3){
                if(!image->filter->reverse_rgb){
                    colorR[image->data[i]]+=1;
                    colorG[image->data[i+1]]+=1;
                    colorB[image->data[i+2]]+=1;
                }
                else{
                   colorR[255 - image->data[i]]+=1;
                    colorG[255 - image->data[i+1]]+=1;
                    colorB[255 - image->data[i+2]]+=1;
                }
            }
            int highest_R = *max_element(std::begin(colorR), std::end(colorR));
            int highest_G = *max_element(std::begin(colorG), std::end(colorG));
            int highest_B = *max_element(std::begin(colorB), std::end(colorB));

            for(int i = 0; i < colorR.size(); i ++){
                float yCoord, xCoord;

                if(image->filter->r_channel){
                    yCoord = (colorR[i]*(y2-y1))/highest_R;
                    xCoord = (i*(x2-x1))/colorR.size();
                    CV::color(1, 0, 0);
                    CV::line(x1 + xCoord, y1, x1 + xCoord, y1 + yCoord);
                }
                if(image->filter->g_channel){
                    yCoord = (colorG[i]*(y2-y1))/highest_G;
                    xCoord = (i*(x2-x1))/colorG.size();
                    CV::color(0, 1, 0);
                    CV::line(x1 + xCoord, y1, x1 + xCoord, y1 + yCoord);
                }
                if(image->filter->b_channel){
                    yCoord = (colorB[i]*(y2-y1))/highest_B;
                    xCoord = (i*(x2-x1))/colorB.size();
                    CV::color(0, 0, 1);
                    CV::line(x1 + xCoord, y1, x1 + xCoord, y1 + yCoord);
                }
            }
    }
};
#endif
