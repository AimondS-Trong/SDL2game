#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "RenderWindow.h"
#include "Entity.h"

using namespace std;

RenderWindow::RenderWindow(const char* p_title, const char* iconPath, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN); //khai báo window

	if (window == NULL) //check window có khai báo thành công không
	{
		cout << "Window failed to init. Error: " << SDL_GetError() << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //khai báo renderer
	if (renderer == NULL) // Kiểm tra renderer có được tạo thành công không
	{
	    cout << "Renderer failed to init. Error: " << SDL_GetError() << endl;
	}
	// Lấy img icon và check xem icon có khai báo thành công không
	SDL_Surface* icon = IMG_Load(iconPath);
	if (!icon)
	{
		cout << "Failed to load icon. Error: " << SDL_GetError() << endl;
		return;
	}
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);
}

// Lấy img cho các texture
SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		cout << "Failed to load texture. Error: " << SDL_GetError() << endl;

	return texture;
}

// Hàm Destroywindow
void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

// Hàm RenderClear
void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

// Hàm vẽ entity
void RenderWindow::render(Entity& p_entity)
{
	// Xác định kích thước ảnh gốc
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	// Xác định vùng hiển thị
	SDL_Rect dst;
	dst.x = p_entity.getPos().x + (p_entity.getCurrentFrame().w - p_entity.getCurrentFrame().w*p_entity.getScale().x)/2;
	dst.y = p_entity.getPos().y + (p_entity.getCurrentFrame().h - p_entity.getCurrentFrame().h*p_entity.getScale().y)/2;
	dst.w = p_entity.getCurrentFrame().w*p_entity.getScale().x;
	dst.h = p_entity.getCurrentFrame().h*p_entity.getScale().y;

	// Hiển thị
	SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, p_entity.getAngle(), 0, SDL_FLIP_NONE);
}

// Hiển thị ảnh tại x, y theo kích thước gốc
void RenderWindow::render(int x, int y, SDL_Texture* p_tex)
{
	SDL_Rect src; 
	src.x = 0;
	src. y = 0;
	src.w;
	src.h;

	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

// Hiển thị chữ tại x, y
void RenderWindow::render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor); // Tạo surface chứa văn bản
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); // Chuyển văn bản thành texture

		// Hiển thị văn bản
		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = surfaceMessage->w;
		src.h = surfaceMessage->h; 

		SDL_Rect dst;
		dst.x = p_x;
		dst.y = p_y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
	 	SDL_DestroyTexture(message);
}

// Hiển thị văn bản ở giữa màn hình
void RenderWindow::renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = surfaceMessage->w;
		src.h = surfaceMessage->h; 

		// Do sử dụng cố định ở màn 640x480 _ em chỉ sử dụng tất cả texture ở định dạng gốc để không bị lệch hiển thị của các texture khác nhau
		SDL_Rect dst;
		dst.x = 640/2 - src.w/2 + p_x;
		dst.y = 480/2 - src.h/2 + p_y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(message);
}

// Cập nhật frame
void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}
