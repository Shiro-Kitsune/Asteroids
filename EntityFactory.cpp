#include "stdafx.h"

EntityFactory::EntityFactory()
{
	m_nextId = 1;
}

Entity EntityFactory::CreatePlayer(int accelerateKeyCode, int shootKeyCode, int rotateLeftKeyCode, int rotateRightKeyCode, int shieldKeyCode, const std::string& name)
{
	Entity entity (GenerateId(), name, Vector2D(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2), 0.0f);
	entity.AddComponent(std::make_unique<PhysicsComponent>(Vector2D(0.0f, 0.0f), Vector2D(0.0f, 0.0f), 0.0f, 0.99f));
	float radius = 15.0f;
	entity.AddComponent(std::make_unique<BoundingCircle2D>(radius));

	std::vector<LineSegment> lines;
	lines.push_back(LineSegment(Vector2D(-radius, -radius), Vector2D(0.0f, radius)));
	lines.push_back(LineSegment(Vector2D(0.0f, radius), Vector2D(radius, -radius)));
	lines.push_back(LineSegment(Vector2D(radius, -radius), Vector2D(0.0f, -radius / 3.0f)));
	lines.push_back(LineSegment(Vector2D(0.0f, -radius / 3.0f), Vector2D(-radius, -radius)));
	entity.AddComponent(std::make_unique<RenderingComponent>(Color(1.0f, 1.0f, 1.0f), lines, false));

	entity.AddComponent(std::make_unique<HealthComponent>(5));
	entity.AddComponent(std::make_unique<ShooterComponent>(FireType::Common, 200.0f));
	entity.AddComponent(std::make_unique<PlayerComponent>(10000.0f, 5.0f));
	entity.AddComponent(std::make_unique<PlayerInputComponent>(accelerateKeyCode, shootKeyCode, rotateLeftKeyCode, rotateRightKeyCode, shieldKeyCode));
	entity.AddComponent(std::make_unique<ShieldUserComponent>(15000.0f, 6000.0f));
	entity.AddComponent(std::make_unique<ExplodableComponent>());

	return entity;
}

Entity EntityFactory::CreateAsteroid()
{
	//Create random values for position and velocity
	float x = static_cast<float>(Utilities::Random(0, APP_VIRTUAL_WIDTH));
	float y = static_cast<float>(Utilities::Random(0, APP_VIRTUAL_HEIGHT));
	float xVelocity = static_cast<float>(Utilities::Random(200, 800)) / 100.f - 0.5f;
	float yVelocity = static_cast<float>(Utilities::Random(200, 800)) / 100.f - 0.5f;


	return CreateAsteroid(Vector2D(x, y), 1, Vector2D(xVelocity, yVelocity));
}

Entity EntityFactory::CreateAsteroid(const Vector2D & position)
{
	//Create random values for velocity
	float xVelocity = static_cast<float>(Utilities::Random(200, 800)) / 100.f - 0.5f;
	float yVelocity = static_cast<float>(Utilities::Random(200, 800)) / 100.f - 0.5f;

	return CreateAsteroid(position, 1, Vector2D(xVelocity, yVelocity));
}

