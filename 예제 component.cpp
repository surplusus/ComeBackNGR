#include "stdafx.h"
class GameObject;
class World;
class Graphics;

//------------Component Interface---------------//
class InputComponent
{
public:
	virtual ~InputComponent() {}
	virtual void Update(GameObject& obj) = 0;
};

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {}
	virtual void Update(GameObject& obj, World& world) = 0;
};

class GraphicsComponent
{
public:
	~GraphicsComponent() {}
	virtual void Update(GameObject& obj, Graphics& graphics) = 0;
};
//------------Client Interface---------------//
class GameObject
{
public:
	int velocity;
	int x, y;

	GameObject(InputComponent* input, 
		PhysicsComponent* physics,
		GraphicsComponent* graphics) 
		: input_() , physics_(physics), graphics_(graphics){}

	void Update(World& world, Graphics& graphics) {
		input_->Update(*this);
		physics_->Update(*this, world);
		graphics_->Update(*this, graphics);
	}

private:
	InputComponent* input_;
	PhysicsComponent* physics_;
	GraphicsComponent* graphics_;
};