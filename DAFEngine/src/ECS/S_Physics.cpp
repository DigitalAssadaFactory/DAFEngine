/*#include "S_Physics.h"



using namespace ECS;
using namespace ECSBase;
using namespace ECS::Utility;
using namespace DirectX;

namespace ECS::System {

	std::map<size_t, btRigidBody*>   Physics::m_RB_map;
	//std::vector<size_t>              Physics::m_RB_system_local_version(1, 1);
	//std::vector<size_t>              Physics::m_TRA_system_local_version(1, 1);
	//std::vector<size_t>              Physics::m_RB_active_index_pool(0);
	//std::vector<size_t>              Physics::m_TRA_active_index_pool(0);

	btDynamicsWorld*                   Physics::m_pWorld = nullptr;
	btDispatcher*                      Physics::m_pDispatcher = nullptr;
	btBroadphaseInterface*             Physics::m_pBroadphase = nullptr;
	btConstraintSolver*                Physics::m_pSolver = nullptr;
	btCollisionConfiguration*          Physics::m_pCollisionConfig = nullptr;
}




namespace ECS::System {

	void Physics::Init() {
		InitWorld();
		InitBodies();
	}

	void Physics::Update() {
		UpdateTransforms();
		m_pWorld->stepSimulation((btScalar)Time::DeltaTime);
	}

	void Physics::Exit() {
		for (auto & body : m_RB_map)
			DeleteRigidBody(body.first);

		delete m_pWorld;
		delete m_pSolver;
		delete m_pBroadphase;
		delete m_pDispatcher;
		delete m_pCollisionConfig;
	}



	btConvexHullShape* Physics::MakeCHS(const std::vector<Vertex> & vertices) {
		btConvexHullShape* chs = new btConvexHullShape();
		for (auto & v : vertices)
			chs->addPoint(btVector3(v.position.x, v.position.y, v.position.z));
		return chs;
	}

	btStaticPlaneShape * Physics::MakeStaticPlane(const btVector3 & normal) {
		return new btStaticPlaneShape(normal, 0);
	}





	void Physics::InitWorld()
	{
		m_pCollisionConfig = new btDefaultCollisionConfiguration();
		m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfig);
		m_pBroadphase = new btDbvtBroadphase();
		m_pSolver = new btSequentialImpulseConstraintSolver();
		m_pWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfig);
		m_pWorld->setGravity(btVector3(0.0f, -9.8f, 0.0f));
	}

	void Physics::InitBodies()
	{
		for (size_t e = 0; e < ECS_EntityCount; ++e)
			if (ECS_GetHandle(e, RigidBody).size() && ECS_GetHandle(e, Transform).size())
				AddRigidBody(e);
	}

	void Physics::UpdateTransforms()
	{


	}




	btRigidBody* Physics::GetRigidBody(const size_t & entityID) { return m_RB_map[entityID]; }

	void Physics::AddRigidBody(const size_t & entityID)
	{
		const size_t rb = ECS_GetHandle(entityID, RigidBody)[0];
		const size_t tra = ECS_GetHandle(entityID, Transform)[0];

		if (!rb)  Logger::ThrowBox("You can't create btRigidBody from entity which doesn't have RigidBody Component.");
		if (!tra) Logger::ThrowBox("You can't create btRigidBody from entity which doesn't have Transform Component.");

		m_RB_map.emplace(entityID, CreateRigidBody(
			Component::RigidBody::mass[rb],
			Component::RigidBody::collisionShape[rb],
			Component::Transform::position[tra],
			Component::Transform::rotation[tra],
			Component::RigidBody::linearVelocity[rb],
			Component::RigidBody::angularVelocity[rb]
		));
	}

	void Physics::DeleteRigidBody(const size_t & entityID)
	{
		if (m_RB_map[entityID] == nullptr)
			Logger::ThrowBox("Entity with ID = " + std::to_string(entityID) + " does not have btRigidBody to delete.");

		m_pWorld->removeRigidBody(m_RB_map[entityID]);
		delete m_RB_map[entityID]->getMotionState();
		delete m_RB_map[entityID]->getCollisionShape();
		delete m_RB_map[entityID];
		m_RB_map.erase(entityID);
	}

	void Physics::UpdateRigidBody(const size_t & entityID)
	{
		if (m_RB_map[entityID] == nullptr)
			Logger::ThrowBox("Entity with ID = " + std::to_string(entityID) + " does not have btRigidBody to update.");

		const size_t rb = ECS_GetHandle(entityID, RigidBody)[0];
		const size_t tra = ECS_GetHandle(entityID, Transform)[0];

		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(
			Component::Transform::position[tra].x,
			Component::Transform::position[tra].y,
			Component::Transform::position[tra].z));

		t.setRotation(btQuaternion(
			Component::Transform::rotation[tra].x,
			Component::Transform::rotation[tra].y,
			Component::Transform::rotation[tra].z));


		m_RB_map[entityID]->setCollisionShape(Component::RigidBody::collisionShape[rb]);
		m_RB_map[entityID]->getCollisionShape()->setLocalScaling(btVector3(
			Component::Transform::scale[tra].x,
			Component::Transform::scale[tra].y,
			Component::Transform::scale[tra].z));
		btVector3 inertia(0, 0, 0);
		if (Component::RigidBody::mass[rb] != 0.0f)
			m_RB_map[entityID]->getCollisionShape()->calculateLocalInertia(Component::RigidBody::mass[rb], inertia);
		m_RB_map[entityID]->setMassProps(Component::RigidBody::mass[rb], inertia);
		m_RB_map[entityID]->setMotionState(Component::RigidBody::motionState[rb]);
		m_RB_map[entityID]->setWorldTransform(t);
		m_RB_map[entityID]->getMotionState()->setWorldTransform(t);
		m_RB_map[entityID]->setLinearVelocity(Component::RigidBody::linearVelocity[rb]);
		m_RB_map[entityID]->setAngularVelocity(Component::RigidBody::angularVelocity[rb]);
	}

	btRigidBody * Physics::CreateRigidBody(const float & mass, btCollisionShape * collisionShape,
		const DirectX::XMFLOAT3 & position, const DirectX::XMFLOAT3 & rotation,
		const btVector3 & linearVel, const btVector3 & angularVel)
	{
		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(position.x, position.y, position.z));
		t.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));

		btMotionState* state = new btDefaultMotionState();

		static btVector3 inertia(0, 0, 0);
		if (mass != 0.0f) collisionShape->calculateLocalInertia(mass, inertia);

		btRigidBody* body = new btRigidBody(mass, state, collisionShape, inertia);

		m_pWorld->addRigidBody(body);

		body->setWorldTransform(t);
		state->setWorldTransform(t);
		body->clearForces();
		body->setLinearVelocity(linearVel);
		body->setAngularVelocity(angularVel);

		return body;
	}

	btRigidBody* Physics::CreateRigidBody(const float & mass, btCollisionShape * collisionShape,
		const btVector3 & position, const btVector3 & rotation, const btVector3 & linearVel, const btVector3 & angularVel)
	{
		btTransform t;
		t.setIdentity();
		t.setOrigin(position);
		t.setRotation(btQuaternion(rotation.getX(), rotation.getY(), rotation.getZ()));

		btMotionState* state = new btDefaultMotionState();

		static btVector3 inertia(0, 0, 0);
		if (mass != 0.0f) collisionShape->calculateLocalInertia(mass, inertia);

		btRigidBody* body = new btRigidBody(mass, state, collisionShape, inertia);

		m_pWorld->addRigidBody(body);

		body->setWorldTransform(t);
		state->setWorldTransform(t);
		body->clearForces();
		body->setLinearVelocity(linearVel);
		body->setAngularVelocity(angularVel);

		return body;
	}


}*/