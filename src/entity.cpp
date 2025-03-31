#include "Entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex) // Khởi tạo lớp entity
:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

// Khai báo texture theo entity
SDL_Texture* Entity::getTex()
{
	return tex;
}

// Hàm cập nhật (cho các lớp kế thừa)
void Entity::update(double deltaTime)
{

}

// Hàm thiết lập vị trí (cho các lớp kế thừa)
void Entity::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

// Hàm thiết lặp góc quay (Cho ball)
void Entity::setAngle(float p_angle)
{
	angle = p_angle;
}

// Hàm thiết lập tỉ lệ (cho các lớp kế thừa)
void Entity::setScale(float w, float h)
{
	scale.x = w;
	scale.y = h;
}

// Hàm lấy kích thước vị trí texture
SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}
