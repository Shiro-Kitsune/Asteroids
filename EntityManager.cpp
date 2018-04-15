#include "stdafx.h"

struct predicate
{
	bool operator()(const std::shared_ptr<Entity>& entity) const
	{
		return entity->NeedsToBeRemoved();
	}
};

unsigned int EntityManager::AddEntity(Entity entity)
{
	unsigned int id = entity.GetId();
	m_entities.push_back(std::make_shared<Entity>(std::move(entity)));
	m_idToIndexMap.emplace(id, m_entities.size()-1);
	return id;
}

std::shared_ptr<Entity> EntityManager::FindEntityByName(const std::string& name)
{
	for (auto const& entity : m_entities)
	{
		if (entity->GetName() == name)
		{
			return entity;
		}
	}
	return nullptr;
}

std::shared_ptr<Entity> EntityManager::FindEntityById(const unsigned int id)
{
	auto position = m_idToIndexMap.find(id);
	if (position != m_idToIndexMap.end())
	{
		int index = position->second;
		return m_entities.at(index);
	}

	return nullptr;
}

Entity* EntityManager::GetEntityAt(int index)
{
	return m_entities.at(index).get();
}

const std::vector<std::shared_ptr<Entity>>& EntityManager::GetEntities() const
{
	return m_entities;
}

unsigned int EntityManager::FindEntityIdByName(const std::string& name)
{
	for (auto const& entity : m_entities)
	{
		if (entity->GetName() == name)
		{
			return entity->GetId();
		}
	}
	return 0;
}

int EntityManager::GetNumberOfEntities() const
{
	return static_cast<int>(m_entities.size());
}

bool EntityManager::RemoveEntityByName(const std::string& name)
{
	auto position = std::find_if(m_entities.begin(), m_entities.end(), [name](const std::shared_ptr<Entity>& entity) { return entity->GetName() == name;});
	if (position != m_entities.end())
	{
		SwapAndPop(position - m_entities.begin());
		return true;
	}

	return false;
}

bool EntityManager::RemoveEntityById(unsigned int id)
{
	auto position = m_idToIndexMap.find(id);
	if (position != m_idToIndexMap.end())
	{
		SwapAndPop(position->second);
		return true;
	}

	return false;
}

void EntityManager::RemoveAllEntities()
{
	m_entities.clear();
	m_idToIndexMap.clear();
}

void EntityManager::RemoveEntitiesMarkedForRemoval()
{
	//m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), predicate()), m_entities.end());
	std::vector<unsigned int> indices = FindExpiredIds();
	for (auto index : indices)
	{
		SwapAndPop(index);
	}
}

std::vector<unsigned int> EntityManager::FindExpiredIds()
{
	std::vector<unsigned int> indices;
	for (int i = m_entities.size() - 1; i >= 0; --i)
	{
		if (m_entities.at(i)->NeedsToBeRemoved())
		{
			indices.push_back(i);
		}
	}
	return indices;
}

void EntityManager::SwapAndPop(int index)
{
	if (index < m_entities.size() - 1)
	{
		unsigned int id = m_entities.at(index)->GetId();
		m_idToIndexMap.erase(id);
		std::swap(m_entities[index], m_entities.back());
		m_entities.pop_back();
		m_idToIndexMap.erase(m_entities.at(index)->GetId());
		m_idToIndexMap.emplace(m_entities.at(index)->GetId(), index);
	}
	else
	{
		unsigned int id = m_entities.at(index)->GetId();
		m_idToIndexMap.erase(id);
		m_entities.pop_back();
	}
}