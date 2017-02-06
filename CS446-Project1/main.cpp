#include <GL\glew.h>
#include <GL\freeglut.h>
#include <vector>

#define PI 3.14159
#define CIRCLE_RES 10
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

std::vector<Circle*> vecCircles;

void displayLoop(void) {
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1, 1);

	glColor3f(1.0f, 1.0f, 1.0f);

	for (size_t i = 0; i < vecCircles.size(); i++) {
		Circle* cir = vecCircles.at(i);

		glBegin(GL_POLYGON);

		for (int j = 0; j < CIRCLE_RES; j++) {
			double xPos = cir->m_x + cir->m_r * cos((2 * PI) / CIRCLE_RES * j);
			double yPos = cir->m_y + cir->m_r * sin((2 * PI) / CIRCLE_RES * j);

			glVertex2f(xPos, yPos);
		}

		glEnd();
	}

	glutSwapBuffers();
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
		exit(true);
		break;
	case GLUT_KEY_DOWN:

		break;
	}
}

void pressNormalKey(unsigned char key, int x, int y) {

}

void releaseNormalKey(unsigned char key, int x, int y) {

}

void mouseButton(int button, int state, int x, int y) {
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {
		// when the button is released
		if (state == GLUT_UP) {
			vecCircles.push_back(new Circle(x, y, CIRCLE_RAD));
		} else {// state = GLUT_DOWN
			//nothing
		}
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glViewport(0, 0, 800, 600);
	glutCreateWindow("CS446 - Project 1");
	
	//drawing
	glutDisplayFunc(displayLoop);
	//glutReshapeFunc(changeSize);
	glutIdleFunc(displayLoop);

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