Entity EntityFactory::CreateAsteroid(const Vector2D & position, const int size, const Vector2D & velocity)
{
	int minRadius = 40 / size;
	int maxRadius = 60 / size;
	int granularity = 20;
	int minVary = 25;
	int maxVary = 75;
	float angle = static_cast<float>(Utilities::Random(0, 359));
	float rotationalSpeed = static_cast<float>(Utilities::Random(200, 800)) / 100.f;

	std::vector<Vector2D> points;
	for (double ang = 0; ang < 2 * M_PI; ang += 2 * M_PI / granularity)
	{
		int angleVaryPc = Utilities::Random(minVary, maxVary);
		double angleVaryRadians = (2 * M_PI / granularity) * static_cast<double>(angleVaryPc) / 100;
		double angleFinal = ang + angleVaryRadians - (M_PI / granularity);
		int radius = Utilities::Random(minRadius, maxRadius);
		float px = static_cast<float>(sin(angleFinal) * radius);
		float py = static_cast<float>(-cos(angleFinal) * radius);

		points.push_back(Vector2D(px, py));
	}

	std::vector<LineSegment> lines;
	for (int i = 0; i < points.size(); ++i)
	{
		if (i != points.size() - 1)
		{
			lines.push_back(LineSegment(points[i], points[i + 1]));
	    }
	    else
	    {
	    	lines.push_back(LineSegment(points[i], points[0]));
	    }
	}

	Entity entity (GenerateId(), position, angle);
	entity.AddComponent(std::make_unique<PhysicsComponent>(velocity, Vector2D(0.0f, 0.0f), rotationalSpeed));
	entity.AddComponent(std::make_unique<BoundingCircle2D>(maxRadius, false));
	entity.AddComponent(std::make_unique<RenderingComponent>(Color(1.000f, 0.843f, 0.000f), lines));
	entity.AddComponent(std::make_unique<HealthComponent>(1));
	entity.AddComponent(std::make_unique<EnemyComponent>(size * 5));
	entity.AddComponent(std::make_unique<AsteroidComponent>(size));

	return entity;
}

Entity EntityFactory::CreateShip(const Vector2D & position)
{
	Entity entity (GenerateId(), position, 0.0f);
	entity.AddComponent(std::make_unique<PhysicsComponent>());
	float radius = 18.0f;
	entity.AddComponent(std::make_unique<BoundingCircle2D>(radius));

	std::vector<LineSegment> lines;
	lines.push_back(LineSegment(Vector2D(-radius, -radius), Vector2D(0.0f, radius)));
	lines.push_back(LineSegment(Vector2D(0.0f, radius), Vector2D(radius, -radius)));
	lines.push_back(LineSegment(Vector2D(radius, -radius), Vector2D(-radius, -radius)));
	entity.AddComponent(std::make_unique<RenderingComponent>(Color(0.541f, 0.169f, 0.886f), lines));

	entity.AddComponent(std::make_unique<HealthComponent>(5));
	entity.AddComponent(std::make_unique<ShooterComponent>(FireType::Common, 1500.0f));
	entity.AddComponent(std::make_unique<EnemyComponent>(15));
	entity.AddComponent(std::make_unique<EnemyShipComponent>(150.0f, 15.0f, 100.0f, 200.0f, Color(0.8f, 0.4f, 0.4f)));
	entity.AddComponent(std::make_unique<ExplodableComponent>());

	return entity;
}

Entity EntityFactory::CreateRamShip(const Vector2D & position)
{
	Entity entity (GenerateId(), position, 0.0f);
	entity.AddComponent(std::make_unique<PhysicsComponent>());
	float radius = 18.0f;
	entity.AddComponent(std::make_unique<BoundingCircle2D>(radius));

	std::vector<Vector2D> points;
	for (double ang = 0; ang < 2 * M_PI; ang += 1)
	{
		float px = static_cast<float>(sin(ang) * radius);
		float py = static_cast<float>(-cos(ang) * radius);
		points.push_back(Vector2D(px, py));
	}

	std::vector<LineSegment> lines;
	for (int i = 0; i < points.size(); ++i)
	{
		if (i != points.size() - 1)
		{
			lines.push_back(LineSegment(points[i], points[i + 1]));
	    }
	    else
	    {
	    	lines.push_back(LineSegment(points[i], points[0]));
	    }
	}

	entity.AddComponent(std::make_unique<RenderingComponent>(Color(1.0f, 1.0f, 1.0f), lines));
	entity.AddComponent(std::make_unique<HealthComponent>(3));
	entity.AddComponent(std::make_unique<EnemyComponent>(15));
	entity.AddComponent(std::make_unique<RamShipComponent>(150.0f, 100.0f));
	entity.AddComponent(std::make_unique<ExplodableComponent>());
	return entity;
}

