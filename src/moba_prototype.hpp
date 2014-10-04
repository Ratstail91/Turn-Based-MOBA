/* Copyright: (c) Kayne Ruse 2013, 2014
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
*/
#ifndef MOBAPROTOTYPE_HPP_
#define MOBAPROTOTYPE_HPP_

#include "base_scene.hpp"

#include "image.hpp"

#include <string>

//constants
constexpr int GRID_WIDTH = 40;
constexpr int GRID_HEIGHT = 40;

constexpr int TILE_TYPES = 10;
constexpr int TILE_WIDTH = 32;
constexpr int TILE_HEIGHT = 32;

constexpr int TOKEN_TYPES = 10;

constexpr int MAP_FORMAT = 20141004;

//utility structures
struct Camera {
	struct {
		int x = 0, y = 0;
	}position;
};

struct Cursor {
	enum Mode {
		TERRAIN = 1,
		STRUCTURES = 2,
	}mode;

	int selection = 0;
};

class MobaPrototype : public BaseScene {
public:
	//Public access members
	MobaPrototype();
	~MobaPrototype();

protected:
	//Frame loop
	void FrameStart();
	void Update();
	void FrameEnd();
	void Render(SDL_Surface* const);

	//Event handlers
	void MouseMotion(SDL_MouseMotionEvent const&);
	void MouseButtonDown(SDL_MouseButtonEvent const&);
	void MouseButtonUp(SDL_MouseButtonEvent const&);
	void KeyDown(SDL_KeyboardEvent const&);
	void KeyUp(SDL_KeyboardEvent const&);

	//utility functions
	void LoadMap(std::string fname);
	void SaveMap(std::string fname);

	//members
	Uint8* keyState = SDL_GetKeyState(nullptr); //shortcut

	Image gridTiles;
	Image tokenTiles;

	int grid[GRID_WIDTH][GRID_HEIGHT];
	int tokens[GRID_WIDTH][GRID_HEIGHT];

	Camera camera;
	Cursor cursor;
};

#endif
