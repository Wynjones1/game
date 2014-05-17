#include "object.h"

void Draw(Object *d, Program &program)
{
	glUniformMatrix4fv(program.model, 1, GL_FALSE, &d->model_matrix[0][0]);
	d->Draw(program);
}