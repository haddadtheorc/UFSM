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
    float x = 0.0, y = 0.0;

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
                if(current_image){
                    x = mouseX;
                    y = mouseY;
                }
                showImagePixelPoint(j, i);
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
    void showImagePixelPoint(int j, int i){
        switch (filter->rotation_mod){
            case 0:
                CV::point(x - (img->getWidth()/2)/filter->scale_mod + j, y - (img->getHeight()/2)/filter->scale_mod + i);
            break;
            case 90:
                CV::point(x - (img->getWidth()/2)/filter->scale_mod + i, y + (img->getHeight()/2)/filter->scale_mod - j);
            break;
            case 180:
                CV::point(x + (img->getWidth()/2)/filter->scale_mod - j, y + (img->getHeight()/2)/filter->scale_mod - i);
            break;
            case 270:
                CV::point(x + (img->getWidth()/2)/filter->scale_mod - i, y - (img->getHeight()/2)/filter->scale_mod + j);
            break;
        }
    }

};


class Images{
public:
    std::vector<Image*> imgVector;
    int current_image = 0;

    void initialize(){
        imgVector.push_back(new Image(".\\ghvieira_t1_v2\\resources\\haddad.bmp"));
        imgVector.push_back(new Image(".\\ghvieira_t1_v2\\resources\\normal_1.bmp"));
        imgVector.push_back(new Image(".\\ghvieira_t1_v2\\resources\\img1.bmp"));
    }

    void show(int mouseX, int mouseY){
        imgVector[current_image]->showImage(mouseX, mouseY, true);
    }

    void filterRChannel(){
        imgVector[current_image]->filter->r_channel = !imgVector[current_image]->filter->r_channel;
    }

    void filterGChannel(){
        imgVector[current_image]->filter->g_channel = !imgVector[current_image]->filter->g_channel;
    }

    void filterBChannel(){
        imgVector[current_image]->filter->b_channel = !imgVector[current_image]->filter->b_channel;
    }

    void filterGrayScale(){
        imgVector[current_image]->filter->grayscale = !imgVector[current_image]->filter->grayscale;
    }

    void filterReverseColor(){
        imgVector[current_image]->filter->reverse_rgb = !imgVector[current_image]->filter->reverse_rgb;
    }

    void scaleUp(){
        if(imgVector[current_image]->filter->print_mod >= 1)
            imgVector[current_image]->filter->print_mod --;
    }

    void scaleDown(){
        if(imgVector[current_image]->filter->print_mod <= 1)
            imgVector[current_image]->filter->print_mod ++;
    }

    void rotateRight(){
        imgVector[current_image]->filter->rotation_mod +=90;
        if(imgVector[current_image]->filter->rotation_mod==360)
            imgVector[current_image]->filter->rotation_mod = 0;
    }

    void rotateLeft(){
        imgVector[current_image]->filter->rotation_mod -=90;
        if(imgVector[current_image]->filter->rotation_mod<0)
            imgVector[current_image]->filter->rotation_mod = 270;
    }
};
#endif
