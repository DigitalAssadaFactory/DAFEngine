#pragma once



namespace DAF
{

#define ECS_EntityCount ECSBase::Manager::componentTypes[0].size()

#define ECS_ComponentTypeCount ECSBase::Manager::componentTypes.size()

#define ECS_GetHandle(entityID,componentType) \
   ECSBase::Manager::componentTypes[ECS::Component::componentType::componentTypeID][entityID]

#define ECS_At(entityID, componentType) ECSBase::Manager::componentTypes[componentType][entityID]

#define ECS_Create(componentType) \
   std::get<0>(ECSBase::Manager::necessaryEvil[componentType])()

#define ECS_Copy(entityID, componentType, iter) \
   std::get<1>(ECSBase::Manager::necessaryEvil[componentType])(ECSBase::Manager::componentTypes[componentType][entityID][iter])

#define ECS_Delete(entityID, componentType, iter) \
   std::get<2>(ECSBase::Manager::necessaryEvil[componentType])(ECSBase::Manager::componentTypes[componentType][entityID][iter])

#define ECS_GenerateEntityID() ECSBase::Manager::GenerateEntityID()

#define ECS_FreeEntity(entityID) ECSBase::Manager::freeEntities.push(entityID);

}