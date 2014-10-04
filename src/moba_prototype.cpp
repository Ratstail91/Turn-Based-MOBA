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
#include <fstream>
#include <stdexcept>
#include <sstream>

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

	//
	try {
		LoadMap(ConfigUtility::GetSingleton()["dir.maps"] + "tmp.txt");
	}
	catch(...) {
		//EMPTY: Ignore this exception if there's no temp file
	}
}

MobaPrototype::~MobaPrototype() {
	//
	SaveMap(ConfigUtility::GetSingleton()["dir.maps"] + "tmp.txt");
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
	//placement
	if (motion.state & SDL_BUTTON_LMASK) {
		//BUGFIX: Out of bounds check
		if (motion.x < camera.position.x ||
			motion.y < camera.position.y ||
			motion.x >= camera.position.x + TILE_WIDTH * GRID_WIDTH ||
			motion.y >= camera.position.y + TILE_HEIGHT * GRID_HEIGHT
			)
		{
			return;
		}

		int i = (motion.x - camera.position.x)  / TILE_WIDTH;
		int j = (motion.y - camera.position.y)  / TILE_HEIGHT;

		//NOTE: duplicate code from MouseButtonDown()
		switch(cursor.mode) {
			case Cursor::Mode::TERRAIN:
				grid[i][j] = cursor.selection;
			break;

			case Cursor::Mode::STRUCTURES:
				tokens[i][j] = cursor.selection;
			break;
		}
	}

	//camera movement
	if (motion.state & SDL_BUTTON_RMASK) {
		camera.position.x += motion.xrel;
		camera.position.y += motion.yrel;
	}
}

void MobaPrototype::MouseButtonDown(SDL_MouseButtonEvent const& button) {
	if (button.button == SDL_BUTTON_LEFT) {
		//BUGFIX: Out of bounds check
		if (button.x < camera.position.x ||
			button.y < camera.position.y ||
			button.x >= camera.position.x + TILE_WIDTH * GRID_WIDTH ||
			button.y >= camera.position.y + TILE_HEIGHT * GRID_HEIGHT
			)
		{
			return;
		}

		int i = (button.x - camera.position.x)  / TILE_WIDTH;
		int j = (button.y - camera.position.y)  / TILE_HEIGHT;

		switch(cursor.mode) {
			case Cursor::Mode::TERRAIN:
				grid[i][j] = cursor.selection;
			break;

			case Cursor::Mode::STRUCTURES:
				tokens[i][j] = cursor.selection;
			break;
		}
	}
}

void MobaPrototype::MouseButtonUp(SDL_MouseButtonEvent const& button) {
	//
}

void MobaPrototype::KeyDown(SDL_KeyboardEvent const& key) {
	//control key: hotkeys
	if (key.keysym.mod & KMOD_CTRL) {
		switch(key.keysym.sym) {
			case SDLK_l:
				LoadMap(ConfigUtility::GetSingleton()["dir.maps"] + ConfigUtility::GetSingleton()["map"]);
			break;

			case SDLK_s:
				SaveMap(ConfigUtility::GetSingleton()["dir.maps"] + ConfigUtility::GetSingleton()["map"]);
			break;

			case SDLK_n:
				//clear the map
				memset(grid, 0, sizeof(int) * GRID_WIDTH * GRID_HEIGHT);
				memset(tokens, 0, sizeof(int) * GRID_WIDTH * GRID_HEIGHT);
			break;

			case SDLK_p:
				//take a screenshot
				SDL_SaveBMP(GetScreen(), (ConfigUtility::GetSingleton()["dir.screenshots"] + "screen.bmp").c_str());
			break;
		}

		return;
	}

	//numberical input
	if (key.keysym.sym >=  '0' && key.keysym.sym <= '9') {
		//shift key: terrain control
		if (key.keysym.mod & KMOD_SHIFT) {
			cursor.mode = Cursor::Mode::TERRAIN;
			cursor.selection = key.keysym.sym - '0';
		}
		//no shift key: structure control
		else {
			cursor.mode = Cursor::Mode::STRUCTURES;
			cursor.selection = key.keysym.sym - '0' + 1;
		}

		return;
	}

	//default hotkeys
	switch (key.keysym.sym) {
		case SDLK_ESCAPE:
			QuitEvent();
		break;

		//NOTE: clear the structures
		case SDLK_SPACE:
			cursor.mode = Cursor::Mode::STRUCTURES;
			cursor.selection = key.keysym.sym - '0' + 1;
		break;
	}
}

void MobaPrototype::KeyUp(SDL_KeyboardEvent const& key) {
	//
}

//-------------------------
//Event handlers
//-------------------------

void MobaPrototype::LoadMap(std::string fname) {
	std::ifstream is(fname);

	if (!is.is_open()) {
		std::ostringstream err;
		err << "Failed to load file: " << fname << std::endl;
		throw(std::runtime_error(err.str()));
	}

	//load the grid
	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < GRID_HEIGHT; ++j) {
			is >> grid[i][j];
		}
	}

	//load the tokens
	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < GRID_HEIGHT; ++j) {
			is >> tokens[i][j];
		}
	}

	is.close();
}

void MobaPrototype::SaveMap(std::string fname) {
	std::ofstream os(fname);

	if (!os.is_open()) {
		std::ostringstream err;
		err << "Failed to save file: " << fname << std::endl;
		throw(std::runtime_error(err.str()));
	}

	//save the grid
	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < GRID_HEIGHT; ++j) {
			os << grid[i][j] << " ";
		}
		os << std::endl;
	}

	os << std::endl;

	//save the tokens
	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < GRID_HEIGHT; ++j) {
			os << tokens[i][j] << " ";
		}
		os << std::endl;
	}

	os.close();
}