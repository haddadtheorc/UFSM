#ifndef _FRAMES_H___
#define _FRAMES_H___
#include <stdio.h>
#include <time.h>

#define UPDATE_RATE 30   //milisegundos


class Frames{
    clock_t t1, t2;
    long    cont_frames;
    float   fps, fps_old;
public:
    Frames(){
        t1 = clock();
        cont_frames = 0;
        fps_old = 20; //valor inicial
   }

    float getFrames(){

        double tempo;
        t2 = clock();
        tempo  = (double)(t2 - t1);
        cont_frames++;

        if( tempo > UPDATE_RATE ){
            t1 = t2;
            fps = cont_frames / (tempo/CLOCKS_PER_SEC);
            cont_frames = 0;
            fps_old = fps;
            return fps;
      }
      return fps_old;
   }
};

#endif
