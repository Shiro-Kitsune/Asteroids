#pragma once

#include "RenderingComponent.h";
#include "PhysicsComponent.h";

class Particle
{
public:
	Particle();
private:
	RenderingComponent renderingComponent;
	PhysicsComponent physicsComponent;
};