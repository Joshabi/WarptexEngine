#pragma once

// Includes:
#include <type_traits>
#include <vector>
#include "EngineScene.h"
#include "Gameobject.h"
#include "Projectile.h"

/// <summary>
/// Generic Object Pool that allows for the creation of a pool of objects of type T.
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class ObjectPool {
	static_assert(std::is_base_of<GameObject, T>::value, "T must inherit from GameObject");
public:
	/// <summary>
	/// Initializes a pool with a given initial size and scene.
	/// </summary>
	/// <param name="initialSize">- Quantity of starting objects</param>
	/// <param name="scene">- Scene for pool to reside in</param>
	ObjectPool(int initialSize, Scene* scene) : scene(scene) {
		for (int i = 0; i < initialSize; i++) {
			T* gameObject = new T(scene);
			gameObject->SetActive(false);
			objectPool.push_back(gameObject);
		}
	}

	/// <summary>
	/// Retrieves an object from the pool. If no deactivated objects exist, a new object is created.
	/// </summary>
	/// <returns></returns>
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

	/// <summary>
	/// Returns the object pool
	/// </summary>
	/// <returns></returns>
	std::vector<T*> GetObjectPool() const {
		return objectPool;
	}

	/// <summary>
	/// Deactivates an object and removes it from the scene.
	/// </summary>
	/// <param name="gameObject"></param>
	void ReleaseObject(T* gameObject) {
		gameObject->SetActive(false);
		scene->DeregisterGameObject(gameObject);
	}

	/// <summary>
	/// Deletes the pool of objects
	/// </summary>
	~ObjectPool() {
		for (T* gameObject : objectPool) {
			delete gameObject;
		}
	}

private:
	std::vector<T*> objectPool;
	Scene* scene;
};