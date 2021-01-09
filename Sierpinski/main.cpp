#include <GL/glut.h>


typedef GLfloat point2[2];                                      // define 2d point
typedef GLfloat point3[3];                                      // define 3d point

point2 v2f[] = { {-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15} };    // 2d triagnle end points
point3 v3f[] = { {0.0, 0.0, 1.0},                               // 3d tetrahedron end points
                 {0.0, 0.942809, -0.333333},
                 {-0.816497, -0.471405, -0.333333},
                 {0.816497, -0.471405, -0.333333} };
GLfloat colors3f[4][3] = { {1.0, 0.0, 0.0},                     // color indexes
                           {0.0, 1.0, 0.0},
                           {0.0, 0.0, 1.0},
                           {0.0, 0.0, 0.0} };

int n = 3;                                                      // recursive depth
int h = 600;                                                    // window height
int w = 2 * h;                                                  // window width


void triangle2(point2 a, point2 b, point2 c);                   // draw 2d triangle
void divide_triangle2(point2 a, point2 b, point2 c, int m);     // find 2d middle points recursively
void triangle3(point3 a, point3 b, point3 c);                   // draw 3d triangle
void divide_triangle3(point3 a, point3 b, point3 c, int m);     // find 3d middle points recursively
void Sierpinski2(int m);                                        // draw 2d Sierpinski triangle
void Sierpinski3(int m);                                        // draw 3d Sierpinski triangle
void mydisplay();                                               // display callback funciton
void init();                                                    // initialize window environment


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);                                      // initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);   // set window configs
    glutInitWindowSize(w, h);                                   // set window size
    glutCreateWindow("Sierpinski");                             // name window
    glutDisplayFunc(mydisplay);                                 // set display callback

    init();                                                     // initialize window
    glutMainLoop();                                             // start main event loop

    return 1;
}

void init()
{
    glEnable(GL_DEPTH_TEST);                                    // enable z-buffer algorithm for hidden-surface removal
    glClearColor(1.0, 1.0, 1.0, 1.0);                           // set background color to white
}

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // clear color and depth buffer with previously set values

    int w, h;                                                   // get current window width and height
    w = glutGet(GLUT_WINDOW_WIDTH);
    h = glutGet(GLUT_WINDOW_HEIGHT);

    glViewport(0, 0, w / 2, h);                                 // set view port to left-half window
    glMatrixMode(GL_PROJECTION);                                // set projection range 1
    glLoadIdentity();                                           // set projection range 2
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);                           // set projection range 3
    glMatrixMode(GL_MODELVIEW);                                 // set projection range 4
    glBegin(GL_TRIANGLES);                                      // begin draw triangle
    Sierpinski2(n);                                             // 2d Sierpinski triangle
    glEnd();                                                    // end draw

    glViewport(w / 2, 0, w / 2, h);                             // set view port to right-half window
    glMatrixMode(GL_PROJECTION);                                // set projection range 1, 2, 3, 4
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_TRIANGLES);                                      // begin draw triangle
    Sierpinski3(n);                                             // 3d Sierpinski triangle
    glEnd();                                                    // end draw

    glFlush();                                                  // empty buffer and refresh window
}

void triangle2(point2 a, point2 b, point2 c)
{
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
}

void divide_triangle2(point2 a, point2 b, point2 c, int m)
{
    point2 v0, v1, v2;
    if (m > 0) {                                                // expected depth not achieved
        for (int j = 0; j < 2; j++)                             // update three end points of the triangle
        {
            v0[j] = (a[j] + b[j]) / 2;
            v1[j] = (a[j] + c[j]) / 2;
            v2[j] = (b[j] + c[j]) / 2;
        }
        divide_triangle2(a, v0, v1, m - 1);                     // divide three new triangles respectively
        divide_triangle2(b, v0, v2, m - 1);
        divide_triangle2(c, v1, v2, m - 1);
    }
    else {                                                      // expected depth achieved, draw triangle
        triangle2(a, b, c);
    }
}

void triangle3(point3 a, point3 b, point3 c)
{
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
}

void divide_triangle3(point3 a, point3 b, point3 c, int m)
{
    point3 v0, v1, v2;
    if (m > 0) {                                                // expected depth not achieved
        for (int j = 0; j < 3; j++)                             // update three end points of the triangle
        {
            v0[j] = (a[j] + b[j]) / 2;
            v1[j] = (a[j] + c[j]) / 2;
            v2[j] = (b[j] + c[j]) / 2;
        }
        divide_triangle3(a, v0, v1, m - 1);                     // divide three new triangles respectively
        divide_triangle3(b, v0, v2, m - 1);
        divide_triangle3(c, v1, v2, m - 1);
    }
    else {                                                      // expected depth achieved, draw triangle
        triangle3(a, b, c);
    }
}

void Sierpinski2(int m)
{
    glColor3fv(colors3f[3]);                                    // set 2d triangle color
    divide_triangle2(v2f[0], v2f[1], v2f[2], n);                // divide and draw triangles recursively
}

void Sierpinski3(int m)
{
    glColor3fv(colors3f[0]);                                    // set 3d triangle color
    divide_triangle3(v3f[0], v3f[1], v3f[2], m);                // divide and draw triangles recursively
    glColor3fv(colors3f[1]);
    divide_triangle3(v3f[1], v3f[2], v3f[3], m);
    glColor3fv(colors3f[2]);
    divide_triangle3(v3f[0], v3f[2], v3f[3], m);
    glColor3fv(colors3f[3]);
    divide_triangle3(v3f[0], v3f[1], v3f[3], m);
}
