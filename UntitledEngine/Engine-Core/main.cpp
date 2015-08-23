#include "src\graphics\window.h"
#include "src\maths\maths.h"
#include <glfw3.h>
#include <iostream>
int main() {
	using namespace u_engine;
	using namespace graphics;
	using namespace maths;

	Window window("Untitled Engine", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vec3 a(1.0f, 2.0f, 3.0f);
	vec3 b(2, 4, 6);

	a += b;
	
	while (!window.closed()) {
		window.clear();
		std::cout << std::endl;
		std::cout << (a) << std::endl;

#if 1
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
#else
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
#endif

		window.update();
	}


	return 0;
}