Entity EntityFactory::CreateBoss(const Vector2D & position)
{
	Entity entity (GenerateId(), position, 0.0f);
	entity.AddComponent(std::make_unique<PhysicsComponent>());
	float radius = 40.0f;
	entity.AddComponent(std::make_unique<BoundingCircle2D>(radius));

	std::vector<Vector2D> points(8);
	points.push_back(Vector2D(-radius + 5, -radius));       // 1
	points.push_back(Vector2D(-radius - 25, radius));       // 2
	points.push_back(Vector2D(-20.0f, radius));             // 3
	points.push_back(Vector2D(-8.0f, 10.0f));               // 4
	points.push_back(Vector2D(8.0f, 10.0f));                // 5
	points.push_back(Vector2D(20.0f, radius));              // 6
	points.push_back(Vector2D(radius + 25, radius));        // 7
	points.push_back(Vector2D(radius - 5, -radius));        // 8

	std::vector<LineSegment> lines;
	for (int i = 0; i < points.size(); ++i)
	{
		if (i != points.size() - 1)
		{
			lines.push_back(LineSegment(points[i], points[i + 1]));
	    }
	    else
	    {
	    	lines.push_back(LineSegment(points[i], points[0]));
	    }
	}

	entity.AddComponent(std::make_unique<RenderingComponent>(Color(0.647f, 0.165f, 0.165f), lines));
	entity.AddComponent(std::make_unique<HealthComponent>(60));
	entity.AddComponent(std::make_unique<ShooterComponent>(FireType::Boss, 1800.0f));
	entity.AddComponent(std::make_unique<EnemyComponent>(20));
	entity.AddComponent(std::make_unique<ShieldUserComponent>(15000.0f, 4000.0f));
	entity.AddComponent(std::make_unique<ExplodableComponent>());

	return entity;
}

Entity EntityFactory::CreateBullet(const Vector2D & position, const float angle, Entity * owner, const bool playerOwner)
{
	// The initial position of the bullet should be the ship's center point
	Vector2D startPosition = position;

	// The direction of the bullet should be the direction in which the ship is facing
	Vector2D velocity(cos(Utilities::ToRadians(angle + 90)), sin(Utilities::ToRadians(angle + 90)));

	// Move the bullet a bit so it doesn't render inside the ship (we want it at the ship's front edge tip)
	startPosition += (velocity * 20);

	// Bullet movement speed factor
	velocity *= 200;

	Entity entity(GenerateId(), position, angle);
	entity.AddComponent(std::make_unique<PhysicsComponent>(velocity));
	float radius = 2.0f;
	entity.AddComponent(std::make_unique<BoundingCircle2D>(radius));
	
	float r, g, b;
	if (playerOwner)
	{
		r = 0.0f;
		g = 1.0f;
		b = 0.0f;
	}
	else
	{
		r = 1.0f;
		g = 0.0f;
		b = 0.0f;
	}

	std::vector<Vector2D> points;
	for (double ang = 0; ang < 2 * M_PI; ang += 1)
	{
		float px = static_cast<float>(sin(ang) * radius);
		float py = static_cast<float>(-cos(ang) * radius);
		points.push_back(Vector2D(px, py));
	}

	std::vector<LineSegment> lines;
	for (int i = 0; i < points.size(); ++i)
	{
		if (i != points.size() - 1)
		{
			lines.push_back(LineSegment(points[i], points[i + 1]));
	    }
	    else
	    {
	    	lines.push_back(LineSegment(points[i], points[0]));
	    }
	}

	entity.AddComponent(std::make_unique<RenderingComponent>(Color(r, g, b), lines));
	entity.AddComponent(std::make_unique<BulletComponent>(owner, playerOwner));
	entity.AddComponent(std::make_unique<ExpireComponent>(2000.0f));

	return entity;
}

