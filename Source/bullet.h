#include <SFML/Graphics.hpp>

using namespace sf;
class Bullet
{
public:
	Texture Bullet_tex;
	Sprite Bullet_sprite;
	float Bullet_x, Bullet_y;
	Bullet(float X , float Y , int Var = 0)
	{
		if (Var == 0)
			Bullet_tex.loadFromFile("img/PNG/Lasers/laserRed01.png");
		else if (Var == 1) 
			Bullet_tex.loadFromFile("img/PNG/Lasers/laserRed11.png");
		else
			Bullet_tex.loadFromFile("img/PNG/Effects/fire15.png");

		Bullet_sprite.setTexture(Bullet_tex);
		Bullet_x = X;
		Bullet_y = Y;
		Bullet_sprite.setPosition(X+33.0, Y-47.0);
		if (Var == 0)
			Bullet_sprite.setScale(0.95, 0.95);
		else if(Var == 1)
			Bullet_sprite.setScale(0.55, 0.55);
		else 
			Bullet_sprite.setScale(0.95, 0.95);
	}
	
};