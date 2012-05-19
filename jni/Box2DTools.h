
#ifndef BOX2DTOOLS_H
#define BOX2DTOOLS_H 

#include <GLES/gl.h>
#include <Box2D/Box2D.h>

void Box2dtoGL(GLfloat *glMat, const b2Transform &box2dMat);

#endif /* BOX2DTOOLS_H */
