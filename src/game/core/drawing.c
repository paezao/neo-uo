#include "drawing.h"

void begin_drawing(struct Window * window)
{
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void end_drawing(struct Window * window)
{
    glfwSwapBuffers(window->handle);
    glDisable(GL_BLEND);
}

void clear_background(Color color)
{
    glClearColor(color.red, color.green, color.blue, color.alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw_rectangle(Rect rect, Texture *texture, Color color)
{
    if(texture) 
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture( GL_TEXTURE_2D, texture->id );
    }

    glPushMatrix();

    glScalef(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    glColor4ub(color.red, color.green, color.blue, color.alpha);

    // Top Left
    if(texture) glTexCoord2f( 0.f, 0.f );
    glVertex3f(rect.x - rect.width / 2, rect.y - rect.height / 2, -10.0f);

    // Bottom Left
    if(texture) glTexCoord2f( 0.f, 1.f );
    glVertex3f(rect.x - rect.width / 2, rect.y + rect.height / 2, -10.0f);

    // Bottom Right
    if(texture) glTexCoord2f( 1.f, 1.f );
    glVertex3f(rect.x + rect.width / 2, rect.y + rect.height / 2, -10.0f);

    // Top Right
    if(texture) glTexCoord2f( 1.f, 0.f );
    glVertex3f(rect.x + rect.width / 2, rect.y - rect.height / 2, -10.0f);

    glEnd();

    glPopMatrix();

    if(texture)
    {
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void draw_tex_map(Rect rect, int east_offset, int south_east_offset, int south_offset, Texture *texture, Color color)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texture->id );

    glPushMatrix();

    glScalef(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    glColor4ub(color.red, color.green, color.blue, color.alpha);

    // Top Left
    glTexCoord2f( 0.f, 0.f );
    glVertex3f(rect.x, rect.y - (rect.width / 2), -10.0f);

    // Bottom Left
    glTexCoord2f( 0.f, 1.f );
    glVertex3f(rect.x - (rect.width / 2), rect.y + south_offset, -10.0f);

    // Bottom Right
    glTexCoord2f( 1.f, 1.f );
    glVertex3f(rect.x, rect.y + (rect.height / 2) + south_east_offset, -10.0f);

    // Top Right
    glTexCoord2f( 1.f, 0.f );
    glVertex3f(rect.x + (rect.width / 2), rect.y + east_offset, -10.0f);

    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void begin_3d(struct Window * window)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0, window->width, window->height, 0, -1000.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void end_3d()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); 
}
