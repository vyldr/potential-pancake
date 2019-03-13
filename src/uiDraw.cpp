// Functions for drawing on the screen.  Also random functions because of reasons
// TODO: Maybe find a better place for the random functions


#define LINUX
//#define MAC_XCODE
//#define WIN_VISUAL_STUDIO

#ifdef MAC_XCODE
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#endif // MAC_XCODE

#ifdef LINUX
//#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#endif // LINUX

#ifdef WIN_VISUAL_STUDIO
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>         // OpenGL library we copied
#define _USE_MATH_DEFINES
#include <math.h>
#endif // WIN_VISUAL_STUDIO

#include <iostream>
#include "include/definitions.h"
#include "include/uiDraw.h"


// RGB values for different items
float colors[3][10] = {
// Type 0  Type 1  Type 2  Type 3  Type 4  Type 5  Type 6  Type 7  Base 1
  {0.0800, 0.6980, 0.6000, 0.5020, 0.4000, 0.2384, 0.5000, 0.7098, 0.0000, 0.2187},  // Red
  {0.0800, 0.4706, 0.4000, 0.3294, 0.2588, 0.1506, 0.5000, 0.8980, 0.5000, 0.8672},  // Green
  {0.0800, 0.2392, 0.2000, 0.1686, 0.1294, 0.0800, 0.5000, 0.2000, 0.8000, 0.3047}}; // Blue

// 2D drawing

// Draw a tile on the screen
void drawTile(int xCoord, int yCoord, int xOffset, int yOffset, float scale, int type, int base)
{
  drawRectangle(
    // Top left corner of tile
    (xCoord * TILE_SIZE - xOffset) * scale,
    (yCoord * TILE_SIZE - yOffset) * scale,
    // Bottom right corner of tile
    ((xCoord + 1) * TILE_SIZE - xOffset) * scale - 1,
    ((yCoord + 1) * TILE_SIZE - yOffset) * scale - 1,
  //Red              Green            Blue
    colors[0][type], colors[1][type], colors[2][type]);

    // Draw a blue square on base tiles
    if (base == 1)
      drawRectangle(
        // Top left corner of tile
        (xCoord * TILE_SIZE - xOffset + (TILE_SIZE / 4)) * scale,
        (yCoord * TILE_SIZE - yOffset + (TILE_SIZE / 4)) * scale,
        // Bottom right corner of tile
        ((xCoord + 1) * TILE_SIZE - xOffset - (TILE_SIZE / 4)) * scale - 1,
        ((yCoord + 1) * TILE_SIZE - yOffset - (TILE_SIZE / 4)) * scale - 1,
      //Red           Green         Blue
        colors[0][8], colors[1][8], colors[2][8]);

}

void drawCharacter(float xCoord, float yCoord, int xOffset, int yOffset, float scale)
{
  drawRectangle(
    // Top left corner of tile
    (xCoord * TILE_SIZE - xOffset - CHARACTER_SIZE / 2) * scale,
    (yCoord * TILE_SIZE - yOffset - CHARACTER_SIZE / 2) * scale,
    // Bottom right corner of tile
    (xCoord * TILE_SIZE - xOffset + CHARACTER_SIZE / 2) * scale,
    (yCoord * TILE_SIZE - yOffset + CHARACTER_SIZE / 2) * scale,
  //Red              Green            Blue
    colors[0][8], colors[1][8], colors[2][8]);
    //std::cout << xCoord << '\n';
}

// Draw the Items
void drawItem(float xCoord, float yCoord, int type, int xOffset, int yOffset, float scale)
{
  drawRectangle(
    // Top left corner of tile
    (xCoord * TILE_SIZE - xOffset - ITEM_SIZE / 2) * scale,
    (yCoord * TILE_SIZE - yOffset - ITEM_SIZE / 2) * scale,
    // Bottom right corner of tile
    (xCoord * TILE_SIZE - xOffset + ITEM_SIZE / 2) * scale,
    (yCoord * TILE_SIZE - yOffset + ITEM_SIZE / 2) * scale,
  //Red              Green            Blue
    colors[0][9], colors[1][9], colors[2][9]);
}

// Draw the yellow box in the center of the screen
void drawCenterBox(float scale)
{
  drawRectangleOutline(
    ( TILE_SIZE / 2 * scale),
    ( TILE_SIZE / 2 * scale - 1),
    (-TILE_SIZE / 2 * scale),
    (-TILE_SIZE / 2 * scale - 1),
    1, 1, 0);
}

// 3D drawing

void setup3DFrame(const float camera[6])
{
  // clear the drawing buffer.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  // Move the camera
  glRotatef(camera[4] * 180 / M_PI, 0, 1, 0);
  glTranslatef(camera[0],camera[1],camera[2]);
}

