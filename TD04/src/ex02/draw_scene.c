#include "draw_scene.h"
#include "3D_tools.h"

void drawBase()
{
}

void drawArm()
{
}

void drawPan()
{
}
void drawFrame()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0., 0., 0.);
    glVertex3f(1, 0., 0.);

    glColor3f(0, 1, 0);
    glVertex3f(0., 0., 0.);
    glVertex3f(0., 1, 0.);

    glColor3f(0, 0, 1);
    glVertex3f(0., 0., 0.);
    glVertex3f(0., 0., 1);

    glEnd();
}

int rot = 0;

void draw()
{
    rot = rot >= 360 ? 0 : rot + 1;

    glPushMatrix();
    glScalef(8.0, 8.0, 8.0);
    drawFrame();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0., 0., 5.);
    glScalef(5, 5, 5);
    drawCircle();
    glPopMatrix();

    glPushMatrix();
    glRotatef(rot, 0., 0., 5);
    glTranslatef(4., 0., 5.);
    glColor3f(1, 0, 0);
    drawSphere();
    glPopMatrix();
}