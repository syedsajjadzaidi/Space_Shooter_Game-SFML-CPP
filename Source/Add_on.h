#include <SFML/Graphics.hpp>
#include <cstdlib>
using namespace sf;
class AddOn
{
public:
	Texture AddOn_tex; bool LivesFlag, DangerFlag, FireFlag, PowerUpFlag;
	Sprite AddOn_sprite;
	float AddOn_x, AddOn_y;
	virtual void fall() = 0;
	virtual bool strikeCheck(float X , float Y) = 0;

};
class Lives :public AddOn
{
public:
	Lives()
	{
		AddOn_x = 20 + rand() % 620;
		AddOn_y = 100; 
		AddOn_tex.loadFromFile("img/PNG/Power-ups/bolt_gold.png");
		AddOn_sprite.setTexture(AddOn_tex);
		AddOn_sprite.setPosition(AddOn_x, AddOn_y);
		AddOn_sprite.setScale(0.95, 0.95);
		LivesFlag = true; DangerFlag = false; FireFlag = false; PowerUpFlag = false;
	}
	void fall()
	{
		AddOn_y += 0.2;  
		AddOn_sprite.setPosition(AddOn_x, AddOn_y);
	}
	bool strikeCheck(float X, float Y)
	{
		if (X + 50 >= AddOn_x && X - 20 <= AddOn_x && Y + 20 >= AddOn_y && Y - 20 <= AddOn_y)
			return true;
		else
			return false;
	}

};
class Danger :public AddOn
{
public:
	Danger()
	{
		AddOn_x = 20 + rand() % 620;
		AddOn_y = 100; 
		AddOn_tex.loadFromFile("img/PNG/Lasers/LaserRed09.png");
		AddOn_sprite.setTexture(AddOn_tex);
		AddOn_sprite.setPosition(AddOn_x, AddOn_y);
		AddOn_sprite.setScale(0.95, 0.95);
		LivesFlag = false; DangerFlag = true; FireFlag = false; PowerUpFlag= false;
	}
	void fall()
	{
		AddOn_y += 0.2;  
		AddOn_sprite.setPosition(AddOn_x, AddOn_y);
	}
	bool strikeCheck(float X, float Y)
	{
		if (X + 50 >= AddOn_x && X - 20 <= AddOn_x && Y + 20 >= AddOn_y && Y - 20 <= AddOn_y)
			return true;
		else
			return false;
	}
};
class PowerUp : public AddOn
{
public:
	PowerUp()
	{
		AddOn_x = 20 + rand() % 620;
		AddOn_y = 100; 
		AddOn_tex.loadFromFile("img/PNG/Power-ups/pill_yellow.png");
		AddOn_sprite.setTexture(AddOn_tex);
		AddOn_sprite.setPosition(AddOn_x, AddOn_y);
		AddOn_sprite.setScale(0.95, 0.95);
		LivesFlag = false; DangerFlag = false; FireFlag = false; PowerUpFlag = true;
	}
	void fall()
	{
		AddOn_y+= 0.2; 
		AddOn_sprite.setPosition(AddOn_x, AddOn_y);
	}
	bool strikeCheck(float X, float Y)
	{
		if (X + 50 >= AddOn_x && X - 20 <= AddOn_x && Y + 20 >= AddOn_y && Y - 20 <= AddOn_y)
			return true;
		else
			return false;
	}
};
class FireAddOn : public AddOn
{
public:
	FireAddOn()
	{
		AddOn_x = 20 + rand() % 620;
		AddOn_y = 100; 
		AddOn_tex.loadFromFile("img/PNG/Power-ups/things_gold.png");
		AddOn_sprite.setTexture(AddOn_tex);
		AddOn_sprite.setPosition(AddOn_x, AddOn_y);
		AddOn_sprite.setScale(0.95, 0.95);
		LivesFlag = false; DangerFlag = false; FireFlag = true; PowerUpFlag = false;
	}
	void fall()
	{
		AddOn_y += 0.2;
		AddOn_sprite.setPosition(AddOn_x, AddOn_y);
	}
	bool strikeCheck(float X, float Y)
	{
		if (X + 50 >= AddOn_x && X - 20 <= AddOn_x && Y + 20 >= AddOn_y && Y - 20 <= AddOn_y)
			return true;
		else
			return false;
	}
};