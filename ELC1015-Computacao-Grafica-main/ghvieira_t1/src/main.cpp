#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include "gl_canvas2d.h"
#include "Bmp.h"
#include "Widget.h"

#define CHECKBOX_MAX 5
#define BUTTON_MAX 5


int screenWidth = 750, screenHeight = 750; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().

//variavel global para selecao do que sera exibido na canvas.
int opcao  = 50;

Bmp *img; //armazena a img a ser manipulada
unsigned char *data; //armazena o array com as infos da img para printar
char image_color_mod = 'D'; //modificador da cor do pixel. D=default, X=grayscale, R=red...
int image_point_mod = 0;    //modificador da posicao do pixel.
int image_scale_mod = 0;
int image_print_mod = 0;


Checkbox *checkbox_vector[CHECKBOX_MAX] = {0};
Botao *bt_right, *bt_left, *bt_scale_plus, *bt_scale_minus;

//função para controlar a cor do próximo pixel a ser printado, dependendo do modificador(filtrar apenas uma cor, ou escala de cinza) o CV::color é diferente
void show_image_pixel_color(int cont){
    float y = 0.0;
    if(image_color_mod == 'R'){
        CV::color(data[cont]/255.0, 0.0, 0.0); //usa um cont p ir pegando cada um e divide pelo 255.0 pra ficar entre 0 e 1
    }
    else if(image_color_mod == 'G'){
        CV::color(0.0, data[cont+=1]/255.0, 0.0); //usa um cont p ir pegando cada um e divide pelo 255.0 pra ficar entre 0 e 1
    }
    else if(image_color_mod == 'B'){
        CV::color(0.0, 0.0, data[cont+=2]/255.0); //usa um cont p ir pegando cada um e divide pelo 255.0 pra ficar entre 0 e 1
    }
    else if(image_color_mod == 'X'){
        y = 0.299*data[cont]/255.0 + 0.587*data[cont++]/255.0 + 0.114*data[cont++]/255.0;
        CV::color(y, y, y); //usa um cont p ir pegando cada um e divide pelo 255.0 pra ficar entre 0 e 1
    }
    else if(image_color_mod == 'Z'){
        CV::color(1-data[cont]/255.0, 1-data[cont++]/255.0, 1-data[cont++]/255.0);
    }
    else{
        CV::color(data[cont]/255.0, data[cont++]/255.0, data[cont++]/255.0); //usa um cont p ir pegando cada um e divide pelo 255.0 pra ficar entre 0 e 1
    }
}

//função para controlar a posição do próximo pixel a ser printado, dependendo do modificador(orientação) o CV::point é diferente
void show_image_pixel_point(int j, int i){
    if(image_point_mod==360)
        image_point_mod = 0;
    if(image_point_mod<0){
        image_point_mod = 270;
    }

    switch (image_point_mod){
        case 0:
            CV::point(screenWidth/2 - (img->getWidth()/2)/image_scale_mod + j, screenHeight/2 - (img->getHeight()/2)/image_scale_mod + i); //p printar a img no centro da tela
        break;

        case 90:
            CV::point(screenWidth/2 - (img->getWidth()/2)/image_scale_mod + i, screenHeight/2 + (img->getHeight()/2)/image_scale_mod - j); //p printar a img no centro da tela
        break;

        case 180:
            CV::point(screenWidth/2 + (img->getWidth()/2)/image_scale_mod - j, screenHeight/2 + (img->getHeight()/2)/image_scale_mod - i); //p printar a img no centro da tela
        break;

        case 270:
            CV::point(screenWidth/2 + (img->getWidth()/2)/image_scale_mod - i, screenHeight/2 - (img->getHeight()/2)/image_scale_mod + j); //p printar a img no centro da tela
        break;
    }
}

//função para mostrar uma imagem na tela, cria um laço para percorrer todo o array da imagem e chama as funcoes auxiliares
void show_image(){

    //aqui faz os tratamentos dos modificadores para printar a imagem na escala desejada
    if(image_print_mod == 0){
        image_scale_mod = 1;
    }
    else if(image_print_mod == 1){
        image_scale_mod = 2;
    }
    else if(image_print_mod == 2){
        image_scale_mod = 4;
    }

    int cont = 0;
    for(int i = 0; i < img->getHeight()/image_scale_mod; i++){
        for(int j = 0; j < img->getWidth()/image_scale_mod; j++){
            show_image_pixel_color(cont);
            show_image_pixel_point(j, i);
            cont += 3 * pow(2,image_print_mod);
            }
            if(image_print_mod!=0){
                cont += img->getWidth() * pow(3,image_print_mod);
            }
        }
}

