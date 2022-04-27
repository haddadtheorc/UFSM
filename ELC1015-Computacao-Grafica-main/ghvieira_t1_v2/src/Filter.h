#ifndef FILTER_H
#define FILTER_H

#include "gl_canvas2d.h"

class Filter{
public:
    float r, g, b;
    bool r_channel = true, g_channel = true, b_channel = true, grayscale = false, reverse_rgb = false;

    Filter(){
        r = 0.0;
        g = 0.0;
        b = 0.0;
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
        if(this->reverse_rgb) {
            r = 1.0 - r;
            g = 1.0 - g;
            b = 1.0 - b;
        }
        if(grayscale){
            float gray = r*0.299 + g*0.587 + b*0.114;
            r = g = b = gray;
        }
    }
};


#endif