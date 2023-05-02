//
// Created by Jonathan Lehman on 4/17/23.
//

#include "ComponentSystem/AnimatorComponent.hpp"

AnimatorComponent::AnimatorComponent() { }

AnimatorComponent::~AnimatorComponent() { }

void AnimatorComponent::Update(double dt) {
    for (std::pair<SpriteComponent*, std::function<bool()>> sprite : sprites) {
        sprite.first->Update(dt);
    }
}

void AnimatorComponent::Render(SDL_Renderer *ren) {
    for (std::pair<SpriteComponent*, std::function<bool()>> sprite : sprites) {
        if (sprite.second()) {
            sprite.first->Render(ren);
            return;
        }
    }
}

void AnimatorComponent::AddSprite(SpriteComponent* sprite, std::function<bool()> condition) {
    sprites.push_back(std::pair<SpriteComponent*, std::function<bool()>>(sprite, condition));
}