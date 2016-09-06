#include "drawing.h"

void begin_drawing(struct Window * window)
{
}

void end_drawing(struct Window * window)
{
    glfwSwapBuffers(window->handle);
}

void clear_background(Color color)
{
    glClearColor(color.red, color.green, color.blue, color.alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw_quad(Color color)
{
    glBegin(GL_QUADS); //Begin quadrilateral coordinates

    glColor4ub(color.red, color.green, color.blue, color.alpha);

    glVertex3f(-0.5f, 0.5f, 0.0f);
    glVertex3f( 0.5f, 0.5f, 0.0f);
    glVertex3f( 0.5f,-0.5f, 0.0f);
    glVertex3f(-0.5f,-0.5f, 0.0f);

    glEnd();
}

void begin_3d(struct Window * window)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0, window->width, window->height, 0, -1000.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
}

void end_3d()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); 
}
