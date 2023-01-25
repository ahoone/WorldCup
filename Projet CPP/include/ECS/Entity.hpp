#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;

class Entity;

//*****************
//*** COMPONENT ***
//*****************

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> 
inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{

public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}

private:


};

//**************
//*** ENTITY ***
//**************

class Entity
{

public:

	void update();
	void draw();
	bool isAlive() const {return _alive; }
	void destroy() {_alive = false; }

	template <typename T> bool hasComponent() const {return _componentBitSet[getComponentTypeID<T>]; }

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr {c};
		_components.emplace_back(std::move(uPtr));

		_componentArray[getComponentTypeID<T>()] = c;
		_componentBitSet[getComponentTypeID<T>()] = true;

		c->init();

		return *c;
	}

	template <typename T>
	T& getComponent() const
	{
		auto ptr(_componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

private:

	bool _alive = true;
	std::vector<std::unique_ptr<Component>> _components;

	ComponentArray _componentArray;
	ComponentBitSet _componentBitSet;

};

inline void Entity::update()
{
	for(auto& c : _components)
		c->update();
}

inline void Entity::draw()
{
	for(auto& c : _components)
		c->draw();
}

//***************
//*** MANAGER ***
//***************

class Manager
{

public:

	void update();
	void draw();
	void actualize();

	Entity& addEntity();

private:

	std::vector<std::unique_ptr<Entity>> _entities;

};

inline void Manager::update()
{
	for(auto& e : _entities)
		e->update();
}

inline void Manager::draw()
{
	for(auto& e : _entities)
		e->draw();
}

inline void Manager::actualize()
{
	_entities.erase(std::remove_if(std::begin(_entities), std::end(_entities), 
		[](const std::unique_ptr<Entity> &mEntity) {return !mEntity->isAlive(); }), 
		std::end(_entities));
}

inline Entity& Manager::addEntity()
{
	Entity* e = new Entity();
	std::unique_ptr<Entity> uPtr {e};
	_entities.emplace_back(std::move(uPtr));
	return *e;
}










