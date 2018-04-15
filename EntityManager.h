#pragma once

class EntityManager
{
public:
	unsigned int AddEntity(Entity entity);
	
	std::shared_ptr<Entity> FindEntityByName(const std::string& name);
	std::shared_ptr<Entity> FindEntityById(unsigned int id);
	Entity* GetEntityAt(int index);
	const std::vector<std::shared_ptr<Entity>>& GetEntities() const;
	
	unsigned int FindEntityIdByName(const std::string& name);

	int GetNumberOfEntities() const;

	bool RemoveEntityByName(const std::string& name);
	bool RemoveEntityById(unsigned int id);
	void RemoveAllEntities();
	void RemoveEntitiesMarkedForRemoval();
private:
	std::vector<unsigned int> FindExpiredIds();
	void SwapAndPop(int index);
private:
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::unordered_map<unsigned int, int> m_idToIndexMap;
};