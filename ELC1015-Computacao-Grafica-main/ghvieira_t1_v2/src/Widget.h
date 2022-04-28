#ifndef WIDGET_H
#define WIDGET_H

#include "gl_canvas2d.h"

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

    void Render(){
        if(check){
            CV::color(1, 1, 1);
            CV::line(x, y, x+largura, y+altura);
            CV::line(x, y+altura, x+largura, y);
        }
        CV::color(r, g, b);
        CV::rect(x, y, x + largura, y + altura);
    }

    bool Colidiu(int mx, int my){
        if( mx >= x && mx <= (x + largura) && my >= y && my <= (y + altura) ){
            return true;
        }
        else{
            return false;
        }
    }
};

class Botao{
  float altura, largura, x, y, r, g, b;
  int mod;

public:
  Botao(float _x, float _y, float _larg, float _alt, int _r, int _g, int _b){
     altura  = _alt;
     largura = _larg;
     x = _x;
     y = _y;
     r = _r;
     g = _g;
     b = _b;

  }

  void Render()
  {
      CV::color(r, g, b);
      CV::rectFill(x, y, x + largura, y + altura);
  }

  //recebe as coordenadas do mouse para tratar clique ou detectar quando o mouse esta em cima do botao
  bool Colidiu(int mx, int my)
  {
      if( mx >= x && mx <= (x + largura) && my >= y && my <= (y + altura) )
      {
          return true;
      }
      return false;
  }

};

#endif
