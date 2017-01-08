#include <math.h>
#include <stdbool.h>
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
	bool left_down;
	bool right_down;
	bool x_hover;
	bool y_hover;
} paddle;

struct {
	GLfloat x;
	GLfloat y;
	GLfloat width;
	GLfloat height;
	bool broken;
} bricks[30];

void init();
void display();
void timer(int value);

void keydown_callback(int key, int x, int y);
void keyup_callback(int key, int x, int y);

int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("OpenGL - Brickout");
	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutSpecialFunc(keydown_callback);
	glutSpecialUpFunc(keyup_callback);
	init();
	glutMainLoop();

}

void init() {

	GLfloat padding, padding_width;
	int i, row, col;

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
	paddle.left_down = false;
	paddle.right_down = false;
	paddle.x_hover = false;
	paddle.y_hover = false;

	padding = 2.0f;
	padding_width = WIDTH - padding;

	for(i = 0; i < 30; i++) {

		row = i / 5;
		col = i % 5;
		
		bricks[i].width = (padding_width / 5) - padding;
		bricks[i].height = 24.0f;
		bricks[i].x = 2.0f + (bricks[i].width + 2.0f) * col;
		bricks[i].y = HEIGHT - (2.0f + (row * 26.0f));
	
		bricks[i].broken = false;
	}

}

void display() {
	
	GLfloat bl, br, bt, bb;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	if(ball.x >= paddle.x-paddle.width && ball.x <= paddle.x+paddle.width) {
		paddle.x_hover = true;	
	} else {
		paddle.x_hover = false;
	}

	if(ball.y - ball.radius >= paddle.y-paddle.height && ball.y - ball.radius <= paddle.y) {
		paddle.y_hover = true;	
	} else {
		paddle.y_hover = false;
	}

	if(paddle.x_hover && paddle.y_hover) {
		ball.dy = -ball.dy;
	}


	glPushMatrix();

	glTranslatef(ball.x, ball.y, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);

	GLfloat angle;
	int i, k, b;

	for(i = 0; i <= 100; i++) {
		angle = i * 2.0f * M_PI / 100;
		glVertex2f(cos(angle) * ball.radius, sin(angle) * ball.radius);
	}
	
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(paddle.x, paddle.y, 0.0f);
	glBegin(GL_QUADS);
	
	if(paddle.x_hover && paddle.y_hover){
		glColor3f(1.0f, 1.0f, 0.0f);
	} else if(paddle.y_hover) {
		glColor3f(0.0f, 1.0f, 0.0f);
	} else if(paddle.x_hover) {
		glColor3f(1.0f, 0.0f, 0.0f);
	} else {
		glColor3f(1.0f, 1.0f, 1.0f);
	}

	glVertex2f(-paddle.width, 0.0f);
	glVertex2f( paddle.width, 0.0f);
	glVertex2f( paddle.width, paddle.height);
	glVertex2f(-paddle.width, paddle.height);
	glEnd();
	glPopMatrix();

	for(i = 0; i < 6; i++) {
		
		switch(i) {
			case 0:
				glColor3f(1.0f, 0.0f, 0.0f);
			break;
			case 1:
				glColor3f(1.0f, 0.647f, 0.0f);
			break;
			case 2:
				glColor3f(1.0f, 1.0f, 0.0f);
			break;
			case 3:
				glColor3f(0.0f, 1.0f, 0.0f);
			break;
			case 4:
				glColor3f(0.0f, 0.0f, 1.0f);
			break;
			case 5:
				glColor3f(0.5f, 0.0f, 0.5f);
			break;
		}

		bl = ball.x - ball.radius;
		br = ball.x + ball.radius;
		bt = ball.y + ball.radius;
		bb = ball.y - ball.radius;

		for(k = 0; k < 5; k++) {
			
			b = i * 5 + k;
			if(bricks[b].broken) {
				continue;
			}

			if(
				((bl >= bricks[b].x && bl <= bricks[b].x + bricks[b].width) || 
				(br >= bricks[b].x && br <= bricks[b].x + bricks[b].width)) && 
				((bt >= bricks[b].y - bricks[b].height && bt <= bricks[b].y) || 
				(bb >= bricks[b].y - bricks[b].height && bb <= bricks[b].y))
			) {
				ball.dy = -ball.dy;
				bricks[b].broken = true;
				continue;
			}

			glBegin(GL_QUADS);
			glVertex2f(bricks[b].x, bricks[b].y);
			glVertex2f(bricks[b].x + bricks[b].width, bricks[b].y);
			glVertex2f(bricks[b].x + bricks[b].width, bricks[b].y - bricks[b].height);
			glVertex2f(bricks[b].x, bricks[b].y - bricks[b].height);
			glEnd();
		}
	}

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

	if(paddle.left_down) {
		paddle.x -= paddle.dx;
	}

	if(paddle.right_down) {
		paddle.x += paddle.dx;
	}

	if(paddle.x < paddle.width) {
		paddle.x = paddle.width;
	} else if (paddle.x > WIDTH - paddle.width) {
		paddle.x = WIDTH - paddle.width;
	}


}

void timer(int value) {
	
	glutPostRedisplay();
	glutTimerFunc(30, timer, 0);

}

void keydown_callback(int key, int x, int y) {

	switch(key) {
		
		case GLUT_KEY_RIGHT:
			paddle.right_down = true;
		break;
		case GLUT_KEY_LEFT:
			paddle.left_down = true;
		break;

	}

}

void keyup_callback(int key, int x, int y) {

	switch(key) {
		
		case GLUT_KEY_RIGHT:
			paddle.right_down = false;
		break;
		case GLUT_KEY_LEFT:
			paddle.left_down = false;
		break;

	}

}
