#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	VideoMode vm(1366, 768);

	RenderWindow window(vm, "Timber!!", Style::Fullscreen);
	
	Texture textureBackground;/* creating a texture to hold a graohic on the GPU memory*/
	textureBackground.loadFromFile("../graphics/background.png");/* load a graphic to texture*/

	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);/* attach texture to the sprite */

	spriteBackground.setPosition(0, 0);/* set sprite to cover the screen */

	// adding tree
	Texture treeTexture;
	treeTexture.loadFromFile("../graphics/tree.png");
	Sprite treeSprite;
	treeSprite.setTexture(treeTexture);
	treeSprite.setPosition(810, 0);

	// adding bee
	Texture beeTexture;
	beeTexture.loadFromFile("../graphics/bee.png");
	Sprite beeSprite;
	beeSprite.setTexture(beeTexture);
	beeSprite.setPosition(0, 600);
	bool beeActive = false;
	float beeSpeed = 0.0f;
	
	// cloud texture
	Texture cloudTexture;
	cloudTexture.loadFromFile("../graphics/cloud.png");

	// adding 3 clouds
	Sprite cloudSprite1;
	Sprite cloudSprite2;
	Sprite cloudSprite3;

	cloudSprite1.setTexture(cloudTexture);
	cloudSprite2.setTexture(cloudTexture);
	cloudSprite3.setTexture(cloudTexture);

	cloudSprite1.setPosition(0, 0);
	cloudSprite2.setPosition(0, 250);
	cloudSprite3.setPosition(0, 500);

	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			window.close();
		}
		window.clear();
		window.draw(spriteBackground);/* draws our game scene */

		// drawing the clouds
		window.draw(cloudSprite1);
		window.draw(cloudSprite2);
		window.draw(cloudSprite3);

		// drawing the tree
		window.draw(treeSprite);

		// drawing the bee
		window.draw(beeSprite);


		window.display();/*we write to a hidden surface then display it to avoiding glitch*/
	}
	return 0;
}