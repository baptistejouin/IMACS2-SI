#include "draw_scene.h"
#include "3D_tools.h"

void drawBase()
{
    glPushMatrix();
    glScalef(3.0, 3.0, 1.0);
    glColor3f(0.92, 0.81, 0.20);
    drawCircle();
    glPopMatrix();

    glPushMatrix();
    glScalef(2.0, 2.0, 10.0);
    glColor3f(0.92, 0.81, 0.20);
    drawCone();
    glPopMatrix();
}

void drawArm()
{
    glPushMatrix();
    glScalef(1.6, 1.6, 1.6);
    glColor3f(0.92, 0.81, 0.20);
    drawSphere();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 0., 1, 0);
    glScalef(1, 1, 10.0);
    glColor3f(0.92, 0.81, 0.20);
    drawCone();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 0., -1, 0);
    glScalef(1, 1, 10.0);
    glColor3f(0.92, 0.81, 0.20);
    drawCone();
    glPopMatrix();
}

void drawPan()
{
    glPushMatrix();
    glScalef(3.0, 3.0, 5.0);
    glColor3f(0.33, 0.45, 0);
    drawCircle();
    glPopMatrix();

    glPushMatrix();

    glBegin(GL_LINES);

    glColor3f(1, 0., 0);
    glVertex3f(0., 0., 5.);
    glVertex3f(cos(M_PI * 2) * 3, sin(M_PI * 2) * 3, 0);

    glVertex3f(0., 0., 5.);
    glVertex3f(cos(M_PI * 2 / 3) * 3, sin(M_PI * 2 / 3) * 3, 0);

    glVertex3f(0., 0., 5.);
    glVertex3f(-cos(M_PI * 2 / 6) * 3, -sin(M_PI * 2 / 6) * 3, 0);
    glEnd();

    glPopMatrix();
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

void draw()
{
    glPushMatrix();
    glScalef(8.0, 8.0, 8.0);
    drawFrame();
    glPopMatrix();

    // drawBase();
    // drawArm();
    drawPan();
}