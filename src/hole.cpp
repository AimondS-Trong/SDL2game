#include "Hole.h"
#include "Entity.h"
#include "Math.h"
#include <SDL2/SDL.h>

// Kế thừa class của Entity và lưu vị trí và hình ảnh của hole
Hole::Hole(Vector2f p_pos, SDL_Texture* p_tex)
:Entity(p_pos, p_tex)
{
}
