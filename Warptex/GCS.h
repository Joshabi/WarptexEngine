#pragma once

// Includes:
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

// Forward Declarations:
class Component;
class GObject;
class GameObjectRegister;

// Typedefs:
using ComponentID = std::size_t;
inline ComponentID GetComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

// Returns a unique ID for each component type:
template <typename T> inline ComponentID GetComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxUniqueComponents = 32;
using ComponentBitSet = std::bitset<maxUniqueComponents>;
using ComponentArray = std::array<Component*, maxUniqueComponents>;

/// <summary>
/// Each component that can be added to a GameObject
/// </summary>
class Component {
public:
	GObject* parentObject;

	virtual void Init() {}
	virtual void Update() {}
	virtual void Input() {}
	virtual void Render(SDL_Renderer* renderer) {}

	virtual ~Component() {}
};

class GObject {
public:
	void Update() {
		for (auto& c : components) c->Update();
		for (auto& c : components) c->Input();
		for (auto& c : components) c->Render();
	}

	void SetRenderer(SDL_Renderer* renderer) { this->renderer = renderer; }
	void Render() {}
	bool IsActive() const { return isActive; }
	void Destroy() { isActive = false; }

	template <typename T> bool HasComponent() const {
		return compBitSet[GetComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->parentObject = this;
		std::unique_ptr<Component> cPtr { c };
		components.emplace_back(std::move(cPtr));

		compArray[GetComponentTypeID<T>()] = c;
		compBitSet[GetComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template<typename T> T& GetComponent() const {
		auto ptr(compArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

protected:
	SDL_Renderer* renderer;
	bool isActive = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray compArray;
	ComponentBitSet compBitSet;
};

class GameObjectRegister {
protected:
	std::vector<std::unique_ptr<GObject>> objects;

public:
	void Update() {
		for (auto& o : objects) o->Update();
	}

	void Render() {
		for (auto& o : objects) o->Render();
	}

	GObject& AddObject(SDL_Renderer* renderer) {
		GObject* o = new GObject();
		o->SetRenderer(renderer);
		std::unique_ptr<GObject> uPtr{ o };
		objects.emplace_back(std::move(uPtr));
		return *o;
	}

	void Refresh() {
		objects.erase(std::remove_if(std::begin(objects), std::end(objects),
			[](const std::unique_ptr<GObject>& mGameObject) {
				return !mGameObject->IsActive();
			}),
			std::end(objects));
	}
};