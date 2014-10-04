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
#include "moba_prototype.hpp"

#include "config_utility.hpp"

#include <cstring>

//-------------------------
//Public access members
//-------------------------

MobaPrototype::MobaPrototype() {
	ConfigUtility& config = ConfigUtility::GetSingleton();

	gridTiles.LoadSurface(config["dir.graphics"] + "grid_tiles.bmp");
	gridTiles.SetClipW(32);
	gridTiles.SetClipH(32);

	tokenTiles.LoadSurface(config["dir.graphics"] + "tokens.bmp");
	tokenTiles.SetClipW(32);
	tokenTiles.SetClipH(32);

	//init the grid
	memset(grid, 0, sizeof(int) * GRID_WIDTH * GRID_HEIGHT);
	memset(tokens, 0, sizeof(int) * GRID_WIDTH * GRID_HEIGHT);

}

MobaPrototype::~MobaPrototype() {
	//
}

//-------------------------
//Frame loop
//-------------------------

void MobaPrototype::FrameStart() {
	//
}

void MobaPrototype::Update() {
	//
}

void MobaPrototype::FrameEnd() {
	//
}

void MobaPrototype::Render(SDL_Surface* const screen) {
	//draw the grid
	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < GRID_HEIGHT; ++j) {
			gridTiles.SetClipX(grid[i][j] * 32);
			gridTiles.DrawTo(screen, camera.position.x + i * TILE_WIDTH, camera.position.y + j * TILE_HEIGHT);
		}
	}

	//draw the tokens (0 = empty)
	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < GRID_HEIGHT; ++j) {
			if (tokens[i][j]) {
				tokenTiles.SetClipX((tokens[i][j] - 1) * 32);
				tokenTiles.DrawTo(screen, camera.position.x + i * TILE_WIDTH, camera.position.y + j * TILE_HEIGHT);
			}
		}
	}
}

//-------------------------
//Event handlers
//-------------------------

void MobaPrototype::MouseMotion(SDL_MouseMotionEvent const& motion) {
	//camera movement
	if (motion.state & SDL_BUTTON_RMASK) {
		camera.position.x += motion.xrel;
		camera.position.y += motion.yrel;
	}
}

void MobaPrototype::MouseButtonDown(SDL_MouseButtonEvent const& button) {
	//change the grid tiles
	if (keyState[SDLK_TAB]) {
		int i = (button.x - camera.position.x)  / TILE_WIDTH;
		int j = (button.y - camera.position.y)  / TILE_HEIGHT;

		grid[i][j] += 1;
		if (grid[i][j] >= TILE_TYPES) {
			grid[i][j] = 0;
		}
	}

	//change the tokens
	if (keyState[SDLK_LSHIFT] || keyState[SDLK_RSHIFT]) {
		int i = (button.x - camera.position.x)  / TILE_WIDTH;
		int j = (button.y - camera.position.y)  / TILE_HEIGHT;

		tokens[i][j] += 1;
		if (tokens[i][j] > TOKEN_TYPES) {
			tokens[i][j] = 0;
		}
	}
}

void MobaPrototype::MouseButtonUp(SDL_MouseButtonEvent const& button) {
	//
}

void MobaPrototype::KeyDown(SDL_KeyboardEvent const& key) {
	//hitkeys
	switch (key.keysym.sym) {
		case SDLK_ESCAPE:
			QuitEvent();
		break;
	}
}

void MobaPrototype::KeyUp(SDL_KeyboardEvent const& key) {
	//
}
