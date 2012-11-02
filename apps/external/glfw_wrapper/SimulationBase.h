#include <iostream>
#include <GL/glfw.h>

class SimulationBase {
public:
  SimulationBase();
  virtual void setup();
  virtual void update();
  virtual void draw();
  virtual void onMouseDown(int x, int y, int button);
  virtual void onMouseUp(int x, int y, int button);
  virtual void onMouseDrag(int x, int y, int dx, int dy, int button);
  virtual void onMouseMove(int x, int y);
  virtual void onKeyDown(char key);
  virtual void onKeyUp(char key);
  virtual void onWindowResize(int w, int h);
  virtual void onWindowClose();
  void setWindowTitle(const char* title);
public:
  int mouse_x;
  int mouse_y;
  int prev_mouse_x;
  int prev_mouse_y;
  int pressed_mouse_button;
  bool is_mouse_down;
};