Entity EntityFactory::CreateItem(const Vector2D & position, const ItemType type)
{
	Entity entity (GenerateId(), position, 0.0f);
	entity.AddComponent(std::make_unique<PhysicsComponent>(Vector2D(0.0f, 0.0f), Vector2D(0.0f, 0.0f), 0.6f));
	float radius = 10.0f;
	entity.AddComponent(std::make_unique<BoundingCircle2D>(radius));
	
	float r, g, b;

	switch (type) {
	case ItemType::Mineral:
		r = 0.0f;
		g = 0.808f;
		b = 0.82f;
		break;

	case ItemType::PowerUp:
		r = 0.486f;
		g = 0.988f;
		b = 0.0f;
		break;

	case ItemType::Heart:
		r = 1.0f;
		g = 0.412f;
		b = 0.706f;
		break;

	default:
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
	}

	std::vector<Vector2D> points;

	switch (type) {
	case ItemType::Mineral:
		points.push_back(Vector2D(-radius / 2, -radius));    // 1
		points.push_back(Vector2D(0.0f, radius));            // 2
		points.push_back(Vector2D(radius / 2, -radius));     // 3
		points.push_back(Vector2D(-radius, 0.0f));           // 4
		points.push_back(Vector2D(radius, 0.0f));            // 5
		break;
	case ItemType::Heart:
		points.push_back(Vector2D(0, -radius));              // 1
		points.push_back(Vector2D(-radius, radius - 5));     // 2
		points.push_back(Vector2D(-radius + 5, radius));     // 3
		points.push_back(Vector2D(-3, radius));              // 4
		points.push_back(Vector2D(0, radius / 2));           // 5
		points.push_back(Vector2D(3, radius));               // 6
		points.push_back(Vector2D(radius - 5, radius));      // 7
		points.push_back(Vector2D(radius, radius - 5));      // 8
		break;
	case ItemType::PowerUp:
		points.push_back(Vector2D(0, radius));
		points.push_back(Vector2D(-radius / 2, 0));
		points.push_back(Vector2D(0, 0));
		points.push_back(Vector2D(-radius / 2 - 2, -radius));
		points.push_back(Vector2D(radius / 2, 2));
		points.push_back(Vector2D(0, 2));
		points.push_back(Vector2D(0, radius / 2));
		break;
	}

	std::vector<LineSegment> lines;
	for (int i = 0; i < points.size(); ++i)
	{
		if (i != points.size() - 1)
		{
			lines.push_back(LineSegment(points[i], points[i + 1]));
	    }
	    else
	    {
	    	lines.push_back(LineSegment(points[i], points[0]));
	    }
	}

	entity.AddComponent(std::make_unique<RenderingComponent>(Color(r, g, b), lines));
	entity.AddComponent(std::make_unique<ItemComponent>(type));
	entity.AddComponent(std::make_unique<ExpireComponent>(10000.0f));

	return entity;
}

Entity EntityFactory::CreateExplosion(const Vector2D & position)
{
	Entity entity (GenerateId(), position, 0.0f);
	float particleLifeTime = 500.0f;
	entity.AddComponent(std::make_unique<ParticleEmmiter>(particleLifeTime));
	entity.AddComponent(std::make_unique<ExpireComponent>(particleLifeTime));

	ParticleEmmiter* emmiter = entity.GetComponent<ParticleEmmiter>();

    Color color(1.000f, 0.271f, 0.000f);
	float angle = 0.0f;
	Vector2D velocity(cos(Utilities::ToRadians(angle)), sin(Utilities::ToRadians(angle)));
	velocity *= 200;
	emmiter->AddParticle(velocity, angle, color);

	angle = 45.0f;
	velocity = Vector2D(cos(Utilities::ToRadians(angle)), sin(Utilities::ToRadians(angle)));
	velocity *= 200;
	emmiter->AddParticle(velocity, angle, color);

	angle = 90.0f;
	velocity = Vector2D(cos(Utilities::ToRadians(angle)), sin(Utilities::ToRadians(angle)));
	velocity *= 200;
	emmiter->AddParticle(velocity, angle, color);

	angle = 135.0f;
	velocity = Vector2D(cos(Utilities::ToRadians(angle)), sin(Utilities::ToRadians(angle)));
	velocity *= 200;
	emmiter->AddParticle(velocity, angle, color);

	angle = 180.0f;
	velocity = Vector2D(cos(Utilities::ToRadians(angle)), sin(Utilities::ToRadians(angle)));
	velocity *= 200;
	emmiter->AddParticle(velocity, angle, color);

	angle = 225.0f;
	velocity = Vector2D(cos(Utilities::ToRadians(angle)), sin(Utilities::ToRadians(angle)));
	velocity *= 200;
	emmiter->AddParticle(velocity, angle, color);

	angle = 270.0f;
	velocity = Vector2D(cos(Utilities::ToRadians(angle)), sin(Utilities::ToRadians(angle)));
	velocity *= 200;
	emmiter->AddParticle(velocity, angle, color);

	angle = 315.0f;
	velocity = Vector2D(cos(Utilities::ToRadians(angle)), sin(Utilities::ToRadians(angle)));
	velocity *= 200;
	emmiter->AddParticle(velocity, angle, color);

	return entity;
}

