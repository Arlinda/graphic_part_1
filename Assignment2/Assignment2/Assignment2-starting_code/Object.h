#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include<GL\GLU.h>
#include <string>
//#include<GL.h>
//#include<GLU.h>

class Object
{
    bool mIsInitialised;
public:
    Object();
    ~Object();

    bool loadTxtFile(const std::string &filename);
    bool isInitialised() { return mIsInitialised; }
    void draw();

};
