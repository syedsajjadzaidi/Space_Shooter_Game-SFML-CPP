#include <SFML/Graphics.hpp>
using namespace sf;
class Animation
{
public:
	Sprite Explosion; float Animation_X; float Animation_Y;
	Texture ExplosionTexture;
	Animation(float X, float Y)
	{
		ExplosionTexture.loadFromFile("img/PNG/Effects/shield3.png");
		Explosion.setTexture(ExplosionTexture);
		Explosion.setScale(0.85, 0.85);
		Explosion.setColor(Color::White);
		Animation_X = X-20; Animation_Y = Y-20;
		Explosion.setPosition(X, Y);
	}
	void move()
	{
		Animation_Y -= 0.1;
		Explosion.setPosition(Animation_X, Animation_Y);
	}
};
class LevelUp
{
public:
	Sprite Background; float levelUp_X; float levelUp_Y;
	Texture BackgroundTexture;
	LevelUp(float X = 680 , float Y = 700 , int x = 0)
	{
		if(x==0)
		BackgroundTexture.loadFromFile("img/PNG/playerShip2_orange.png");
		if(x==1)
		BackgroundTexture.loadFromFile("img/PNG/playerShip2_red.png");
		if(x==2)
		BackgroundTexture.loadFromFile("img/PNG/playerShip2_blue.png");
		if(x==3)
		BackgroundTexture.loadFromFile("img/PNG/playerShip2_green.png");
		Background.setTexture(BackgroundTexture);
		Background.setScale(0.85, 0.85);
		levelUp_X = X; levelUp_Y = Y;
	}
};
class MonsterPNG
{
public:
	Sprite Explosion; float Animation_X; float Animation_Y;
	Texture ExplosionTexture;
	MonsterPNG()
	{
		ExplosionTexture.loadFromFile("img/caution.png");
		Explosion.setTexture(ExplosionTexture);
		Explosion.setScale(0.7, 0.7);
		Animation_X = 0; Animation_Y = 350;
		Explosion.setPosition(0,0);
	}
};