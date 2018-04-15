#pragma once

class Component;
class Collision;

class Entity
{
public:
	Entity(unsigned int id, const Vector2D& position, float angle);
	Entity(unsigned int id, const std::string& name, const Vector2D& position, float angle);

    template <typename T>
    T* GetComponent()
    {
    	std::type_index index(typeid(T));
    	if(m_components.count(std::type_index(typeid(T))) != 0)
    	{
    		return static_cast<T*>(m_components[index].get());
    	}
    	else
    	{
    		return nullptr;
    	}
    }
	void AddComponent(std::unique_ptr<Component> component);

	void AddCollision(const Collision& collision);
    const std::vector<Collision>& GetCollisions();
    void RemoveCollisionWithEntity(unsigned int entityId);
	void RemoveAllCollisions();

	unsigned int GetId() const;
	Vector2D GetPosition() const;
	void SetPosition(const Vector2D& position);
	float GetAngle() const;
	void SetAngle(float angle);
	void MarkAsNeedsToBeRemoved();
	bool NeedsToBeRemoved() const;
	const std::string& GetName() const;

private:
	unsigned int m_id;
	std::string m_name;
	bool m_needsToBeRemoved;
	Vector2D m_position;
	float m_angle;

    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
	std::vector<Collision> m_collisions;
};