void show_text_filter(){
    CV::color(1, 1, 1);
    CV::text(10, screenHeight-15, "Filtro de Cores e P&B");
}

//função para mostrar os textos na tela, contém funções auxiliares para chamar cada texto a ser mostrado
void show_text(){
    show_text_filter();
}

//função para printar o vetor de checkboxes
void show_widget_checkbox(){
    int i=0;
    for(i=0; i<CHECKBOX_MAX; i++){
        checkbox_vector[i]->Render();
    }
}

//função para printar os botões
void show_widget_button(){
    bt_right->Render();
    bt_left->Render();
    bt_scale_plus->Render();
    bt_scale_minus->Render();
}

//função para mostrar os widgets na tela, contém funções auxiliares para chamar cada widget a ser mostrado
void show_widget(){
    show_widget_checkbox();
    show_widget_button();
}

//função para fazer os desenhos na tela, nesse caso as setinhas para os botões de rotação
void show_draw(){
    //setinhas
    CV::color(0, 0, 0);
    CV::rectFill(screenWidth/2 + img->getWidth()/2 - 50, screenHeight/2 - img->getHeight()/2 - 32.5, screenWidth/2 + img->getWidth()/2 - 35, screenHeight/2 - img->getHeight()/2 - 37.5);
    float a[] = {screenWidth/2 + img->getWidth()/2 - 35, screenWidth/2 + img->getWidth()/2 - 20, screenWidth/2 + img->getWidth()/2 - 35};
    float b[] = {screenHeight/2 - img->getHeight()/2 - 30, screenHeight/2 - img->getHeight()/2 - 35, screenHeight/2 - img->getHeight()/2 - 40};
    CV::polygonFill(a, b, 3);
    CV::rectFill(screenWidth/2 - img->getWidth()/2 + 50, screenHeight/2 - img->getHeight()/2 - 32.5, screenWidth/2 - img->getWidth()/2 + 35, screenHeight/2 - img->getHeight()/2 - 37.5);
    float c[] = {screenWidth/2 - img->getWidth()/2 + 35, screenWidth/2 - img->getWidth()/2 + 20, screenWidth/2 - img->getWidth()/2 + 35};
    float d[] = {screenHeight/2 - img->getHeight()/2 - 30, screenHeight/2 - img->getHeight()/2 - 35, screenHeight/2 - img->getHeight()/2 - 40};
    CV::polygonFill(c, d, 3);

    //+ e -
    CV::rectFill(screenWidth - 50, screenHeight - 32.5, screenWidth - 20, screenHeight - 37.5);
    CV::rectFill(screenHeight - 32.5, screenWidth - 50, screenHeight - 37.5, screenWidth - 20);
    CV::rectFill(screenWidth - 50, screenHeight - 92.5, screenWidth - 20, screenHeight - 97.5);



}

//a render mais enxuta possível, chamando as funções para mostrar a imagem, textos, widgets e os desenhos na tela
void render(){
    CV::clear(0,0,0);
    show_image();
    show_text();
    show_widget();
    show_draw();
}

//desmarca todas as checkboxes
void checkbox_uncheck(){
    int i=0;
    for(i=0; i<CHECKBOX_MAX; i++){
        checkbox_vector[i]->check=false;
    }
    image_color_mod = 'D';
}

//faz a checagem da colisão com as checkboxes, desmarca todas e aplica o modificador caso necessário
void check_widget_collision_checkbox(int x, int y){
    int i=0;
    for(i=0; i<CHECKBOX_MAX; i++){
        if(checkbox_vector[i]->Colidiu(x, y)){
            if(checkbox_vector[i]->check == false){
                checkbox_uncheck();
                checkbox_vector[i]->check=true;
                image_color_mod = checkbox_vector[i]->mod;
            }
            else{
                checkbox_uncheck();
            }
        }
    }
}

