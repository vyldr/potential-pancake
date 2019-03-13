// GameWindow handles interfaces and events necessary to work with OpenGL.

#include <time.h>     // for clock
#include <cstdlib>    // for rand()



#define LINUX
//#define MAC_XCODE
//#define WIN_VISUAL_STUDIO

#ifdef MAC_XCODE
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#endif // MAC_XCODE

#ifdef LINUX
//#include <GL/gl.h>    // Main OpenGL library
#include <GL/glut.h>  // Second OpenGL library
#endif // LINUX

#ifdef WIN_VISUAL_STUDIO
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>           // OpenGL library we copied
#include <ctime>            // for ::Sleep();
#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <thread> // VS 11
#include <chrono> // VS 11
#endif // WIN_VISUAL_STUDIO

#include "include/uiInteract.h"
//#include "include/point.h"
#include "include/definitions.h"


// Sleep until it is time to draw again
void sleep(unsigned long msSleep)
{
// For Windows
#ifdef WIN_VISUAL_STUDIO
  this_thread::sleep_for(chrono::milliseconds(33));

// LINUX, XCODE
#else
  timespec req = {};
  time_t sec = (int)(msSleep / 1000);
  msSleep -= (sec * 1000);

  req.tv_sec = sec;
  req.tv_nsec = msSleep * 1000000L;

  while (nanosleep(&req, &req) == -1)
    ;

#endif // LINUX, XCODE
  return;
}


// Clear the background buffer, draw on it, and send it to the front
void drawCallback()
{
  GameWindow gameWindow;

  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT);

  // Call the client's display function
  gameWindow.callBack(&gameWindow, gameWindow.p);

  // Wait until the right time
  if (!gameWindow.isTimeToDraw())
    sleep((unsigned long)((gameWindow.getNextTick() - clock()) / 1000));

  gameWindow.setNextDrawTime();
  glutSwapBuffers();

  // Count how many frames keys have been pressed for
  if (gameWindow.keyDownPress)
    gameWindow.keyDownPress++;
  if (gameWindow.keyUpPress)
    gameWindow.keyUpPress++;
  if (gameWindow.keyLeftPress)
    gameWindow.keyLeftPress++;
  if (gameWindow.keyRightPress)
    gameWindow.keyRightPress++;
  gameWindow.keySpacePress = false;
  gameWindow.keyPlusPress = false;
  gameWindow.keyMinusPress = false;
}

void resize(int x, int y)
{
  // Set up the perspective view
  glMatrixMode(GL_PROJECTION);  
  glLoadIdentity();
  gluPerspective(40.0, x / y, 0.3, 40.0);
  glMatrixMode(GL_MODELVIEW);
  glViewport(0, 0, x, y);
}


// Handle the arrow keys
void arrowKeyDownCallback(int key, int x, int y)
{
  GameWindow gameWindow;
  switch(key)
  {
    case GLUT_KEY_DOWN:
      gameWindow.keyDownPress = 1;
      break;
    case GLUT_KEY_UP:
      gameWindow.keyUpPress = 1;
      break;
    case GLUT_KEY_RIGHT:
      gameWindow.keyRightPress = 1;
      break;
    case GLUT_KEY_LEFT:
      gameWindow.keyLeftPress = 1;
      break;
  }
}

// Handle releasing the arrow keys
void arrowKeyUpCallback(int key, int x, int y)
{
  GameWindow gameWindow;
  switch(key)
  {
    case GLUT_KEY_DOWN:
      gameWindow.keyDownPress = 0;
      break;
    case GLUT_KEY_UP:
      gameWindow.keyUpPress = 0;
      break;
    case GLUT_KEY_RIGHT:
      gameWindow.keyRightPress = 0;
      break;
    case GLUT_KEY_LEFT:
      gameWindow.keyLeftPress = 0;
      break;
  }
}

// Handle other keys
void keypressCallback(unsigned char key, int x, int y)
{
  GameWindow gameWindow;
  switch (key)
  {
    case ' ':
      gameWindow.keySpacePress = true;
      break;
    case '+':
      gameWindow.keyPlusPress = true;
      break;
    case '-':
      gameWindow.keyMinusPress = true;
      break;
    case 'q':
      exit(EXIT_SUCCESS);
  }
}

// Is it time yet?
bool GameWindow::isTimeToDraw()
{
  return ((unsigned int)clock() >= nextTick);
}

// When should we draw next?
void GameWindow::setNextDrawTime()
{
  nextTick = clock() + static_cast<int> (timePeriod * CLOCKS_PER_SEC);
}

// Set frames per second (this is a very helpful comment)
void GameWindow::setFramesPerSecond(double value)
{
  timePeriod = (1 / value);
}

// Initialize static variables
int          GameWindow::keyDownPress  = 0;
int          GameWindow::keyUpPress    = 0;
int          GameWindow::keyLeftPress  = 0;
int          GameWindow::keyRightPress = 0;
bool         GameWindow::keySpacePress = false;
bool         GameWindow::keyPlusPress  = false;
bool         GameWindow::keyMinusPress = false;
bool         GameWindow::initialized  = false;
double       GameWindow::timePeriod   = 1.0 / FRAMERATE;
unsigned int GameWindow::nextTick     = 0;
void *       GameWindow::p            = NULL;
void (*GameWindow::callBack)(const GameWindow *, void *) = NULL;


// Destroy!
GameWindow::~GameWindow() {}


// Initialize the RNG, the window, and OpenGL stuff
void GameWindow::initialize(int argc, char ** argv, const char * title)
{
  if (initialized)
    return;

// Set up the RNG
  srand((long)(4)); // TODO: Add a way to pass in a seed

  // Set the boundaries for the window
  int xMin = (-(X_SIZE / 2) - 1);
  int xMax = (X_SIZE / 2);
  int yMin = (-(Y_SIZE / 2) - 1);
  int yMax = (Y_SIZE / 2);

  // Create the window
  glutInit(&argc, argv);
  glutInitWindowSize(xMax - xMin, yMax - yMin); // Size of the window

  glutInitWindowPosition( 350, 50); // Set initial position
  glutCreateWindow(title); // Set window title
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // double buffering
  glutIgnoreKeyRepeat(true);

  // Set up the drawing style
  glClearColor(0, 0, 0, 0); // Set black as the background color
  gluOrtho2D(xMin, xMax, yMin, yMax); // 2D environment
  glEnable(GL_DEPTH_TEST);

  // Let OpenGL know how to call our functions
  glutDisplayFunc(   drawCallback         );
  glutReshapeFunc(   resize               );
  glutIdleFunc(      drawCallback         );
  glutKeyboardFunc(  keypressCallback     );
  glutSpecialFunc(   arrowKeyDownCallback );
  glutSpecialUpFunc( arrowKeyUpCallback   );
  

  initialized = true; // Initialization complete

  return;
}

// Start the main graphics loop
void GameWindow::run(void (*callBack)(const GameWindow *, void *), void *p)
{
  // Set the callbacks
  this->p = p;
  this->callBack = callBack;

  // Give control to OpenGL
   glutMainLoop();

   return;
}
