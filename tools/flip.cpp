#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

//constants
constexpr int GRID_WIDTH = 40;
constexpr int GRID_HEIGHT = 40;

constexpr int TILE_TYPES = 10;
constexpr int TILE_WIDTH = 32;
constexpr int TILE_HEIGHT = 32;

constexpr int TOKEN_TYPES = 10;

constexpr int MAP_FORMAT = 20141004;

//copy-pasted functions
void loadMap(int grid[GRID_WIDTH][GRID_HEIGHT], int tokens[GRID_WIDTH][GRID_HEIGHT], std::string fname) {
	std::ifstream is(fname);

	if (!is.is_open()) {
		std::ostringstream err;
		err << "Failed to load file: " << fname << std::endl;
		throw(std::runtime_error(err.str()));
	}

	//check the version
	int format;
	is >> format;
	if (format != MAP_FORMAT) {
		std::ostringstream err;
		err << "Map file \'" << fname << "\' is an incorrect format, received " << format << ", expected " << MAP_FORMAT << std::endl;
		throw(std::runtime_error(err.str()));
	}

	//load the grid
	for (int j = 0; j < GRID_HEIGHT; ++j) {
		for (int i = 0; i < GRID_WIDTH; ++i) {
			is >> grid[i][j];
		}
	}

	//load the tokens
	for (int j = 0; j < GRID_HEIGHT; ++j) {
		for (int i = 0; i < GRID_WIDTH; ++i) {
			is >> tokens[i][j];
		}
	}

	is.close();
}

void saveMap(int grid[GRID_WIDTH][GRID_HEIGHT], int tokens[GRID_WIDTH][GRID_HEIGHT], std::string fname) {
	std::ofstream os(fname);

	if (!os.is_open()) {
		std::ostringstream err;
		err << "Failed to save file: " << fname << std::endl;
		throw(std::runtime_error(err.str()));
	}

	//save the format
	os << MAP_FORMAT << std::endl;

	//save the grid
	for (int j = 0; j < GRID_HEIGHT; ++j) {
		for (int i = 0; i < GRID_WIDTH; ++i) {
			os << grid[i][j] << " ";
		}
		os << std::endl;
	}

	os << std::endl;

	//save the tokens
	for (int j = 0; j < GRID_HEIGHT; ++j) {
		for (int i = 0; i < GRID_WIDTH; ++i) {
			os << tokens[i][j] << " ";
		}
		os << std::endl;
	}

	os.close();
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " [filename]" << std::endl;
	}

	int grid[GRID_WIDTH][GRID_HEIGHT];
	int tokens[GRID_WIDTH][GRID_HEIGHT];

	loadMap(grid, tokens, argv[1]);

	//flip
	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < i; ++j) {
			grid[i][j] = grid[j][i];
			tokens[i][j] = tokens[j][i];
		}
	}

	saveMap(grid, tokens, argv[1]);

	return 0;
}