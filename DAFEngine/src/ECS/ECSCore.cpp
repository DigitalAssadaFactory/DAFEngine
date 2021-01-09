#include "ECSCore.h"



namespace DAF
{

	namespace ECSBase {

		std::queue<size_t>                                     Manager::freeEntities;
		DYNAMIC_ARRAY_03(size_t)                               Manager::componentTypes = DYNAMIC_ARRAY_03_INIT(size_t, 1, 1, 0); //(1, std::vector<size_t>(1, std::vector<size_t>()));
		std::vector<std::tuple<fpCreate, fpCopy, fpDelete>>    Manager::necessaryEvil(1, std::tuple<fpCreate, fpCopy, fpDelete>(0, 0, 0));

		size_t Manager::GenerateEntityID() {
			if (freeEntities.empty())
			{
				size_t newSize = componentTypes[0].size() + 1;
				for (auto& componentType : componentTypes)
					componentType.resize(newSize);

				return newSize - 1;
			}
			else
			{
				size_t temp = freeEntities.front();
				freeEntities.pop();
				return temp;
			}
		}
	}

	namespace ECS {

		Entity::Entity() : entityID(ECS_GenerateEntityID()) {}

		Entity::Entity(const Entity& e) : entityID(ECS_GenerateEntityID()) {
			for (size_t ct = 1; ct < ECS_ComponentTypeCount; ++ct)
			{
				for (size_t c = 0; c < ECS_At(e.GetID(), ct).size(); ++c)
				{
					ECS_At(entityID, ct).push_back(ECS_Copy(e.GetID(), ct, c));
				}
			}
		}

		Entity::Entity(Entity&& e) noexcept
		{
			entityID = e.GetID();
			e.SetID(0);
		}

		Entity::~Entity() {
			if (entityID == 0) return;
			for (size_t ct = 1; ct < ECS_ComponentTypeCount; ++ct)
			{
				for (size_t c = 0; c < ECS_At(entityID, ct).size(); ++c)
				{
					ECS_Delete(entityID, ct, c);
				}
				ECS_At(entityID, ct).resize(0);
			}
			ECS_FreeEntity(entityID);
		}

		size_t Entity::GetID() const { return entityID; }
		void Entity::SetID(const size_t& newID) { entityID = newID; }
	}

}