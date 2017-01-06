#include <math.h>
#include <GL/freeglut.h>

void init(void);
void display(void);
void draw_ball(void);

struct {
	float x;
	float y;
	float r;
	float c[3];
} ball;

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

	// Initialize Ball
	ball.x = 0.0f;
	ball.y = 0.0f;
	ball.r = 0.05f;
	ball.c[0] = 1.0f;
	ball.c[1] = 1.0f;
	ball.c[2] = 1.0f;

}

void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);
	
	// Draw Ball
	draw_ball();

	glFlush();

}


void draw_ball(void) {
	
	int i, num_segments;
	float angle;

	glColor3f(ball.c[0], ball.c[1], ball.c[2]);
	glTranslatef(ball.x, ball.y, 0.0f);
	
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	for (i = 0; i <= num_segments; i++) {
		angle = i * 2.0f * M_PI / num_segments;
		glVertex2f(cos(angle) * ball.r, sin(angle) * ball.r);
	}
	glEnd();

}
