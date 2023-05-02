//
// Created by Jonathan Lehman on 4/11/23.
//
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <vector>
#include <tuple>
#include "Engine.hpp"
#include "GameObject.hpp"
#include "Managers/Input.hpp"
#include "Managers/ColliderManager.hpp"
#include "ComponentSystem/CameraFocusComponent.hpp"
#include "ComponentSystem/Component.hpp"
#include "ComponentSystem/ControllerComponent.hpp"
#include "ComponentSystem/PhysicsComponent.hpp"
#include "ComponentSystem/SpriteComponent.hpp"
#include "ComponentSystem/TileMapComponent.hpp"
#include "ComponentSystem/TransformComponent.hpp"
#include "ComponentSystem/CollectComponent.hpp"
#include "ComponentSystem/PatrolComponent.hpp"
#include "ComponentSystem/EnemyComponent.hpp"
#include "ComponentSystem/AnimatorComponent.hpp"
#include "TileMapEditor.hpp"
#include "SpriteEditor.hpp"

namespace py = pybind11;

PYBIND11_MODULE(StuartLittleEngine, m) {
    m.doc() = "The Stuart Little Engine.";

    py::class_<Engine>(m, "Engine")
            .def(py::init<>())
            .def("initGraphics", &Engine::InitializeGraphicsSubSystem)
            .def("shutDown", &Engine::Shutdown)
            .def("addGameObject", &Engine::AddGameObject)
            .def("input", &Engine::Input)
            .def("update", &Engine::Update)
            .def("render", &Engine::Render)
            .def("delay", &Engine::Delay);

    py::class_<GameObject>(m, "GameObject")
            .def(py::init<>())
            .def("addComponent", &GameObject::AddComponent);

    py::class_<Component>(m, "Component");

    py::class_<TileMapComponent, Component>(m, "TileMapComponent")
            .def(py::init<std::string, int, int, int, int, int, int>())
            .def(py::init<std::string>());

    py::class_<TransformComponent, Component>(m, "TransformComponent")
            .def(py::init<int, int>())
            .def("getX", &TransformComponent::GetX)
            .def("getY", &TransformComponent::GetY)
            .def("setX", &TransformComponent::SetX)
            .def("setY", &TransformComponent::SetY);

    py::class_<SpriteComponent, Component>(m, "SpriteComponent")
            .def(py::init<TransformComponent*, std::string, bool>())
            .def(py::init<std::string, TransformComponent*, bool>())
            .def("getColliderID", &SpriteComponent::GetColliderID)
            .def("setFlipped", &SpriteComponent::SetFlipped);

    py::class_<PhysicsComponent, Component>(m, "PhysicsComponent")
            .def(py::init<TransformComponent*, TileMapComponent*, bool, int>());

    py::class_<ControllerComponent, Component>(m, "ControllerComponent")
            .def(py::init<PhysicsComponent*>())
            .def("setVelocity", &ControllerComponent::SetVelocity)
            .def("getXVelocity", &ControllerComponent::GetXVelocity)
            .def("getYVelocity", &ControllerComponent::GetYVelocity)
            .def("isGrounded", &ControllerComponent::IsGrounded);

    py::class_<CameraFocusComponent, Component>(m, "CameraFocusComponent")
            .def(py::init<TransformComponent*, float, float, float, float>())
            .def("updateZoomBy", &CameraFocusComponent::UpdateZoomBy);

    py::class_<CollectComponent, Component>(m, "CollectComponent")
            .def(py::init<TransformComponent*, TransformComponent*, SpriteComponent*>());

    py::class_<PatrolComponent, Component>(m, "PatrolComponent")
            .def(py::init<int, int, TransformComponent*>());

    py::class_<EnemyComponent, Component>(m, "EnemyComponent")
            .def(py::init<TransformComponent*, TransformComponent*>());

    py::class_<AnimatorComponent, Component>(m, "AnimatorComponent")
            .def(py::init<>())
            .def("addSprite", &AnimatorComponent::AddSprite);

    py::class_<Input>(m, "Input")
            .def_static("getInstance", &Input::GetInstance)
            .def("isPressingKey", &Input::isPressingKey)
            .def("gotQuitInput", &Input::gotQuitInput);

    py::class_<ColliderManager>(m, "ColliderManager")
            .def_static("getInstance", &ColliderManager::GetInstance)
            .def("colliding", &ColliderManager::Colliding);
        
    py::class_<SpriteEditor>(m, "SpriteEditor")
            .def(py::init<>())
            .def("Start", &SpriteEditor::Start)
            .def("Shutdown", &SpriteEditor::Shutdown)
            .def("InitializeGraphicsSubSystem", &SpriteEditor::InitializeGraphicsSubSystem)
            .def("Input", &SpriteEditor::HandleInput)
            .def("CreateNewSprite", &SpriteEditor::CreateNewSprite)
            .def("SaveSprite", &SpriteEditor::SaveSprite)
            .def("LoadSprite", &SpriteEditor::LoadSprite)
            .def("Render", &SpriteEditor::Render)
            .def("SetCurrentFrame", &SpriteEditor::setCurrentFrame)
            .def("SetSpriteWidth", &SpriteEditor::setSpriteWidth)
            .def("SetSpriteHeight", &SpriteEditor::setSpriteHeight);

    py::class_<TileMapEditor>(m, "TileMapEditor")
            .def(py::init<>())
            .def("Start", &TileMapEditor::Start)
            .def("Shutdown", &TileMapEditor::Shutdown)
            .def("InitializeGraphicsSubSystem", &TileMapEditor::InitializeGraphicsSubSystem)
            .def("Input", &TileMapEditor::HandleInput)
            .def("CreateTileMap", &TileMapEditor::CreateTileMap)
            .def("SaveTileMap", &TileMapEditor::SaveTileMap)
            .def("LoadTileMap", &TileMapEditor::LoadTileMap)
            .def("Render", &TileMapEditor::Render)
            .def("SetCurrentType", &TileMapEditor::setCurrentType);
}
