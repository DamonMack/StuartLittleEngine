//
// Created by Jonathan Lehman on 4/6/23.
//

#include "Managers/Input.hpp"

Input& Input::GetInstance() {
    static Input* instance = new Input();
    return *instance;
}

void Input::handleInput() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYDOWN) {
            heldKeys.insert(SDL_GetKeyName(e.key.keysym.sym));
        }
        else if (e.type == SDL_KEYUP) {
            heldKeys.erase(SDL_GetKeyName(e.key.keysym.sym));
        }
        else if (e.type == SDL_QUIT) {
            quitInput = true;
        }
    }
}

bool Input::isPressingKey(std::string keyName) {
    return heldKeys.find(keyName) != heldKeys.end();
}

bool Input::gotQuitInput() {
    return quitInput;
}