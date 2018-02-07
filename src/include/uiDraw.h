#ifndef UI_DRAW_H
#define UI_DRAW_H


// Drawing functions for various game items
void drawTile(int xCoord, int yCoord, int xOffset, int yOffset, float scale, int type, int base);
void drawCharacter(float xCoord, float yCoord, int xOffset, int yOffset, float scale);
void drawItem(float xCoord, float yCoord, int type, int xOffset, int yOffset, float scale);
void drawCenterBox(float scale);

// General drawing functions

// Draw text on the screen from specific coordinates
void drawText(int x, int y, const char * text);

// Draw a rectangle based on two corners and the color
void drawRectangle(int xBegin, int yBegin, int xEnd, int yEnd, float red, float green, float blue);
void drawRectangleOutline(int xBegin, int yBegin, int xEnd, int yEnd, float red, float green, float blue);


// Generate a random number within a range
int    random(int    min, int    max);
double random(double min, double max);

#endif // UI_DRAW_H
