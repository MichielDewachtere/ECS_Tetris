#include "Entity.h"

monthly::entity_id monthly::Entity::m_CurrentEntityIdx = 0;

monthly::entity_id monthly::Entity::CreateNewEntity()
{
	return m_CurrentEntityIdx++;
}