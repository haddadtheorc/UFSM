#ifndef FILTER_H
#define FILTER_H
#include "gl_canvas2d.h"

//HEADER PARA GERENCIAMENTO DOS FILTROS

//Cada imagem possui filtros pr�prios, ent�o uma classe foi criada para englobar qualquer modifica��o que seja feita em uma imagem
//A fun��o filter() trata de aplicar na imagem a ser mostrada quaisquer filtros que sejam aplicados a ela
//A fun��o reset() apenas reseta os filtros de uma imagem

class Filter{
    public:
        float r, g, b;
        int rotation_mod, scale_mod, print_mod;
        bool r_channel = true, g_channel = true, b_channel = true, grayscale = true, reverse_rgb = true;

        filter(){
            r = 0.0;
            g = 0.0;
            b = 0.0;
            rotation_mod = 0;
            scale_mod = 0;
            print_mod = 0;
        }

        void filter(float _r, float _g, float _b){
            r = _r;
            g = _g;
            b = _b;

            //checking for possible color filters on the image (filtering specific color channels, reverse colors or gayscale)
            if(!this->r_channel){
                r = 0.0;
            }
            if(!this->g_channel){
                g = 0.0;
            }
            if(!this->b_channel){
                b = 0.0;
            }
            if(!this->reverse_rgb) {
                r = 1.0 - r;
                g = 1.0 - g;
                b = 1.0 - b;
            }
            if(!grayscale){
                float gray = r*0.299 + g*0.587 + b*0.114;
                r = g = b = gray;
            }
        }

        void reset(){
            this->r_channel = true;
            this->g_channel = true;
            this->b_channel = true;
            this->grayscale = true;
            this->reverse_rgb = true;
        }
};
#endif
