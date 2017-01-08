#include <math.h>
#include <GL/freeglut.h>

#define WIDTH  640
#define HEIGHT 480

GLfloat ballX = 100.0f;
GLfloat ballY = 100.0f;
GLfloat ballRadius = 14.0f;

void init();
void display();
void timer(int value);

int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("OpenGL - Brickout");
	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	init();
	glutMainLoop();

}

void init() {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glTranslatef(ballX, ballY, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);

	GLfloat angle;
	int i;

	for(i = 0; i <= 100; i++) {
		angle = i * 2.0f * M_PI / 100;
		glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
	}
	
	glEnd();
	glPopMatrix();
	glutSwapBuffers();

	ballX += 2.0f;
	ballY += 2.0f;

}

void timer(int value) {
	
	glutPostRedisplay();
	glutTimerFunc(30, timer, 0);

}
