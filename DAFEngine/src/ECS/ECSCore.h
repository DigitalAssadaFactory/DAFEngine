#pragma once
#include <vector>
#include <queue>
#include <tuple>
#include "../Utility.h"
#include "../Utility/DYNAMIC_ARRAY_MACRO.h"
#include "ECS_MACRO.h"



namespace DAF
{

	typedef size_t(*fpCreate)();
	typedef size_t(*fpCopy)(const size_t&);
	typedef void(*fpDelete)(const size_t&);

	namespace ECSBase {

		struct Manager {
			template<typename T>
			static size_t GenerateComponentTypeID() {
				const size_t last = componentTypes.size(); //-1
				const size_t newSize = componentTypes.size() + 1;
				componentTypes.resize(newSize);
				necessaryEvil.resize(newSize);

				componentTypes[last].resize(1, std::vector<size_t>());
				necessaryEvil[last] = std::make_tuple((fpCreate)T::Create, (fpCopy)T::Copy, (fpDelete)T::Delete);

				return last;
			}
			static size_t GenerateEntityID();

			static std::queue<size_t>                                     freeEntities;
			static DYNAMIC_ARRAY_03(size_t)                               componentTypes; // [typeID][entityID][vector of component indices]
			static std::vector<std::tuple<fpCreate, fpCopy, fpDelete>>    necessaryEvil;
		};

		template<typename T>
		struct ECSComponent {
			static const size_t componentTypeID;
		};
		template<typename T>
		const size_t ECSComponent<T>::componentTypeID(Manager::GenerateComponentTypeID<T>());
	}

	namespace ECS {

		struct Entity {
			Entity();
			Entity(const Entity& e);
			Entity(Entity&& e) noexcept;
			~Entity();

			template<typename T>
			auto GetComponent(const int& at = 0) const {
				if (at >= (int)ECS_At(entityID, T::componentTypeID).size() || at < -1)
					Logger::ThrowBox("GetComponent failed.");

				int temp = at;
				if (at == -1) temp = (int)(ECS_At(entityID, T::componentTypeID).size()) - 1;

				return T::Wrapper(ECS_At(entityID, T::componentTypeID)[temp]);
			}

			template<typename T>
			void AddComponent(const int& count = 1) {
				for (int i = 0; i < count; ++i)
				{
					ECS_At(entityID, T::componentTypeID).push_back(T::Create());
				}
			}

			template<typename T>
			void RemoveComponent(const int& at = 0) {
				if (at >= ECS_At(entityID, T::componentTypeID).size()) return;

				T::Delete(ECS_At(entityID, T::componentTypeID)[at]);
				ECS_At(entityID, T::componentTypeID).erase(ECS_At(entityID, T::componentTypeID).begin() + at);
			}

			template<typename T>
			void UpdateComponent() {

			}

			size_t GetID() const;
			void SetID(const size_t& newID);

		private:
			size_t entityID;
		};

		namespace Component {
			// all component classes created by REGISTER_ECSComponent_XX macro are here
		}

		namespace System {
			// all systems are here + helper functions used by more than one system
		}

		namespace Utility {
			// header name with "U_" stands for Utility. For example "U_Graphics.h" contains useful graphics constants
		}

	}

}
//||||||||||||||||||||||||||||||||||||||||||
#include "ECSComponent_TEMPLATE_MACRO.h"
//||||||||||||||||||||||||||||||||||||||||||