void drawTile3D(int xCoord, int yCoord, int type, int base)
{
  if (type == 0)
  {
    // Draw Floor
    glBegin(GL_TRIANGLES);
      glColor3f(colors[0][type], colors[1][type], colors[2][type]);
      glVertex3f( 1.0f + xCoord, 0.0f, 0.0f + yCoord);
      glVertex3f( 1.0f + xCoord, 0.0f, 1.0f + yCoord);
      glVertex3f( 0.0f + xCoord, 0.0f, 1.0f + yCoord);
    glEnd();
    glBegin(GL_TRIANGLES);
      glColor3f(colors[0][type], colors[1][type], colors[2][type]);
      glVertex3f( 0.0f + xCoord, 0.0f, 1.0f + yCoord);
      glVertex3f( 0.0f + xCoord, 0.0f, 0.0f + yCoord);
      glVertex3f( 1.0f + xCoord, 0.0f, 0.0f + yCoord);
    glEnd();

    // Draw Ceiling
    glBegin(GL_TRIANGLES);
      glColor3f(colors[0][type], colors[1][type], colors[2][type]);
      glVertex3f( 1.0f + xCoord, 1.0f, 0.0f + yCoord);
      glVertex3f( 1.0f + xCoord, 1.0f, 1.0f + yCoord);
      glVertex3f( 0.0f + xCoord, 1.0f, 1.0f + yCoord);
    glEnd();
    glBegin(GL_TRIANGLES);
      glColor3f(colors[0][type], colors[1][type], colors[2][type]);
      glVertex3f( 0.0f + xCoord, 1.0f, 1.0f + yCoord);
      glVertex3f( 0.0f + xCoord, 1.0f, 0.0f + yCoord);
      glVertex3f( 1.0f + xCoord, 1.0f, 0.0f + yCoord);
    glEnd();
    // glFlush();
  }
  else
  {
    // Draw Walls
    glBegin(GL_TRIANGLES);
      glColor3f(colors[0][type], colors[1][type], colors[2][type]);
      glVertex3f( 0.0f + xCoord, 0.0f, 0.0f + yCoord);
      glVertex3f( 0.0f + xCoord, 0.0f, 1.0f + yCoord);
      glVertex3f( 0.0f + xCoord, 1.0f, 1.0f + yCoord);
    glEnd();
    glBegin(GL_TRIANGLES);
      glColor3f(colors[0][type], colors[1][type], colors[2][type]);
      glVertex3f( 0.0f + xCoord, 1.0f, 1.0f + yCoord);
      glVertex3f( 0.0f + xCoord, 1.0f, 0.0f + yCoord);
      glVertex3f( 0.0f + xCoord, 0.0f, 0.0f + yCoord);
    glEnd();
    glBegin(GL_TRIANGLES);
      glColor3f(colors[0][type], colors[1][type], colors[2][type]);
      glVertex3f( 0.0f + xCoord, 0.0f, 1.0f + yCoord);
      glVertex3f( 1.0f + xCoord, 0.0f, 1.0f + yCoord);
      glVertex3f( 1.0f + xCoord, 1.0f, 1.0f + yCoord);
    glEnd();
    glBegin(GL_TRIANGLES);
      glColor3f(colors[0][type], colors[1][type], colors[2][type]);
      glVertex3f( 1.0f + xCoord, 1.0f, 1.0f + yCoord);
      glVertex3f( 0.0f + xCoord, 1.0f, 1.0f + yCoord);
      glVertex3f( 0.0f + xCoord, 0.0f, 1.0f + yCoord);
    glEnd();
    glBegin(GL_TRIANGLES);
      glColor3f(colors[0][type], colors[1][type], colors[2][type]);
      glVertex3f( 1.0f + xCoord, 0.0f, 1.0f + yCoord);
      glVertex3f( 1.0f + xCoord, 0.0f, 0.0f + yCoord);
      glVertex3f( 1.0f + xCoord, 1.0f, 0.0f + yCoord);
    glEnd();
    glBegin(GL_TRIANGLES);
      glColor3f(colors[0][type], colors[1][type], colors[2][type]);
      glVertex3f( 1.0f + xCoord, 1.0f, 0.0f + yCoord);
      glVertex3f( 1.0f + xCoord, 1.0f, 1.0f + yCoord);
      glVertex3f( 1.0f + xCoord, 0.0f, 1.0f + yCoord);
    glEnd();
    glBegin(GL_TRIANGLES);
      glColor3f(colors[0][type], colors[1][type], colors[2][type]);
      glVertex3f( 1.0f + xCoord, 0.0f, 0.0f + yCoord);
      glVertex3f( 0.0f + xCoord, 0.0f, 0.0f + yCoord);
      glVertex3f( 0.0f + xCoord, 1.0f, 0.0f + yCoord);
    glEnd();
    glBegin(GL_TRIANGLES);
      glColor3f(colors[0][type], colors[1][type], colors[2][type]);
      glVertex3f( 0.0f + xCoord, 1.0f, 0.0f + yCoord);
      glVertex3f( 1.0f + xCoord, 1.0f, 0.0f + yCoord);
      glVertex3f( 1.0f + xCoord, 0.0f, 0.0f + yCoord);
    glEnd();

  }
  
}

// Draw text on the screen from specific coordinates
void drawText(int x, int y, const char * text)
{
  // Set color to white TODO: Add color input options
  glColor3f(1.0, 1.0, 1.0);

  // Top-left corner of the text
  glRasterPos2f(x, y);

  // Draw each character
  for (const char *p = text; *p; p++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
}


// Draw a rectangle based on two corners and the color
void drawRectangle(int xBegin, int yBegin, int xEnd, int yEnd, float red, float green, float blue)
{
  glColor3f(red, green, blue); // Set color
  glRectf(xBegin, yBegin, xEnd, yEnd); // Draw the thing!
}

void drawRectangleOutline(int xBegin, int yBegin, int xEnd, int yEnd, float red, float green, float blue)
{
  glColor3f(red, green, blue); // Set color

  // Draw the thing!
  glBegin(GL_LINE_STRIP);
  glVertex2f(xBegin, yBegin);
  glVertex2f(xEnd - 1, yBegin); // Subtract 1 to fill in the corner
  glVertex2f(xEnd, yEnd);
  glVertex2f(xBegin, yEnd);
  glVertex2f(xBegin, yBegin);
  glEnd();
}


// Generate a random number within a specified range
int random(int min, int max)
{
  if (min == max)
    return min;
  return ((rand() % (max - min)) + min);
}

double random(double min, double max)
{
  if (min == max)
    return min;
  return (min + ((double)rand() / (double)RAND_MAX * (max - min)));
}
