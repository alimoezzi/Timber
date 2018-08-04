#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	VideoMode vm(1366, 768);

	RenderWindow window(vm, "Timber!!", Style::Fullscreen);
	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			window.close();
		}
		window.clear();
		window.display();
	}
	return 0;
}