//checagem da colisão com os botões, dependendo da colisão altera o modificador de orientação da imagem
void check_widget_collision_button(int x, int y){
    if(bt_right->Colidiu(x, y)){
        image_point_mod +=90;
    }
    if(bt_left->Colidiu(x, y)){
       image_point_mod -=90;
    }
    if(bt_scale_plus->Colidiu(x, y)){
        if(image_print_mod >= 1){
            image_print_mod --;
        }
    }
    if(bt_scale_minus->Colidiu(x, y)){
        if(image_print_mod <= 1){
            image_print_mod ++;
       }
    }

}

//função pra o tratamento da colisão entre os widgets, chama funções auxiliares para cada widget implementado
void check_widget_collision(int x, int y){
    check_widget_collision_checkbox(x, y);
    check_widget_collision_button(x, y);
}

//tratamento do teclado
void keyboard(int key){
//    printf("\nPressinou tecla: %d" , key);
    if( key < 200 ){
        opcao = key;
    }

    switch(key){
        case 27:
            exit(0);

        //tratamento de girar a imagem +- 90: seta p/ esquerda e seta p/ direita
        case 200:
            image_point_mod -=90;
        break;
        case 202:
            image_point_mod +=90;
        break;
        case 201:
            if(image_print_mod >= 1){
                image_print_mod --;
            }
        break;
        case 203:
            if(image_print_mod <= 1){
                image_print_mod ++;
            }
        break;

        //tratamento de filtrar um canal de cor: r(vermelho) g(verde) b(azul) x(cinza) z(invertido) d(default)
        case 100:
            image_color_mod = 'D';
        break;
        case 114:

            if(image_color_mod == 'R'){
                image_color_mod = 'D';
            }
            else{
                checkbox_uncheck();
                image_color_mod = 'R';
            }
        break;
        case 103:
            if(image_color_mod == 'G'){
                image_color_mod = 'D';
            }
            else{
                checkbox_uncheck();
                image_color_mod = 'G';
            }
        break;
        case 98:
            if(image_color_mod == 'B'){
                image_color_mod = 'D';
            }
            else{
                checkbox_uncheck();
                image_color_mod = 'B';
            }
        break;
        case 120:
            if(image_color_mod == 'X'){
                image_color_mod = 'D';
            }
            else{
                checkbox_uncheck();
                image_color_mod = 'X';
            }
        break;
        case 122:
            if(image_color_mod == 'Z'){
                image_color_mod = 'D';
            }
            else{
                checkbox_uncheck();
                image_color_mod = 'Z';
            }
        break;

    }
}

void keyboardUp(int key){
    //printf("\nLiberou tecla: %d" , key);
}

//tratamento do mouse
void mouse(int button, int state, int wheel, int direction, int x, int y){
    mouseX = x;
    mouseY = y;
    //printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);
    if( state == 0 ){
        check_widget_collision(x, y); //checa a colisão com os widgets
    }
}



int main(void){

    img = new Bmp(".\\ghvieira_t1\\resources\\normal_1.bmp");
    data = img->getImage();

    checkbox_vector[0] = new Checkbox(60, screenHeight-40, 15, 15, 1, 0, 0, 'R');
    checkbox_vector[1] = new Checkbox(90, screenHeight-40, 15, 15, 0, 1, 0, 'G');
    checkbox_vector[2] = new Checkbox(120, screenHeight-40, 15, 15, 0, 0, 1, 'B');
    checkbox_vector[3] = new Checkbox(150, screenHeight-40, 15, 15, 1, 1, 1, 'X');
    checkbox_vector[4] = new Checkbox(180, screenHeight-40, 15, 15, 0.5, 0, 0.5, 'Z');
    bt_right = new Botao(screenWidth/2 + img->getWidth()/2 - 60, screenHeight/2 - img->getHeight()/2 - 60, 50, 50, 1, 1, 1);
    bt_left = new Botao(screenWidth/2 - img->getWidth()/2 + 10, screenHeight/2 - img->getHeight()/2 - 60, 50, 50, 1, 1, 1);
    bt_scale_plus = new Botao(screenWidth - 60, screenHeight - 60, 50, 50, 1, 1, 1);
    bt_scale_minus = new Botao(screenWidth - 60, screenHeight - 120, 50, 50, 1, 1, 1);

    CV::init(&screenWidth, &screenHeight, "Trabalho 1 – Visualizador de Imagens e API de widgets");
    CV::run();
}
