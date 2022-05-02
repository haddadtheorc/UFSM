#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include "gl_canvas2d.h"

//HEADER PARA GERENCIAMENTO DO HISTOGRAMA

//Seu método plot() trata da renderização do histograma da imagem na tela
//A imagem a ter seu histograma renderizado, bem como o tamanho da tela são os argumentos necessários para a função

class Histogram{
    public:


    void plot(Images images, int screenWidth, int screenHeight){
        //EIXOS
        int x1 = screenWidth - screenWidth*0.30, y1 = screenHeight - screenHeight*0.30, x2 = screenWidth, y2 = screenHeight;
        CV::color(1, 1, 1);
        CV::line(x1,y1,x1,y2);
        CV::line(x1,y1,x2,y1);

        if(images.current_image == -1)
            return;

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
};
#endif
