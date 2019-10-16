/*
  Zachary Klein

  Currently this is just a simple mandelbrot viewer.
  Inputs:
  -w [width]:       window width
  -h [height]:      window height
  -i [iterations]:  max iteration count

  Controls:
  Q/q/Esc:          exit the program
*/
#include <iostream>
#include <cstring>
#include <complex>

#ifdef __APPLE__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

// declare width and height
int width = 0;
int height = 0;

//max iterations
int iter_max = 50;

//sets value in pixel array based on coordinates.
void setVal (int x, int y, int startPos, float* pixels) {
  complex<float> point((float)x / width - 1.5, (float)y / height - 0.5);
  complex<float> z(0, 0);
  unsigned int iter = 0;
  while(abs(z) < 2 && iter < iter_max) {
    z = z * z + point;
    iter++;
  }
  float val = 0;
  if(iter < iter_max) val = (iter + 0.0) / iter_max;
  pixels[startPos] = val;
}

// render the fractal
void render()
{
  // set clear to opaque black
  glClearColor(0, 0, 0, 1);
  // clear window
  glClear(GL_COLOR_BUFFER_BIT);

  float* pixels = new float[width * height * 3];

  for(int i = 0; i < width * height * 3; i += 3)
    setVal(i / 3 % width, i / 3 / width, i, pixels);

  glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

  // swap buffers
  glutSwapBuffers();
  delete pixels;
}

/*
   Keyboard callback
*/
void handleKey(unsigned char key, int x, int y)
{

  switch (key)
  {
  case 'q': // q - quit
  case 'Q':
  case 27: // esc - quit
    exit(0);

  default: // not a valid key -- just ignore it
    return;
  }
}

/*
   So things don't just break on resize
*/
void handleReshape(int w, int h)
{
  // set the viewport to be the entire window
  glViewport(0, 0, w, h);

  // define the drawing coordinate system on the viewport
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  width = w;
  height = h;
}

int main(int argc, char *argv[])
{
  // read arguments
  for (int i = 1; i < argc; i++)
  {
    // check for width flag
    if (strcmp(argv[i], "-w") == 0)
    {
      ++i;

      //check validity of input
      if (i == argc || !sscanf(argv[i], "%i", &width) || width <= 0)
      {
        cout << "Must provide valid width for -w flag" << endl;
        exit(1);
      }
    }

    // check for height flag
    else if (strcmp(argv[i], "-h") == 0)
    {
      ++i;

      // check validity of input
      if (i == argc || !sscanf(argv[i], "%i", &height) || height <= 0)
      {
        cout << "Must provide valid height for -h flag" << endl;
        exit(1);
      }
    }

    // check for iteration flag
    if (strcmp(argv[i], "-i") == 0)
    {
      ++i;

      //check validity of input
      if (i == argc || !sscanf(argv[i], "%i", &iter_max) || iter_max <= 0)
      {
        cout << "Must provide positive number for iteration flag" << endl;
        exit(1);
      }
    }
  }

  // If no dimensions were specified, initialize at 600
  if (height == 0)
    height = 600;
  if (width == 0)
    width = 600;

  // start up the glut utilities
  glutInit(&argc, argv);

  // create the window
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(width, height);
  glutCreateWindow("Mandelbrot");

  //callback routines
  glutDisplayFunc(render);
  glutKeyboardFunc(handleKey);
  glutReshapeFunc(handleReshape);
  glutReshapeWindow(width, height);
  glutPostRedisplay();

  glutMainLoop();
  return 0;
}
