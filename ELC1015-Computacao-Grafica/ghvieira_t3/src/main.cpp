#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include "Bike.h"
#include "Pilot.h"
#import "Background.h"
#import "Fps.h"

int screenWidth = 1000, screenHeight = 800;
Bike bike;
Background background;
Frames *frames;
Pilot pilot;
float fps;
static char fpsText[50];
float speed = 3.75;
bool controlPoints = false;

void initialize()
{
    bike.initialize(screenWidth);
    pilot.initialize(bike.getSeatCenter(), bike.getPedalCoords(), screenWidth);
    background.initialize(screenHeight, screenWidth, bike.getSeatCenter());
    frames = new Frames();
}

void renderFps()
{
    sprintf(fpsText, "FPS:  %.0f", fps);
    CV::color(0, 0, 0);
    CV::text(0 + screenWidth*0.01, screenHeight - screenHeight*0.05, fpsText);
}

void render()
{
    fps = frames->getFrames();
    background.render(1/fps * speed, controlPoints);
    pilot.renderLeg("left");
    bike.render(1/fps * speed, controlPoints);
    pilot.renderUpper(controlPoints, bike.getPedalCoords(), 1/fps * speed);
    pilot.renderLeg("right");
    renderFps();
}

void keyboard(int key)
{
    switch(key){
        case(99):
            controlPoints = !controlPoints;
        break;
        //left arrow
        case (200):
            if(speed <= 0)
                break;
            speed -=0.3125;
        break;
        //right arrow
        case(202):
            if(speed > 17)
                break;
            speed +=0.3125;
        break;
    }
}

void keyboardUp(int key)
{
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
}

int main(void)
{
    initialize();
    CV::init(&screenWidth, &screenHeight, "Trabalho 3 - Transformações geométricas");
    CV::run();
}
