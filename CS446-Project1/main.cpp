/* Matthew Clark
   CS 446 - Computer Graphics
================================================
	- Left click for circles
	- Right click to transform shape
*/

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <vector>
#include <iostream>

#define PI 3.14159
#define CIRCLE_RES 20
#define CIRCLE_RAD 20

class Circle {
public:
	Circle(int x, int y, int r) {
		m_x = x; 
		m_y = y;
		m_r = r;
	}

	int m_x = 0;
	int m_y = 0;
	int m_r = 0;
};

class GLObject {
public:
	double hScale = 1.0;
	double vScale = 1.0;
	double xPos = 400;
	double yPos = 300;
	int angle = 0;
};

std::vector<Circle*> vecCircles;
GLObject objShape;
bool menuOpen = false;

void displayLoop(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	gluOrtho2D(0, 800, 600, 0);

	//draw circles
	glColor3f(1.0f, 1.0f, 1.0f);
	for (size_t i = 0; i < vecCircles.size(); i++) {
		Circle* cir = vecCircles.at(i);

		glBegin(GL_POLYGON);

		for (int j = 0; j < CIRCLE_RES; j++) {
			double xPos = cir->m_x + cir->m_r * cos((2 * PI) / CIRCLE_RES * j);
			double yPos = cir->m_y + cir->m_r * sin((2 * PI) / CIRCLE_RES * j);

			glVertex2f((float)xPos, (float)yPos);
		}

		glEnd();
	}

	//draw transformed shape

	glTranslated(objShape.xPos, objShape.yPos, 0);
	glScaled(objShape.hScale, objShape.vScale, 1);
	glRotated(objShape.angle, 0, 0, 1);

	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
	glVertex2f(-40, -40);
	glVertex2f(40, -40);
	glVertex2f(-40, 40);
	glVertex2f(40, 40);

	glVertex2f(60, 60);
	glVertex2f(140, 60);
	glVertex2f(60, 140);
	glVertex2f(140, 140);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(-40, -40);
	glVertex2f(140, 60);
	glVertex2f(160, 140);
	glEnd();

	glutSwapBuffers();
}

void processMenuStatus(int status, int x, int y) {
	if (status == GLUT_MENU_IN_USE) menuOpen = true;
	else menuOpen = false;
}

void menu(int item) {
	switch (item) {
	case 1:
		objShape.xPos -= 5;
		break;
	case 2:
		objShape.xPos += 5;
		break;
	case 3:
		objShape.yPos -= 5;
		break;
	case 4:
		objShape.yPos += 5;
		break;
	case 5:
		objShape.hScale *= 2;
		break;
	case 6:
		objShape.hScale *= 0.5;
		break;
	case 7:
		objShape.vScale *= 2;
		break;
	case 8:
		objShape.vScale *= 0.5;
		break;
	case 9:
		objShape.angle += 10;
		break;
	case 10:
		objShape.angle -= 10;
		break;
	default:
		std::cout << "menu number " << item << " pressed" << std::endl;
		break;
	}
}

void createMenu() {
	int subTranslate = glutCreateMenu(menu);
	glutAddMenuEntry("Left", 1);
	glutAddMenuEntry("Right", 2);
	glutAddMenuEntry("Up", 3);
	glutAddMenuEntry("Down", 4);

	int subScale = glutCreateMenu(menu);
	glutAddMenuEntry("H-Enlarge", 5);
	glutAddMenuEntry("H-Shrink", 6);
	glutAddMenuEntry("V-Enlarge", 7);
	glutAddMenuEntry("V-Shrink", 8);

	int subRotate = glutCreateMenu(menu);
	glutAddMenuEntry("Clockwise", 9);
	glutAddMenuEntry("Counter-Clockwise", 10);

	int mainMenu = glutCreateMenu(menu);
	glutAddSubMenu("Translate", subTranslate);
	glutAddSubMenu("Scale", subScale);
	glutAddSubMenu("Rotate", subRotate);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void pressKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:

		break;
	case GLUT_KEY_DOWN:
		
		break;
	}
}

void releaseKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		
		break;
	case GLUT_KEY_DOWN:

		break;
	}
}

void pressNormalKey(unsigned char key, int x, int y) {
	switch (key) {
	case 'Q':
	case 'q':
		exit(1);
		break;
	}
}

void releaseNormalKey(unsigned char key, int x, int y) {

}

void mouseButton(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_UP) {
			
		} else {// state = GLUT_DOWN
			if (!menuOpen) {
				vecCircles.push_back(new Circle(x, y, CIRCLE_RAD));
			}
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_UP) {

		} else {// state = GLUT_DOWN
			
		}
		break;
	}
}

void redraw(int) {
	glutPostRedisplay();
	glutTimerFunc(1000.0 / 60, redraw, 0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glViewport(0, 0, 800, 600);
	glutCreateWindow("CS446 - Project 1");
	
	createMenu();
	glutMenuStatusFunc(processMenuStatus);

	//drawing
	glutDisplayFunc(displayLoop);
	//glutReshapeFunc(changeSize);
	//glutIdleFunc(displayLoop);
	glutTimerFunc(1000.0 / 60, redraw, 0);

	//ignore repeated key holding
	glutIgnoreKeyRepeat(true);

	//handle keyboard
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutKeyboardFunc(pressNormalKey);
	glutKeyboardUpFunc(releaseNormalKey);

	//handle mouse
	glutMouseFunc(mouseButton);
	//glutMotionFunc(mouseMove);

	glutMainLoop();
	return 0;
}