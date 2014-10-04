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

//-------------------------
//Public access members
//-------------------------

MobaPrototype::MobaPrototype() {
	ConfigUtility& config = ConfigUtility::GetSingleton();
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
	//
}

//-------------------------
//Event handlers
//-------------------------

void MobaPrototype::MouseMotion(SDL_MouseMotionEvent const& motion) {
	//
}

void MobaPrototype::MouseButtonDown(SDL_MouseButtonEvent const& button) {
	//
}

void MobaPrototype::MouseButtonUp(SDL_MouseButtonEvent const& button) {
	//
}

void MobaPrototype::KeyDown(SDL_KeyboardEvent const& key) {
	//
}

void MobaPrototype::KeyUp(SDL_KeyboardEvent const& key) {
	//
}
