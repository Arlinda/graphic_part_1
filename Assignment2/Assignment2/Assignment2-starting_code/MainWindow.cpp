#include "MainWindow.h"
#include<GL\glew.h>
#include<GL\GL.h>
#include<GL\GLU.h>
#include <SDL.h>
#include <iostream>
#include <string>
#include "Object.h"
#include "drawingFunctions.h"

using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 60;

MainWindow::MainWindow() :
    mIsValid(false),
    mQuitFlag(false),
    mCameraAngleX(0.0f),
    mCameraAngleY(0.0f),
    mCameraZoom(8.0f),
    mObject(nullptr)
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        return;
    }

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 1 ); //Turn on VSync
    //Create Window
    SDL_Surface *screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL | SDL_RESIZABLE );
    if( screen == nullptr )
    {
        cout << "Couldn't set GL mode: " << SDL_GetError() << endl;
        return;
    }
    
    //Set window title
    SDL_WM_SetCaption( "Assignment 2", nullptr );

    //Enable unicode (so we can get unicode keypresses)
    SDL_EnableUNICODE( SDL_TRUE );

    //Initialise the Glew extension library (this has the be done when we have a GL context)
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
       // Problem: glewInit failed, something is seriously wrong.
       cout << "Error: %s\n" << glewGetErrorString(err) << endl;
       return;
    }

    //Initialize OpenGL
    resizeWindow(screen->w, screen->h);  //Sometimes the resize event doesn't seem to get called on window creation. So just do it
    if( initGL() == false ) {
        return;
    }

    initObjects();

    mIsValid = true;
}

MainWindow::~MainWindow()
{
    //free the objects memory
    if(mObject) {
        delete mObject;
        mObject = nullptr;
    }

    //Quit SDL
    SDL_Quit();
}

bool MainWindow::isValid()
{
    return mIsValid;
}

bool MainWindow::initGL()
{
    //Print out some OpenGL details
    std::cout << ::glGetString(GL_VENDOR) << std::endl;
    std::cout << ::glGetString(GL_RENDERER) << std::endl;
    std::cout << ::glGetString(GL_VERSION) << std::endl;

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //Initialize the depth buffer stuff
    glClearDepth(1.0f);                             // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Test To Do

    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective 

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    //Initialize the lights
    GLfloat LightAmbient[]= { 0.4f, 0.4f, 0.4f, 1.0f };  // Ambient Light Values
    GLfloat LightDiffuse[]= { 0.6f, 0.6f, 0.6f, 1.0f };  // Diffuse Light Values
    GLfloat LightPosition[]= { 0.0f, 0.0f, 0.0f, 1.0f }; // Light Position
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);      // Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);      // Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);    // Position The Light
    glEnable(GL_LIGHT1);                                 // Enable Light One


    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}

void MainWindow::initObjects()
{
    mObject = new Object();
    mObject->loadTxtFile("C:/Users/Arlinda/Desktop/HIG/Graphic Programming/Assignments/Assignment_2/Assignment2-starting_code/cube.txt");
}

void MainWindow::exec()
{
    mQuitFlag = false;

    Uint32 prevFrameStartTime = 0;

	//Wait for user exit
	while( mQuitFlag == false )
	{
        //Used to regulate the frame rate
        Uint32 curFrameStartTime = SDL_GetTicks();
        if(prevFrameStartTime == 0) {
            prevFrameStartTime = curFrameStartTime;
        }

        //Event handler
        SDL_Event sdlEvent;

        //While there are events to handle
		while( SDL_PollEvent( &sdlEvent ) )
		{
			if( sdlEvent.type == SDL_QUIT )
			{
                mQuitFlag = true;
            }
            else if( sdlEvent.type == SDL_KEYDOWN )
            {
                //Handle keypress with current mouse position
                int x = 0, y = 0;
                SDL_GetMouseState( &x, &y );
                handleKeys( (unsigned char)sdlEvent.key.keysym.unicode, x, y );
            } else if( sdlEvent.type == SDL_VIDEORESIZE) {
                resizeWindow(sdlEvent.resize.w, sdlEvent.resize.h);
            } else if( sdlEvent.type == SDL_MOUSEMOTION) {
                mouseMove(sdlEvent.motion);
            }
		}

        //Run frame update
        update(double(curFrameStartTime - prevFrameStartTime) / 1000);

        //Render frame
        draw();

        //Regulate the frame rate
        Uint32 frameTime = SDL_GetTicks() - curFrameStartTime;
        if( frameTime < 1000 / FRAMES_PER_SECOND )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - frameTime );
        }
        prevFrameStartTime = curFrameStartTime;
	}
}

void MainWindow::resizeWindow(int width, int height)
{
    glViewport(0, 0, width, height);

    //Setup the perspective projection matrix
    glMatrixMode(GL_PROJECTION);                // Select The Projection Matrix
    glLoadIdentity();                           // Reset The Projection Matrix
    gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);  // Calculate The Aspect Ratio Of The Window
 
}

void MainWindow::handleKeys( unsigned char key, int x, int y )
{
    if( key == ' ' ) { //Spacebar pressed

    } else if(key == 27) { //Escape key
        mQuitFlag = true;
    }

}

void MainWindow::mouseMove(const SDL_MouseMotionEvent &motion)
{
    if(SDL_GetModState() & KMOD_CTRL) { //If control button is pressed down
        if(motion.state & SDL_BUTTON_LMASK) { //if left mouse button is currently pressed down
            mCameraZoom *= (float)exp(0.002 * motion.yrel);
        }
    } else {
        if(motion.state & SDL_BUTTON_LMASK) { //if left mouse button is currently pressed down
            const float scale = 0.2f;
            mCameraAngleX += (float)motion.xrel * scale;
            mCameraAngleY += (float)motion.yrel * scale;
        }
    }
}

//update is called once per frame
//deltaTime is the total time of the last frame
void MainWindow::update(double deltaTime)
{
}

void MainWindow::draw()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //Note: A lot of these functions are depricated in OpenGL 3.0+, but I think they are still useful as a learning steping stone
    glMatrixMode(GL_MODELVIEW);                 // Select The Modelview Matrix
    glLoadIdentity();                           // Reset The Modelview Matrix

    //Position the clight in camera space
    static GLfloat LightPosition[]= { 0.0f, 2.0f, 0.0f, 1.0f }; // Light Position
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);    // Position The Light

    //Set the camera view matrix - Note we need to use the inverse when setting the camera
    //As moving the camera backward by x is like moving the world forward by x, etc
    glTranslatef(0, 0, -mCameraZoom);    //this puts the camera at (0, 0, x)
    glRotatef(mCameraAngleY, 1, 0, 0);
    glRotatef(mCameraAngleX, 0, 1, 0);

    //After finishing the camera movement - this is effectively world space here
    //Any more transformations will be into object space
    //However, we can use push and pop to return to this matrix state

    drawAxis();

    glPushMatrix();
    if(mObject) {
        mObject->draw();
    }
    glPopMatrix();

    //Update screen
    SDL_GL_SwapBuffers();
}
