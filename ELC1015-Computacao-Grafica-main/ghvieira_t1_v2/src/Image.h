#ifndef IMAGE_H
#define IMAGE_H

#include "gl_canvas2d.h"

#include <vector>
#include "Bmp.h"
#include "Filter.h"

class Image{
public:

    Bmp *img;
    Filter *filter;
    unsigned char *data;

    Image(const char *fileName){
        img = new Bmp(fileName);
        img->convertBGRtoRGB();
        filter = new Filter();
        data = img->getImage();
    }

    // IMPRESSAO DE IMAGEM NA TELA
    void showImage(int mouseX, int mouseY, bool current_image){
        if(filter->print_mod == 0){
            filter->scale_mod = 1;
        }
        else if(filter->print_mod == 1){
            filter->scale_mod = 2;
        }
        else if(filter->print_mod == 2){
            filter->scale_mod = 4;
        }
        int cont = 0;
        for(int i = 0; i < img->getHeight()/filter->scale_mod; i++){
            for(int j = 0; j < img->getWidth()/filter->scale_mod; j++){
                showImagePixelColor(cont);
                showImagePixelPoint(j, i, mouseX, mouseY);
                cont += 3 * pow(2,filter->print_mod);
            }
            if(filter->print_mod!=0){
            cont += img->getWidth() * pow(3,filter->print_mod);
            }
        }
    }

    // COR DO PROXIMO PIXEL A SER PINTADO
    // -> o filter aplica qualquer transformacao necesseria no RBG
    void showImagePixelColor(int cont){
        filter->filter(data[cont]/255.0, data[cont+1]/255.0, data[cont+2]/255.0);
        CV::color(filter->r, filter->g, filter->b);
    }

    // POSICAO DO PROXIMO PIXEL A SER PRINTADO
    // -> o point_mod e scale_mod aplicam transformacao de tamanho ou orientacao
    void showImagePixelPoint(int j, int i, int mouseX, int mouseY){
        switch (filter->rotation_mod){
            case 0:
                CV::point(mouseX - (img->getWidth()/2)/filter->scale_mod + j, mouseY - (img->getHeight()/2)/filter->scale_mod + i);
            break;
            case 90:
                CV::point(mouseX - (img->getWidth()/2)/filter->scale_mod + i, mouseY + (img->getHeight()/2)/filter->scale_mod - j);
            break;
            case 180:
                CV::point(mouseX + (img->getWidth()/2)/filter->scale_mod - j, mouseY + (img->getHeight()/2)/filter->scale_mod - i);
            break;
            case 270:
                CV::point(mouseX + (img->getWidth()/2)/filter->scale_mod - i, mouseY - (img->getHeight()/2)/filter->scale_mod + j);
            break;
        }
    }

};
#endif
