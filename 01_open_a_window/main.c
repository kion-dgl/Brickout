#include <GL/freeglut.h>

void init(void);
void display(void);

int main(int argc, char *argv[]) {

    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutCreateWindow("OpenGL Brickout");
    glutDisplayFunc(display);

    init();
    glutMainLoop();

    return 0;

}

void init(void) {

    glClearColor(0.0, 0.0, 0.0, 1.0);

}

void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

}
