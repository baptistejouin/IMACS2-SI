#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Coords
{
	double x, y;
};
struct GL_FRGB
{
	GLfloat red, green, blue;
};

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "TD03 Ex01";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Virtual windows space */
// Space is defined in interval -1 and 1 on x and y axes
static const float GL_VIEW_SIZE = 160.;

void drawSquare(float cx, float cy, float width, float heigth, GL_FRGB color, int is_full)
{
	if (is_full == 0)
	{
		glBegin(GL_LINE_LOOP);
	}
	else
	{
		glBegin(GL_QUADS);
	}

	glColor3f(color.red, color.green, color.blue);

	glVertex2f(cx, cy);
	glVertex2f(cx + width, cy);
	glVertex2f(cx + width, cy + heigth);
	glVertex2f(cx, cy + heigth);

	glEnd();
}

void drawCircle(float cx, float cy, float r, int num_segments, GL_FRGB color, int is_full)
{
	float theta = 3.1415926 * 2 / float(num_segments);
	float tan = tanf(theta);

	float rad = cosf(theta);

	float x = r;

	float y = 0;

	glLineWidth(2);

	if (is_full == 0)
	{
		glBegin(GL_LINE_LOOP);
	}
	else
	{
		glBegin(GL_POLYGON);
	}
	glColor3f(color.red, color.green, color.blue);

	for (int i = 0; i < num_segments; i++)
	{
		glVertex2f(x + cx, y + cy);

		float tx = -y;
		float ty = x;

		x += tx * tan;
		y += ty * tan;

		x *= rad;
		y *= rad;
	}
	glEnd();
};

void drawBaseLine(float cx, float cy, float width, GL_FRGB color)
{
	glBegin(GL_LINES);
	glColor3f(color.red, color.green, color.blue);

	glVertex2f(cx, cy);
	glVertex2f(cx + width, cy);

	glEnd();

	glPopMatrix();
}

void drawFirstArm()
{
	drawCircle(0, 0, 20, 100, {1., 1., 1.}, 0);
	drawCircle(60, 0, 10, 100, {1., 1., 1.}, 0);

	// First line
	glBegin(GL_LINES);
	glVertex2f(0, 20);
	glVertex2f(60, 10);
	glEnd();

	// Second line
	glBegin(GL_LINES);
	glVertex2f(0, -20);
	glVertex2f(60, -10);
	glEnd();
}

void drawRoundedSquare(float cx, float cy, float width, float heigth, GL_FRGB color, int is_full)
{
	// TODO: RoundedSquare instead of normal square
	drawSquare(cx, cy, width, heigth, color, is_full);
}

void drawSecondArm()
{
	drawRoundedSquare(-5, -5, 10, 10, {0., 0., 1.}, 0);

	drawSquare(-4, -3, 46, 6, {0., 0., 1.}, 0);

	glPushMatrix();
	glTranslatef(38., 0., 0.);

	drawRoundedSquare(-5, -5, 10, 10, {0., 0., 1.}, 0);

	glPopMatrix();
}

void drawThirdArm()
{
	drawSquare(-2, -2, 40, 4, {0., 1., 0.}, 1);

	glPushMatrix();
	glTranslatef((42 - 4), 0., 0.);

	drawCircle(0, 0, 4, 40, {0., 1., 0.}, 1);

	glPopMatrix();
}

void draw()
{
	drawBaseLine(-160, 0, 160 * 2, {1., 0., 0.});
	drawFirstArm();
	drawSecondArm();
	drawThirdArm();
}

/* Error handling function */
void onError(int error, const char *description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow *window, int width, int height)
{
	aspectRatio = width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (aspectRatio > 1)
	{
		gluOrtho2D(
			-GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
			-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
	}
	else
	{
		gluOrtho2D(
			-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
			-GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
	}
	glMatrixMode(GL_MODELVIEW);
}

void onKey(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_A:
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_L:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case GLFW_KEY_P:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		default:
			fprintf(stdout, "Touche non gérée\n");
		}
	}
}

int main(int argc, char **argv)
{
	/* GLFW initialisation */
	GLFWwindow *window;
	if (!glfwInit())
		return -1;

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, onWindowResized);
	glfwSetKeyCallback(window, onKey);

	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	glPointSize(4.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		/* RENDER HERE */
		draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if (elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
		}
	}

	glfwTerminate();
	return 0;
}
