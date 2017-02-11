/*
    DashGL.com Brickout Clone Tutorial

    Copyright (C) 2017 Benjamin Collins

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License version 2
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <math.h>
#include <GL/freeglut.h>

#define WIDTH 640
#define HEIGHT 480

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
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL Brickout");
    glutDisplayFunc(display);

    init();
    glutMainLoop();

    return 0;

}

void init(void) {

    glClearColor(0.0, 0.0, 0.0, 1.0);

	// Initialize Orthangonal Coordinates
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,WIDTH,0,HEIGHT);

	// Initialize Ball
	ball.x = WIDTH * 0.5f;
	ball.y = HEIGHT * 0.5f;
	ball.r = HEIGHT * 0.025f;
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
	glPushMatrix();
	glTranslatef(ball.x, ball.y, 0.0f);
	
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	for (i = 0; i <= num_segments; i++) {
		angle = i * 2.0f * M_PI / num_segments;
		glVertex2f(cos(angle) * ball.r, sin(angle) * ball.r);
	}
	glEnd();
	glPopMatrix();

}
