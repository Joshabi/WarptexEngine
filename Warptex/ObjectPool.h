#pragma once

// ************************* //
//  Generic Object Pooling   //
// ************************* //

// Includes:
#include <type_traits>
#include <vector>
#include "EngineScene.h"
#include "Gameobject.h"
#include "Projectile.h"

template<typename T>
class ObjectPool {
	static_assert(std::is_base_of<GameObject, T>::value, "T must inherit from GameObject");
public:
	ObjectPool(int initialSize, Scene* scene) : scene(scene) {
		for (int i = 0; i < initialSize; i++) {
			T* gameObject = new T(scene);
			gameObject->SetActive(false);
			objectPool.push_back(gameObject);
		}
	}

	T* GetObject() {
		for (T* gameObject : objectPool) {
			if (!gameObject->IsActive()) {
				gameObject->SetActive(true);
				scene->RegisterGameObject(gameObject);
				return gameObject;
			}
		}

		// If no deactivated objects exist...
		T* newGameObject = new T(scene);
		newGameObject->SetActive(true);
		scene->RegisterGameObject(newGameObject);
		objectPool.push_back(newGameObject);

		return newGameObject;
	}

	std::vector<T*> GetObjectPool() const {
		return objectPool;
	}

	void ReleaseObject(T* gameObject) {
		gameObject->SetActive(false);
		scene->DeregisterGameObject(gameObject);
	}

	~ObjectPool() {
		for (T* gameObject : objectPool) {
			delete gameObject;
		}
	}

private:
	std::vector<T*> objectPool;
	Scene* scene;
};