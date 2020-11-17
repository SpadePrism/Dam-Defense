//Titan Engine, by Atlas X Games 
// Physics.h - header for the class that represents physics bodies
#pragma once
//include other headers
#include "Transform.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include "Renderer.h"
//include glm features
#include "GLM/glm.hpp"

//import other required features
#include <vector>
#include "entt.hpp"
//import the bullet physics engine
#include <btBulletDynamicsCommon.h>

namespace Titan {

#pragma region old
	//class for bullet3 collisions
	//class TTN_PhysicsB
	//{
	//public:
	//	TTN_PhysicsB();
	//	~TTN_PhysicsB()=default;

	//	TTN_PhysicsB(glm::vec3 pos, btDiscreteDynamicsWorld* world, btAlignedObjectArray<btCollisionShape*> parray);

	//	void InitCollision(); // initiailizes stuff required to detect and solve collisions

	//	void SetMass(btScalar mass);
	//	void SetTrans(btVector3 trans);

	//	btTransform GetTrans() { return m_trans; };

	//	//btDiscreteDynamicsWorld* GetWorld() { return m_world; };
	//	//btBroadphaseInterface* GetBroad() { return m_broadphase; };

	//	//btBroadphaseInterface* m_broadphase;
	//	/*static btDefaultCollisionConfiguration* m_config;
	//	static btCollisionDispatcher* m_dispatcher;

	//	static btSequentialImpulseConstraintSolver* m_solver;
	//	static btDiscreteDynamicsWorld* m_world;
	//	static btDefaultMotionState* m_MotionState;*/

	//	btTransform m_trans;
	//	//collision object
	//	btCollisionObject m_col;
	//	//mass of object
	//	btScalar m_mass;

	//};

	//class TTN_Debug : public btIDebugDraw {
	///*public:

	//	struct Line {
	//		GLfloat vertices[6];
	//		
	//		Line(const btVector3& from, const btVector3& to) {
	//			vertices[0] = from.x();
	//			vertices[1] = from.y();
	//			vertices[2] = from.z();

	//			vertices[3] = to.x();
	//			vertices[4] = to.y();
	//			vertices[5] = to.z();}
	//	};


	//	TTN_Debug();
	//	virtual ~TTN_Debug();

	//	virtual void setDebugMode(int debugmode);

	//	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
	//	
	//	virtual void lines(const btVector3& from, const btVector3& to);

	//	virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

	//	virtual void reportErrorWarning(const char* warningString);

	//	virtual void draw3dText(const btVector3& location, const char* textString);

	//	virtual int getDebugMode() const;


	//	int m_debugMode;*/

	//	int m_debugMode;

	//public:

	//	TTN_Debug();
	//	virtual ~TTN_Debug();

	//	virtual void	drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor);

	//	virtual void	drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

	//	virtual void	drawSphere(const btVector3& p, btScalar radius, const btVector3& color);

	//	virtual void	drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha);

	//	virtual void	drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

	//	virtual void	reportErrorWarning(const char* warningString);

	//	virtual void	draw3dText(const btVector3& location, const char* textString);

	//	virtual void	setDebugMode(int debugMode);

	//	virtual int		getDebugMode() const { return m_debugMode; }

	//};

#pragma endregion 
	class TTN_Physics
	{
	public:

		//default constructor
		TTN_Physics();

		//contrustctor with data
		TTN_Physics(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, entt::entity entityNum, bool dynamic = true, float mass = 1.0f);

		~TTN_Physics();

		//copy, move, and assingment constrcutors for ENTT
		TTN_Physics(const TTN_Physics&) = default;
		TTN_Physics(TTN_Physics&&) = default;
		TTN_Physics& operator=(TTN_Physics&) = default;

		//update function, keeps data up to date, call once a frame
		void Update(float deltaTime);

		//getters
		TTN_Transform GetTrans() { return m_trans; }
		bool GetIsStatic() { return m_IsStaticBody; }
		float GetMass() { return m_Mass; }
		btRigidBody* GetRigidBody() { return m_body; }
		bool GetIsInWorld() { return m_InWorld; }
		glm::vec3 GetLinearVelocity();
		glm::vec3 GetAngularVelocity();
		bool GetHasGravity() { return m_hasGravity; }
		entt::entity GetEntity() { return m_entity; }

		//setters
		void SetIsStatic(bool isStatic);
		void SetIsInWorld(bool inWorld);
		void SetMass(float mass);
		void SetLinearVelocity(glm::vec3 velocity);
		void SetAngularVelocity(glm::vec3 velocity);
		void SetHasGravity(bool hasGrav);

		//forces
		void AddForce(glm::vec3 force);
		void AddImpulse(glm::vec3 impulseForce);
		void ClearForces();

		//identifier
		void SetEntity(entt::entity entity);

	protected:
		TTN_Transform m_trans; //transform with the position, rotation, and scale of the physics body

		bool m_IsStaticBody; //is the body dynamic or static

		//bullet data
		float m_Mass; //mass of the object
		bool m_hasGravity; //is the object affected by gravity
		btCollisionShape* m_colShape; //the shape of it's collider, includes scale
		btTransform m_bulletTrans;  //it's internal transform, does not include scale
		btDefaultMotionState* m_MotionState; //motion state for it, need to extract the transform out of this every update if the body is dynamic
		btRigidBody* m_body; //rigidbody, acutally does the collision stuff, have to get the transform out of this every update if the body is static
		bool m_InWorld; //boolean marking if it's been added to the bullet physics world yet, used to make sure that the physics body

		entt::entity m_entity; //the entity number that gets stored as a void pointer in bullet so that it can be used to indentify the objects later

		//data for rendering the physics box
		static TTN_Shader::sshptr shader;
		static TTN_Texture::stptr texture;
		static TTN_Material::smatptr mat;
		static TTN_Mesh::smptr mesh;
		static bool renderingSetUp;
		static TTN_Renderer renderer;
	};

	class TTN_Collision {
	public:
		//defines a special easier to use name for the shared(smart) pointer to the class
		typedef std::shared_ptr<TTN_Collision> scolptr;

		//creates and returns a shared(smart) pointer to the class
		static inline scolptr Create() {
			return std::make_shared<TTN_Collision>();
		}
	public:
		//ensure moving and copying is not allowed so we can control destructor calls through pointers
		TTN_Collision(const TTN_Collision& other) = delete;
		TTN_Collision(TTN_Collision& other) = delete;
		TTN_Collision& operator=(const TTN_Collision& other) = delete;
		TTN_Collision& operator=(TTN_Collision&& other) = delete;

	public:
		//constructor
		TTN_Collision();

		//destructor
		~TTN_Collision() = default;

		//getters
		const btRigidBody* GetBody1() { return b1; }
		const btRigidBody* GetBody2() { return b2; }
		glm::vec3 GetNormal1() { return norm1; }
		glm::vec3 GetNormal2() { return norm2; }

		//setters
		void SetBody1(const btRigidBody* body);
		void SetBody2(const btRigidBody* body);
		void SetNormal1(btVector3 normal);
		void SetNormal2(btVector3 normal);

	protected:
		//rigidbodies for the colliding objects (which should also contain a reference to the entity)
		const btRigidBody* b1;
		const btRigidBody* b2;
		//normals for the collision
		glm::vec3 norm1;
		glm::vec3 norm2;
	};
 
}