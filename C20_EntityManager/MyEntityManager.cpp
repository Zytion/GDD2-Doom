#include "MyEntityManager.h"
using namespace std;
using namespace Simplex;
//  MyEntityManager
MyEntityManager* MyEntityManager::m_pInstance = nullptr;
void MyEntityManager::Init(void)
{
	m_uEntityCount = 0;
	m_entityList.clear();
}
void MyEntityManager::Release(void)
{
	for (uint uEntity = 0; uEntity < m_uEntityCount; ++uEntity)
	{
		MyEntity* pEntity = m_entityList[uEntity];
		SafeDelete(pEntity);
	}
	m_uEntityCount = 0;
	m_entityList.clear();
}
MyEntityManager* MyEntityManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new MyEntityManager();
	}
	return m_pInstance;
}
void MyEntityManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
int Simplex::MyEntityManager::GetEntityIndex(String a_sUniqueID)
{
	//look one by one for the specified unique id
	for (uint uIndex = 0; uIndex < m_uEntityCount; ++uIndex)
	{
		if (a_sUniqueID == m_entityList[uIndex]->GetUniqueID())
			return uIndex;
	}
	//if not found return -1
	return -1;
}
//Accessors
Model* Simplex::MyEntityManager::GetModel(uint a_uIndex)
{
	//if the list is empty return blank
	if (m_entityList.size() == 0)
		return nullptr;

	// if out of bounds
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_entityList[a_uIndex]->GetModel();
}
Model* Simplex::MyEntityManager::GetModel(String a_sUniqueID)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->GetModel();
	}
	return nullptr;
}
MyRigidBody* Simplex::MyEntityManager::GetRigidBody(uint a_uIndex)
{
	//if the list is empty return blank
	if (m_entityList.size() == 0)
		return nullptr;

	// if out of bounds
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_entityList[a_uIndex]->GetRigidBody();
}
MyRigidBody* Simplex::MyEntityManager::GetRigidBody(String a_sUniqueID)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->GetRigidBody();
	}
	return nullptr;
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(uint a_uIndex)
{
	//if the list is empty return blank
	if (m_entityList.size() == 0)
		return IDENTITY_M4;

	// if out of bounds
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_entityList[a_uIndex]->GetModelMatrix();
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(String a_sUniqueID)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		return pTemp->GetModelMatrix();
	}
	return IDENTITY_M4;
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, String a_sUniqueID)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->SetModelMatrix(a_m4ToWorld);
	}
}
void Simplex::MyEntityManager::SetAxisVisibility(bool a_bVisibility, uint a_uIndex)
{
	//if the list is empty return blank
	if (m_entityList.size() == 0)
		return;

	// if out of bounds
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	return m_entityList[a_uIndex]->SetAxisVisible(a_bVisibility);
}
void Simplex::MyEntityManager::SetAxisVisibility(bool a_bVisibility, String a_sUniqueID)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->SetAxisVisible(a_bVisibility);
	}
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, uint a_uIndex)
{
	//if the list is empty return blank
	if (m_entityList.size() == 0)
		return;

	// if out of bounds
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount -1;

	m_entityList[a_uIndex]->SetModelMatrix(a_m4ToWorld);
}
//The big 3
MyEntityManager::MyEntityManager(){Init();}
MyEntityManager::MyEntityManager(MyEntityManager const& other){ }
MyEntityManager& MyEntityManager::operator=(MyEntityManager const& other) { return *this; }
MyEntityManager::~MyEntityManager(){Release();};
// other methods
void Simplex::MyEntityManager::Update(void)
{
	bool colliding = false;
	//check collisions
	for (uint i = 1; i < m_uEntityCount; i++)
	{
		if (m_entityList[0]->IsColliding(m_entityList[i])) 
		{
			colliding = true;
			//take entityID
			string entityID = m_entityList[i]->GetUniqueID();

			//CHECK FOR WALLS
			if (entityID[0] == 'W') 
			{
				cout << "STOP MOVEMENT IN PROGRESS" << endl;
			}
			//CHECK FOR BULLETS
			else if (entityID[0] == 'B') 
			{
				//END GAME!
				cout << "Bullet Hit" << endl;
			}
			//CHECK IF ENEMY HIT PLAYER
			else if (entityID[0] == 'E')
			{
				//END GAME!
				cout << "Player Collides with Enemy" << endl;
			}
		}
	}
	if (!colliding)
	{
		m_entityList[0]->ApplyMovement();
	}
	else
	{
		m_entityList[0]->ApplyMovement();
	}
	
	for (uint i = 14; i < m_uEntityCount; i++) 
	{
		colliding = false;
		for (uint j = i + 1; j < m_uEntityCount; j++) 
		{
			if (m_entityList[i]->IsColliding(m_entityList[j]))
			{
				colliding = true;
				//CHECK FOR ENEMIES
				if (m_entityList[i]->GetUniqueID()[0] == 'E')
				{
					//CHECK IF BULLET HIT
					if (m_entityList[j]->GetUniqueID()[0] == 'B')
					{
						//DESTROY ENEMY
						cout << "Enemy Takes Damage" << endl;
					}
				}
				//CHECK FOR BULLET
				else if (m_entityList[i]->GetUniqueID()[0] == 'B')
				{
					//BULLET COLLIDED WITH WALL
					if (m_entityList[j]->GetUniqueID()[0] == 'W')
					{
						//DESTROY BULLET
						cout << "Bullet go BRRRRR" << endl;
					}
				}
			}
		}
		if (!colliding)
		{
			m_entityList[i]->ApplyMovement();
		}
	}

}
void Simplex::MyEntityManager::AddEntity(MyEntity* p)
{
	if (p->IsInitialized())
	{
		m_entityList.push_back(p);
		m_uEntityCount = m_entityList.size();
	}
}
void Simplex::MyEntityManager::AddEntity(String a_sFileName, String a_sUniqueID)
{
	//Create a temporal entity to store the object
	MyEntity* pTemp = new MyEntity(a_sFileName, a_sUniqueID);
	//if I was able to generate it add it to the list
	if (pTemp->IsInitialized())
	{
		m_entityList.push_back(pTemp);
		m_uEntityCount = m_entityList.size();
	}
}
void Simplex::MyEntityManager::RemoveEntity(uint a_uIndex)
{
	//if the list is empty return
	if (m_entityList.size() == 0)
		return;

	// if out of bounds choose the last one
	if (a_uIndex >= m_uEntityCount)
		a_uIndex = m_uEntityCount - 1;

	// if the entity is not the very last we swap it for the last one
	if (a_uIndex != m_uEntityCount - 1)
	{
		std::swap(m_entityList[a_uIndex], m_entityList[m_uEntityCount - 1]);
	}
	
	//and then pop the last one
	MyEntity* pTemp = m_entityList[m_uEntityCount - 1];
	SafeDelete(pTemp);
	m_entityList.pop_back();
	--m_uEntityCount;
	return;
}
void Simplex::MyEntityManager::RemoveEntity(String a_sUniqueID)
{
	int nIndex = GetEntityIndex(a_sUniqueID);
	RemoveEntity((uint)nIndex);
}
String Simplex::MyEntityManager::GetUniqueID(uint a_uIndex)
{
	//if the list is empty return blank
	if (m_entityList.size() == 0)
		return "";
	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_entityList.size())
		a_uIndex = m_entityList.size() - 1;
	return m_entityList[a_uIndex]->GetUniqueID();
}
MyEntity* Simplex::MyEntityManager::GetEntity(uint a_uIndex)
{
	//if the list is empty return blank
	if (m_entityList.size() == 0)
		return nullptr;

	//if the index is larger than the number of entries we are asking for the last one
	if (a_uIndex >= m_entityList.size())
		a_uIndex = m_entityList.size() - 1;

	return m_entityList[a_uIndex];
}
void Simplex::MyEntityManager::AddEntityToRenderList(uint a_uIndex, bool a_bRigidBody)
{
	//if out of bounds will do it for all
	if (a_uIndex >= m_uEntityCount)
	{
		//add for each one in the entity list
		for (a_uIndex = 0; a_uIndex < m_uEntityCount; ++a_uIndex)
		{
			m_entityList[a_uIndex]->AddToRenderList(a_bRigidBody);
		}
	}
	else //do it for the specified one
	{
		m_entityList[a_uIndex]->AddToRenderList(a_bRigidBody);
	}
}
void Simplex::MyEntityManager::AddEntityToRenderList(String a_sUniqueID, bool a_bRigidBody)
{
	//Get the entity
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);
	//if the entity exists
	if (pTemp)
	{
		pTemp->AddToRenderList(a_bRigidBody);
	}
}