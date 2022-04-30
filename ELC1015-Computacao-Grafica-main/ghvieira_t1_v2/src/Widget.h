#ifndef WIDGET_H
#define WIDGET_H
#include <vector>
#include "gl_canvas2d.h"
#include "Image.h"

class Checkbox{
public:
    float altura, largura, x, y, r, g, b;
    bool check = false;
    char id;

    Checkbox(float _x, float _y, float _larg, float _alt, float _r, float _g, float _b, char _id){
        altura  = _alt;
        largura = _larg;
        x = _x;
        y = _y;
        r = _r;
        g = _g;
        b = _b;
        id = _id;
    }

    void render(){
        if(check){
            CV::color(1, 1, 1);
            CV::line(x, y, x+largura, y+altura);
            CV::line(x, y+altura, x+largura, y);
        }
        CV::color(r, g, b);
        CV::rect(x, y, x + largura, y + altura);
    }

    bool collide(int mx, int my){
        if( mx >= x && mx <= (x + largura) && my >= y && my <= (y + altura) )
            return true;
        return false;
    }
};

class Button{
    public:
        float altura, largura, x, y, r, g, b;
        int mod;
        char id;

        Button(float _x, float _y, float _larg, float _alt, int _r, int _g, int _b, char _id){
         altura  = _alt;
         largura = _larg;
         x = _x;
         y = _y;
         r = _r;
         g = _g;
         b = _b;
         id = _id;

      }

        void render(){
            CV::color(r, g, b);
            CV::rectFill(x, y, x + largura, y + altura);
            CV::color(0, 0, 0);
            CV::text(x, y+altura/2, "lel");
        }

        bool collide(int mx, int my){
            if( mx >= x && mx <= (x + largura) && my >= y && my <= (y + altura))
                return true;
            return false;
        }
};

class Widget{
    public:
    std::vector<Checkbox*> checkboxVector;
    std::vector<Button*> buttonVector;

    void initialize(int screenWidth, int screenHeight){
            //CHECKBOXES (R, G, B, X, Z)
            checkboxVector.push_back(new Checkbox(60, screenHeight-50, screenWidth*0.02, screenHeight*0.02, 1, 0, 0, 'R'));
            checkboxVector.push_back(new Checkbox(90, screenHeight-50, screenWidth*0.02, screenHeight*0.02, 0, 1, 0, 'G'));
            checkboxVector.push_back(new Checkbox(120, screenHeight-50, screenWidth*0.02, screenHeight*0.02, 0, 0, 1, 'B'));
            checkboxVector.push_back(new Checkbox(150, screenHeight-50, screenWidth*0.02, screenHeight*0.02, 0.5, 0.5, 0.5, 'X'));
            checkboxVector.push_back(new Checkbox(180, screenHeight-50, screenWidth*0.02, screenHeight*0.02, 1, 0, 1, 'Z'));
            //BUTTONS (LEFT, RIGHT)
            buttonVector.push_back(new Button(100, 100, screenHeight*0.07 , screenWidth*0.07, 1, 1, 1, 'A'));
            buttonVector.push_back(new Button(screenWidth-100-screenWidth*0.07, 100, screenHeight*0.07 , screenWidth*0.07, 1, 1, 1, 'D'));
        }

    char collide(int mx, int my){
        for(int i = 0; i < buttonVector.size(); i ++){
            if(buttonVector[i]->collide(mx, my)){
                return (buttonVector[i]->id);
            }
        }
        for(int i = 0; i < checkboxVector.size(); i ++){
            if(checkboxVector[i]->collide(mx, my)){
                return (checkboxVector[i]->id);
            }
        }
    }

    void show(Images images){
            uncheckCheckboxes();
            showButtons();
            if(images.current_image > -1)
                checkCheckboxes(images.imgVector[images.current_image]);
            showCheckboxes();
        }

    void showButtons(){
            for(int i = 0; i < buttonVector.size(); i++){
                buttonVector[i]->render();
            }
        }

    void showCheckboxes(){
            for(int i = 0; i < checkboxVector.size(); i++){
                checkboxVector[i]->render();
            }
    }

    void uncheckCheckboxes(){
        for(int i = 0; i < checkboxVector.size(); i++){
            checkboxVector[i]->check = false;
        }
    }

    void checkCheckboxes(Image* image){
        if(!image->filter->r_channel)
            checkCheckbox('R');
        if(!image->filter->g_channel)
            checkCheckbox('G');
        if(!image->filter->b_channel)
            checkCheckbox('B');
        if(!image->filter->grayscale)
            checkCheckbox('X');
        if(!image->filter->reverse_rgb)
            checkCheckbox('Z');
    }

    void checkCheckbox(char id){
        for(int i = 0; i < checkboxVector.size(); i++){
            if(checkboxVector[i]->id == id)
                checkboxVector[i]->check = true;
        }
    }

};
#endif