Entity EntityFactory::CreateShield(Entity * parent)
{
	Entity entity (GenerateId(), Vector2D(0.0f, 0.0f), 0.0f);
	float radius = parent->GetComponent<BoundingCircle2D>()->GetRadius();

	std::vector<Vector2D> points;
	for (double ang = 0; ang < 2 * M_PI; ang += 0.05)
	{
		float px = static_cast<float>(sin(ang) * (radius + 6));
		float py = static_cast<float>(-cos(ang) * (radius + 6));
		points.push_back(Vector2D(px, py));
	}

	std::vector<LineSegment> lines;
	for (int i = 0; i < points.size(); ++i)
	{
		if (i != points.size() - 1)
		{
			lines.push_back(LineSegment(points[i], points[i + 1]));
	    }
	    else
	    {
	    	lines.push_back(LineSegment(points[i], points[0]));
	    }
	}

	entity.AddComponent(std::make_unique<RenderingComponent>(Color(0.0f, 0.8f, 0.9f), lines));
	entity.AddComponent(std::make_unique<ShieldComponent>());
	entity.AddComponent(std::make_unique<ParentComponent>(parent));

	return entity;
}

Entity EntityFactory::CreateUIText(const Vector2D & position, const std::string& text, const Color & color, const std::string& name)
{
	Entity entity (GenerateId(), name, position, 0.0f);
	entity.AddComponent(std::make_unique<UITextComponent>(text, color));
	return entity;
}

Entity EntityFactory::CreateUIText(const Vector2D & position, const std::string& text, const Color & color)
{
	Entity entity (GenerateId(), position, 0.0f);
	entity.AddComponent(std::make_unique<UITextComponent>(text, color));
	return entity;
}

Entity EntityFactory::CreateUIButton(const Vector2D & position, float width, float height, const std::string& text, const Color & color, const Color & hoverColor, const std::string& name)
{
	Entity entity (GenerateId(), name, position, 0.0f);
	entity.AddComponent(std::make_unique<UIButtonComponent>(color, hoverColor));
	entity.AddComponent(std::make_unique<UITextComponent>(text, color));

	float halfHeight = height / 2.0f;
	float padding = 5.0f;
	Vector2D p1(0 - padding, halfHeight + padding);
	Vector2D p2(width - padding, halfHeight + padding);
	Vector2D p3(width - padding, -halfHeight + padding);
	Vector2D p4(0 - padding, -halfHeight + padding);

	std::vector<LineSegment> lines;
	lines.push_back(LineSegment(p1, p2));
	lines.push_back(LineSegment(p2, p3));
	lines.push_back(LineSegment(p3, p4));
	lines.push_back(LineSegment(p4, p1));

	entity.AddComponent(std::make_unique<RenderingComponent>(color, lines));
	entity.AddComponent(std::make_unique<BoundingBox2D>(width, height));
	return entity;
}

void EntityFactory::ResetIdCounter()
{
	m_nextId = 1;
}

unsigned int EntityFactory::GenerateId()
{
	return m_nextId++;
}
