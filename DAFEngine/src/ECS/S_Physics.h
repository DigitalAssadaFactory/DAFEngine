/*#pragma once
#include "U_Basic.h"
#include "../Time.h"
#include "C_RigidBody.h"
#include "C_Transform.h"
#include <map>



namespace ECS::System {

	struct Physics {

		static void Init();
		static void Update();
		static void Exit();

		//static void Recalibrate(); No need to recalibrate anything yet

		static btRigidBody* GetRigidBody(const size_t & entityID);
		static void AddRigidBody(const size_t & entityID);
		static void DeleteRigidBody(const size_t & entityID);
		static void UpdateRigidBody(const size_t & entityID);

		static btConvexHullShape* MakeCHS(const std::vector<ECS::Utility::Vertex> & vertices);
		static btStaticPlaneShape* MakeStaticPlane(const btVector3 & normal);

	private:
		static void InitWorld();
		static void InitBodies();
		static void UpdateTransforms();


		static btRigidBody* CreateRigidBody(const float & mass, btCollisionShape * collisionShape,
			const btVector3 & position = { 0,0,0 }, const btVector3 & rotation = { 0,0,0 },
			const btVector3 & linearVel = { 0,0,0 }, const btVector3 & angularVel = { 0,0,0 });

		static btRigidBody* CreateRigidBody(const float & mass, btCollisionShape * collisionShape,
			const DirectX::XMFLOAT3 & position = { 0,0,0 }, const DirectX::XMFLOAT3 & rotation = { 0,0,0 },
			const btVector3 & linearVel = { 0,0,0 }, const btVector3 & angularVel = { 0,0,0 });
					

		static std::map<size_t, btRigidBody*>   m_RB_map;
		static btDynamicsWorld*                   m_pWorld;
		static btDispatcher*                      m_pDispatcher;
		static btBroadphaseInterface*             m_pBroadphase;
		static btConstraintSolver*                m_pSolver;
		static btCollisionConfiguration*          m_pCollisionConfig;
	};
}*/