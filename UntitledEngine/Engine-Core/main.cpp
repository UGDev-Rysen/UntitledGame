#include <GLFW\glfw3.h>
#include "src\graphics\window.h"
#include <iostream>
int main() {
	using namespace u_engine;
	using namespace graphics;

	Window window("Untitled Engine", 800, 600);

	while (!window.closed()) {
		window.update();
	}

	system("PAUSE");
	return 0;
}