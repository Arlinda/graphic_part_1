#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
//#include <SDL.h>
//#include <SDL_opengl.h>
#include <vector>
//#include "Drawable.h"
#include "Object.h"

//pre declarations
struct SDL_MouseMotionEvent;

class MainWindow
{
    bool mIsValid;
    bool mQuitFlag;
    float mCameraAngleX;
    float mCameraAngleY;
    float mCameraZoom;
    Object *mObject;
public:
    MainWindow();
    ~MainWindow();

    bool isValid();
    void exec();
protected:
    bool initGL();
    void initObjects();
    void handleKeys( unsigned char key, int x, int y );
    void update(double deltaTime);
    void draw();
    void resizeWindow(int width, int height);
    void mouseMove(const SDL_MouseMotionEvent &motion);
};
