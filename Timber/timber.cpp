#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	VideoMode vm(1366, 768);

	RenderWindow window(vm, "Timber!!", Style::Fullscreen);
	
	Texture textureBackground;/* creating a texture to hold a graohic on the GPU*/
	textureBackground.loadFromFile("../graphics/background.png");/* load a graphic to texture*/

	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);/* attach texture to the sprite */

	spriteBackground.setPosition(0, 0);/* set sprite to cover the screen */

	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			window.close();
		}
		window.clear();
		window.draw(spriteBackground);/* draws our game scene */
		window.display();/*we write to a hidden surface then display it to avoiding glitch*/
	}
	return 0;
}