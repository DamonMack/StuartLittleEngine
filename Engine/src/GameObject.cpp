#include "GameObject.hpp"

GameObject::GameObject() { }

GameObject::~GameObject() { }

void GameObject::Update(double dt) {
    for (Component* c: m_components) {
        c->Update(dt);
    }
}

void GameObject::Render(SDL_Renderer *ren) {
    for (Component* c: m_components) {
        c->Render(ren);
    }
}

void GameObject::AddComponent(Component* c) {
    m_components.push_back(c);
}

void GameObject::DeleteComponents() {
    for (Component *c : m_components) {
        if (nullptr != c) {
            delete c;
        }
    }
}