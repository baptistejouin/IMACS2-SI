#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

struct Coords
{
	double x, y;
};

std::vector<Coords> tabMouseButtonCoordsHistory{};

/* Window properties */
static const unsigned int WINDOW_WIDTH = 600;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "TD02 Ex02";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Virtual windows space */
// Space is defined in interval -1 and 1 on x and y axes
static const float GL_VIEW_SIZE = 2.;

static bool D_HAS_PRESS = false;

void pointsEx01()
{
	glColor3f(1, 1, 1);
	glVertex2f(0., 0.);

	glColor3f(1, 0, 0);
	glVertex2f(0.5, 0.);

	glColor3f(0, 1, 0);
	glVertex2f(0., 0.5);

	glColor3f(1, 0, 1);
	glVertex2f(-0.5, -0.5);
}

void drawFromMousePoints()
{
	for (size_t i = 0; i < tabMouseButtonCoordsHistory.size(); i++)
	{
		glColor3f(1, 1, 1);
		glVertex2f(tabMouseButtonCoordsHistory[i].x, tabMouseButtonCoordsHistory[i].y);
	}

	// tabMouseButtonCoordsHistory.clear();
}

void draw()
{
	glColor3f(1, 1, 1);

	if (D_HAS_PRESS)
	{
		glBegin(GL_LINE_LOOP);
	}
	else
	{
		glBegin(GL_POINTS);
		pointsEx01();
	}

	drawFromMousePoints();
	glEnd();
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
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		D_HAS_PRESS = true;
	}
}

void onMouseButton(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;

		// getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);

		double x = ((xpos * 2 / WINDOW_WIDTH) - 1) * WINDOW_WIDTH / WINDOW_HEIGHT;
		double y = -((ypos * 2 / WINDOW_HEIGHT) - 1);

		Coords mouseCoords = {x, y};

		tabMouseButtonCoordsHistory.push_back(mouseCoords);
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
	glfwSetMouseButtonCallback(window, onMouseButton);

	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	glPointSize(4.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

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
