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

#include "Utility/Color.h"
#include "Utility/Vector2D.h"
#include "Utility/Matrix3x3.h"
#include "Utility/LineSegment.h"

#include "GameEngine.h"
#include "Entity.h"
#include "EntityManager.h"
#include "EntityFactory.h"
#include "EventManager.h"

#include "States/GameState.h"
#include "States/StartMenuState.h"
#include "States/IntroGameState.h"
#include "States/SinglePlayerGameState.h"
#include "States/GameMenuState.h"
#include "States/LoseState.h"

#include "Events/Event.h"
#include "Events/Collision.h"

#include "Components/Component.h"
#include "Components/AsteroidComponent.h"
#include "Components/BoundingBox2D.h"
#include "Components/BoundingCircle2D.h"
#include "Components/BulletComponent.h"
#include "Components/EnemyComponent.h"
#include "Components/EnemyShipComponent.h"
#include "Components/ExpireComponent.h"
#include "Components/ExplodableComponent.h"
#include "Components/HealthComponent.h"
#include "Components/ItemComponent.h"
#include "Components/ParentComponent.h"
#include "Components/ParticleEmmiter.h"
#include "Components/PhysicsComponent.h"
#include "Components/PlayerComponent.h"
#include "Components/PlayerInputComponent.h"
#include "Components/RamShipComponent.h"
#include "RenderingComponent.h"
#include "Components/ShieldComponent.h"
#include "Components/ShieldUserComponent.h"
#include "Components/ShooterComponent.h"
#include "Components/UIButtonComponent.h"
#include "Components/UITextComponent.h"

#include "Systems/System.h"
#include "Systems/AsteroidSystem.h"
#include "Systems/BulletSystem.h"
#include "Systems/CollisionDetectionSystem.h"
#include "Systems/CollisionRemoverSystem.h"
#include "Systems/EnemyShipSystem.h"
#include "Systems/EnemySpawnerSystem.h"
#include "Systems/ExpireSystem.h"
#include "Systems/HealthSystem.h"
#include "Systems/ItemSystem.h"
#include "Systems/ParentSystem.h"
#include "Systems/ParticleSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/PlayerSystem.h"
#include "Systems/RamShipSystem.h"
#include "Systems/Renderer.h"
#include "Systems/ShieldSystem.h"
#include "Systems/ShieldUserSystem.h"
#include "Systems/ShootingSystem.h"
#include "Systems/TextUpdateSystem.h"
#include "Systems/UIButtonSystem.h"

#include "App/app.h"
#include "Utilities.h"
