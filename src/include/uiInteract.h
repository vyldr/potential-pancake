// Class to open a window, enter the OpenGL main loop, and recieve input

#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

// Class to handle a window
class GameWindow
{
public:
  GameWindow()
  {
    initialize(0, 0x0000, "Window");
  }

  GameWindow(int argc, char ** argv, const char * windowTitle)
  {
    initialize(argc, argv, windowTitle);
  }

  // Destroy!
  ~GameWindow();

  // Start the game
  void run(void (*callBack)(const GameWindow *, void *), void *p);

  // Get key events
  int  keyDown()  const { return keyDownPress;  }
  int  keyUp()    const { return keyUpPress;    }
  int  keyLeft()  const { return keyLeftPress;  }
  int  keyRight() const { return keyRightPress; }
  bool keySpace() const { return keySpacePress; }
  bool keyPlus()  const { return keyPlusPress;  }
  bool keyMinus() const { return keyMinusPress; }

  static void *p; // for the callback
  static void (*callBack)(const GameWindow *, void *);

private:
  void initialize(int argc, char ** argv, const char * windowTitle);
  bool isTimeToDraw();
  void setNextDrawTime();
  unsigned int getNextTick() { return nextTick; }
  void setFramesPerSecond(double value);

  // Indicate whether a key has been pressed or not.
  friend void arrowKeyDownCallback( int           key, int x, int y);
  friend void arrowKeyUpCallback(   int           key, int x, int y);
  friend void keypressCallback(unsigned char key, int x, int y);
  friend void drawCallback();

  // Get the frame rate
  double frameRate() const { return timePeriod;   }

  static bool         initialized;  // So the constructor only runs once
  static double       timePeriod;   // Time between frame draws
  static unsigned int nextTick;     // Time of the next draw

  // Who has been pressed, and for how long?
  static int  keyDownPress;
  static int  keyUpPress;
  static int  keyLeftPress;
  static int  keyRightPress;
  static bool keySpacePress;
  static bool keyPlusPress;
  static bool keyMinusPress;
};

// Run the game
void run();

#endif // GAME_WINDOW_H
