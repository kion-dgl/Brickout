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
