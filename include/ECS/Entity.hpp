#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;

class Entity;

class Manager;

//*****************
//*** COMPONENT ***
//*****************

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> 
inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

//Sert de base à tous les Component
class Component
{

public:
	Entity* entity;

	//Fonctions virtuelles car
	//redéfinies par chaque classe fille
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

	Entity(Manager& mManager) : _manager(mManager) {}

	//Les entity d'un même groupe sont
	//réunies pour qu'on puisse itérer
	//dessus et faire les updates...
	bool hasGroup(Group mGroup) {return _groupBitSet[mGroup]; }
	void addGroup(Group mGroup);
	void delGroup(Group mGroup) {_groupBitSet[mGroup] = false; }

	template <typename T> 
	bool hasComponent() const {return _componentBitSet[getComponentTypeID<T>()]; }

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

	Manager& _manager;

	//Sert à stocker les données des
	//components possédés par l'entity.
	ComponentArray _componentArray;
	ComponentBitSet _componentBitSet;
	GroupBitSet _groupBitSet;

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

	void AddToGroup(Entity* mEntity, Group mGroup);
	std::vector<Entity*>& getGroup(Group mGroup);

	Entity& addEntity();

private:

	std::vector<std::unique_ptr<Entity>> _entities;
	std::array<std::vector<Entity*>, maxGroups> _groupedEntities;

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
	for(auto i(0u); i<maxGroups; i++)
	{
		auto& v(_groupedEntities[i]);
		v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
			{return !mEntity->isAlive() || !mEntity->hasGroup(i); }),
			std::end(v));
	}

	_entities.erase(std::remove_if(std::begin(_entities), std::end(_entities), 
		[](const std::unique_ptr<Entity> &mEntity) {return !mEntity->isAlive(); }), 
		std::end(_entities));
}

inline void Manager::AddToGroup(Entity* mEntity, Group mGroup)
{
	_groupedEntities[mGroup].emplace_back(mEntity);
}

inline std::vector<Entity*>& Manager::getGroup(Group mGroup)
{
	return _groupedEntities[mGroup];
}

inline Entity& Manager::addEntity()
{
	Entity* e = new Entity(*this);
	std::unique_ptr<Entity> uPtr {e};
	_entities.emplace_back(std::move(uPtr));
	return *e;
}

//Must be defined here, if no, class Manager is considered incomple.
inline void Entity::addGroup(Group mGroup)
{
	_groupBitSet[mGroup] = true;
	_manager.AddToGroup(this, mGroup);
}