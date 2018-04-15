// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include <memory>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string> 
#include <list>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <array>
#include <random>
#include <chrono>
#include <typeindex>

#include "Color.h"
#include "Vector2D.h"
#include "Matrix3x3.h"
#include "LineSegment.h"

#include "GameEngine.h"
#include "Entity.h"
#include "EntityManager.h"
#include "EntityFactory.h"
#include "EventManager.h"

#include "GameState.h"
#include "StartMenuState.h"
#include "IntroGameState.h"
#include "SinglePlayerGameState.h"
#include "GameMenuState.h"
#include "LoseState.h"

#include "Event.h"
#include "Collision.h"

#include "Component.h"
#include "AsteroidComponent.h"
#include "BoundingBox2D.h"
#include "BoundingCircle2D.h"
#include "BulletComponent.h"
#include "EnemyComponent.h"
#include "EnemyShipComponent.h"
#include "ExpireComponent.h"
#include "ExplodableComponent.h"
#include "HealthComponent.h"
#include "ItemComponent.h"
#include "ParentComponent.h"
#include "ParticleEmmiter.h"
#include "PhysicsComponent.h"
#include "PlayerComponent.h"
#include "PlayerInputComponent.h"
#include "RamShipComponent.h"
#include "RenderingComponent.h"
#include "ShieldComponent.h"
#include "ShieldUserComponent.h"
#include "ShooterComponent.h"
#include "UIButtonComponent.h"
#include "UITextComponent.h"

#include "systems/System.h"
#include "systems/AsteroidSystem.h"
#include "BulletSystem.h"
#include "CollisionDetectionSystem.h"
#include "CollisionRemoverSystem.h"
#include "EnemyShipSystem.h"
#include "EnemySpawnerSystem.h"
#include "ExpireSystem.h"
#include "HealthSystem.h"
#include "ItemSystem.h"
#include "ParentSystem.h"
#include "ParticleSystem.h"
#include "PhysicsSystem.h"
#include "PlayerSystem.h"
#include "RamShipSystem.h"
#include "Renderer.h"
#include "ShieldSystem.h"
#include "ShieldUserSystem.h"
#include "ShootingSystem.h"
#include "TextUpdateSystem.h"
#include "UIButtonSystem.h"

#include "App/app.h"
#include "Utilities.h"