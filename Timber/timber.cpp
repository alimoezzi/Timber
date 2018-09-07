#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#pragma warning(disable:4996)
//#pragma warning ( disable : 4789 )
using namespace sf;


void moveSprite(int min,int width, int n, bool &beeActive, float &beeSpeed, int minSpeed, sf::Sprite &beeSprite, sf::Time &dt);
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum side {
	LEFT,RIGHT,NONE
};

side branchPositions[NUM_BRANCHES];

int main() {
	//VideoMode vm(1366, 768);
	VideoMode vm(VideoMode::getDesktopMode().width,VideoMode::getDesktopMode().height);
	//VideoMode vm(1280, 1024);
	const float OBJSCALE = (((float)vm.width / 1920));

	RenderWindow window(vm, "Timber!!", Style::Resize);
	
	Texture textureBackground;/* creating a texture to hold a graohic on the GPU memory*/
	textureBackground.loadFromFile("../graphics/background.png");/* load a graphic to texture*/

	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);/* attach texture to the sprite */

	spriteBackground.setPosition(0, 0);/* set sprite to cover the screen */
	spriteBackground.setScale(OBJSCALE, OBJSCALE);

	// adding tree
	Texture treeTexture;
	treeTexture.loadFromFile("../graphics/tree.png");
	Sprite treeSprite;
	treeSprite.setTexture(treeTexture);
	treeSprite.setScale(OBJSCALE, OBJSCALE);
	treeSprite.setPosition(800*OBJSCALE, 0);

	// adding bee
	Texture beeTexture;
	beeTexture.loadFromFile("../graphics/bee.png");
	Sprite beeSprite;
	beeSprite.setTexture(beeTexture);
	beeSprite.setPosition(0, 600);
	beeSprite.setScale(OBJSCALE, OBJSCALE);
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

	cloudSprite1.setScale(OBJSCALE, OBJSCALE);
	cloudSprite2.setScale(OBJSCALE, OBJSCALE);
	cloudSprite3.setScale(OBJSCALE, OBJSCALE);

	cloudSprite1.setPosition(0, 0);
	cloudSprite2.setPosition(0, 250);
	cloudSprite3.setPosition(0, 500);

	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	//Prepare 6 branches
	Texture branchTexture;
	branchTexture.loadFromFile("../graphics/branch.png");
	//Set the texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(branchTexture);
		branches[i].setPosition(-2000 * OBJSCALE, -2000 * OBJSCALE);

		//set the sprite's origin to dead center
		//we can then spin it around without changing its position
		branches[i].setOrigin(220 * OBJSCALE, 20 * OBJSCALE);
	}
	//prepare the player
	Texture playerTexture;
	playerTexture.loadFromFile("../graphics/player.png");
	Sprite playerSprite;
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(580 * OBJSCALE, 720 * OBJSCALE);
	playerSprite.setScale(OBJSCALE, OBJSCALE);

	//initial side of the player
	side playerSide = side::LEFT;

	//prepare the gravestone
	Texture RIPTexture;
	RIPTexture.loadFromFile("../graphics/rip.png");
	Sprite RIPSprite;
	RIPSprite.setTexture(RIPTexture);
	RIPSprite.setPosition(600 * OBJSCALE, 860 * OBJSCALE);
	RIPSprite.setScale(OBJSCALE, OBJSCALE);

	//prepare the axe
	Texture axeTexture;
	axeTexture.loadFromFile("../graphics/axe.png");
	Sprite axeSprite;
	axeSprite.setTexture(axeTexture);
	axeSprite.setPosition(700 * OBJSCALE, 830 * OBJSCALE);
	axeSprite.setScale(OBJSCALE, OBJSCALE);

	//line the axe up with the tree
	const float AXE_POSITION_LEFT = 700 * OBJSCALE;
	const float AXE_POSITION_RIGHT = 1075 * OBJSCALE;

	//variable to control time itself
	Clock clock;

	// prepare the flying log
	Texture logTexture;
	logTexture.loadFromFile("../graphics/log.png");
	Sprite logSprite;
	logSprite.setTexture(logTexture);
	logSprite.setPosition(800*OBJSCALE,720*OBJSCALE);
	logSprite.setScale(OBJSCALE, OBJSCALE);

	//some other useful log related variable
	bool logActive = false;//moving or not
	float logSpeedX = 1000;
	float logSpeedY = -1500;


	//time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400*OBJSCALE;
	float timeBarHeight = 80*OBJSCALE;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setScale(OBJSCALE, OBJSCALE);
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((vm.width / 2) - (timeBarStartWidth / 2), vm.height-110);
	std::cout << "Width: " << vm.width << "Height: " << vm.height<< std::endl;


	Time gameTotalTime;
	float timeRemaing = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaing;


	//bool for pausing the game
	bool paused = true;

	//draw some text
	int score = 0;
	Text messageText;
	Text scoreText;

	//choose a font
	Font font;
	font.loadFromFile("../fonts/KOMIKAP_.ttf");

	//setting the font
	messageText.setFont(font);
	scoreText.setFont(font);

	//assigning the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	//seting the text size
	messageText.setCharacterSize((int)(75 * ((float)vm.width / 1920)));
	scoreText.setCharacterSize((int)(60 * ((float)vm.width / 1920)));

	//choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	//position the text
	FloatRect textRect = messageText.getLocalBounds();
	//change the origin of the text message to the center of the textRect
	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);
	messageText.setPosition(vm.getDesktopMode().width/2.0f, vm.getDesktopMode().height/2.0f);
	scoreText.setPosition(20, 20);

	updateBranches(1);
	updateBranches(2);
	updateBranches(3);
	updateBranches(4);
	updateBranches(5);
	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (Mouse::isButtonPressed(Mouse::Right)) {
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			paused = false;

			//reset the time and the score
			score = 0;
			timeRemaing = 5;
		}
		
		//pause moving the obj before pressing enter
		if(!paused){
			//Measure time
			Time dt = clock.restart();// restart the clock

			//subtract from the remaining time
			timeRemaing -= dt.asSeconds();
			//size up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaing, timeBarHeight));


			if (timeRemaing <= 0.0f) {
				//pause the game
				paused = true;

				//change the message to be shown to the player
				messageText.setString("Out of time!!");
				
				//Reposition the text based on the new string
				textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);
				messageText.setPosition(vm.getDesktopMode().width / 2.0f, vm.getDesktopMode().height / 2.0f);
			}


									  //setup the bee
			moveSprite(300,200,20, beeActive, beeSpeed,200 , beeSprite, dt);
			//setup the cloud
			moveSprite(0,150,30, cloud1Active, cloud1Speed,10 , cloudSprite1, dt);
			moveSprite(0,200,40, cloud2Active, cloud2Speed, 25, cloudSprite2, dt);
			moveSprite(0,100,50, cloud3Active, cloud3Speed,5 , cloudSprite3, dt);

			// updating the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());
			//update the branch sprite
			for (int i = 0; i < NUM_BRANCHES; i++) {
				float height = i * 150 * OBJSCALE;
				if (branchPositions[i] == side::LEFT) {
					//move the branch to the left side
					branches[i].setPosition(610 * OBJSCALE, height);
					//Flip the sprite round the other way
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT) {
					//move the sprite to the right side
					branches[i].setPosition(1300 * OBJSCALE, height);
					//set the sprite rotation to normal
					branches[i].setRotation(0);
				} else {
					// hide the branch
					branches[i].setPosition(3000 * OBJSCALE, height);
				}
			}
		}

		window.clear();
		window.draw(spriteBackground);/* draws our game scene */

		// drawing the clouds
		window.draw(cloudSprite1);
		window.draw(cloudSprite2);
		window.draw(cloudSprite3);

		// drawing the branches
		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}

		// drawing the tree
		window.draw(treeSprite);

		//drawing the player
		window.draw(playerSprite);

		//drawing the axe
		window.draw(axeSprite);

		//drawing the log
		window.draw(logSprite);

		//drawing the rip
		window.draw(RIPSprite);

		// drawing the bee
		window.draw(beeSprite);
		
		//drawing the score
		window.draw(scoreText);
		
		//drawing the time bar
		window.draw(timeBar);

		if (paused) {
			//drawing the message
			window.draw(messageText);
		}

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

void updateBranches(int seed) {
	// move all the branches down one place
	for (int j = NUM_BRANCHES -1 ; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
		//(branchPositions[j - 1] == side::LEFT ? side::LEFT : (branchPositions[j - 1] == side::RIGHT ? side::RIGHT : side::NONE));
	}
	
	//spawn a new branch at position 0
	//Left right none
	srand((int)(time(0)) + seed);
	int r = (rand() % 5);
	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
}
