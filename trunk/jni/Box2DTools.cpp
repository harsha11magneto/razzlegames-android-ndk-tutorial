

#include <Box2D/Box2D.h>

#include "Box2DTools.h"

void Box2dtoGL(GLfloat *glMat, const b2Transform &box2dMat)
{

	glMat[0] = box2dMat.R.col1.x; glMat[1] = box2dMat.R.col1.y; glMat[2] = 0.0f; glMat[3] = 0.0f;
	glMat[4] = box2dMat.R.col2.x; glMat[5] = box2dMat.R.col2.y; glMat[6] = 0.0f; glMat[7] = 0.0f;
	glMat[8] = 0.0f; glMat[9] = 0.0f; glMat[10] = 1.0f; glMat[11] = 0.0f;
	glMat[12] = box2dMat.position.x; glMat[13] = box2dMat.position.y; glMat[14] = 0.0f; glMat[15] = 1.0f;
}


