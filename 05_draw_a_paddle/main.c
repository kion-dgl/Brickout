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

#define WIDTH  640
#define HEIGHT 480

struct {
	GLfloat x;
	GLfloat y;
	GLfloat radius;
	GLfloat dy;
	GLfloat dx;
} ball;

struct {
	GLfloat x;
	GLfloat y;
	GLfloat dx;
	GLfloat width;
	GLfloat height;
} paddle;

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

	ball.x = 320.0f;
	ball.y = 240.0f;
	ball.radius = 14.0f;
	ball.dx = 3.0f;
	ball.dy = -3.0f;

	paddle.x = 320.0f;
	paddle.y = 20.0f;
	paddle.height = 18.0f;
	paddle.width = 60.0f;
	paddle.dx = 4.0f;

}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glTranslatef(ball.x, ball.y, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);

	GLfloat angle;
	int i;

	for(i = 0; i <= 100; i++) {
		angle = i * 2.0f * M_PI / 100;
		glVertex2f(cos(angle) * ball.radius, sin(angle) * ball.radius);
	}
	
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(paddle.x, paddle.y, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-paddle.width, 0.0f);
	glVertex2f( paddle.width, 0.0f);
	glVertex2f( paddle.width, paddle.height);
	glVertex2f(-paddle.width, paddle.height);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();

	ball.x += ball.dx;
	ball.y += ball.dy;

	if(ball.x < ball.radius) {
		ball.x = ball.radius;
		ball.dx = -ball.dx;
	} else if(ball.x > WIDTH - ball.radius) {
		ball.x = WIDTH - ball.radius;
		ball.dx = -ball.dx;
	}

	if(ball.y < ball.radius) {
		ball.y = ball.radius;
		ball.dy = -ball.dy;
	} else if(ball.y > HEIGHT - ball.radius) {
		ball.y = HEIGHT - ball.radius;
		ball.dy = -ball.dy;
	}

}

void timer(int value) {
	
	glutPostRedisplay();
	glutTimerFunc(30, timer, 0);

}
