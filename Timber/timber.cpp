#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

void moveSprite(int min,int width, int n, bool &beeActive, float &beeSpeed, int minSpeed, sf::Sprite &beeSprite, sf::Time &dt);
int main() {
	VideoMode vm(1366, 768);
	//VideoMode vm(1280, 1024);

	RenderWindow window(vm, "Timber!!", Style::Resize);
	
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

	//variable to control time itself
	Clock clock;

	//bool for pausing the game
	bool paused = true;


	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (Mouse::isButtonPressed(Mouse::Right)) {
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			paused = false;
		}
		
		//pause moving the obj before pressing enter
		if(!paused){
			//Measure time
			Time dt = clock.restart();// restart the clock

									  //setup the bee
			moveSprite(300,200,20, beeActive, beeSpeed,200 , beeSprite, dt);
			//setup the cloud
			moveSprite(0,150,30, cloud1Active, cloud1Speed,10 , cloudSprite1, dt);
			moveSprite(0,200,40, cloud2Active, cloud2Speed, 25, cloudSprite2, dt);
			moveSprite(0,100,50, cloud3Active, cloud3Speed,5 , cloudSprite3, dt);
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

void moveSprite(int min,int width,int n, bool &beeActive, float &beeSpeed, int minSpeed, sf::Sprite &beeSprite, sf::Time &dt) {
	if (!beeActive) {
		//How fast the bee is
		srand((int)time(0) * n);
		beeSpeed = (rand() % minSpeed) + minSpeed;

		//How high is the bee
		srand((int)time(0) * n);
		float height = (rand() % width)+min;
		beeSprite.setPosition(1366, height);
		std::cout << height << std::endl;
		beeActive = true;
	}//moving the bee
	else {
		beeSprite.setPosition(
			beeSprite.getPosition().x - (beeSpeed * dt.asSeconds()),
			beeSprite.getPosition().y
		);
		//if the bee reached the right edge of the screen
		if (beeSprite.getPosition().x<0) {
			//setup the bee agin
			beeActive = false;
		}
	}
}
