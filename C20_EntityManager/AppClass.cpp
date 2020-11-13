#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUp(
		vector3(3.0f, 0.0f, 15.0f), //Position
		vector3(0.0f, 0.0f, 12.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)
	
	//Entity Manager
	m_pEntityMngr = MyEntityManager::GetInstance();
	
	//creeper
	/*
	m_pEntityMngr->AddEntity("Minecraft\\Creeper.obj", "Creeper");
	m_pEntityMngr->SetAxisVisibility(true, "Creeper"); //set visibility of the entity's axis

	//steve
	m_pEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve");
	m_pEntityMngr->SetAxisVisibility(true, "Steve"); //set visibility of the entity's axis

	//add an entity
	m_pEntityMngr->AddEntity("Minecraft\\Cow.obj", "Cow");
	//set the model matrix and visibility of the last entity added
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(2.0f,-1.5f,-1.0f)));
	m_pEntityMngr->SetAxisVisibility(true);

	//add an entity
	m_pEntityMngr->AddEntity("Minecraft\\Zombie.obj", "Zombie");
	//set the model matrix and visibility of the last entity added
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(0.0f, -2.5f, 0.0f)));
	m_pEntityMngr->SetAxisVisibility(true);
	*/		

	//OUTSIDE WALLS AND FLOORS
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Floor");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(0.0f, -5.0f, 0.0f)) * glm::scale(vector3(140.0f, 1.0f, 100.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall1");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(0.0f, -5.0f, 0.0f)) * glm::scale(vector3(140.0f, 10.0f, 1.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall2");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(0.0f, -5.0f, 99.0f)) * glm::scale(vector3(140.0f, 10.0f, 1.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall3");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(139.0f, -5.0f, 1.0f)) * glm::scale(vector3(1.0f, 10.0f, 98.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall4");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(0.0f, -5.0f, 1.0f)) * glm::scale(vector3(1.0f, 10.0f, 98.0f)));

	//INSIDE WALLS
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall5");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(113.0f, -5.0f, 43.0f)) * glm::scale(vector3(2.0f, 7.5f, 20.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall6");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(113.0f, -5.0f, 1.0f)) * glm::scale(vector3(2.0f, 7.5f, 33.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall7");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(70.0f, -5.0f, 73.0f)) * glm::scale(vector3(2.0f, 7.5f, 26.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall8");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(23.0f, -5.0f, 25.0f)) * glm::scale(vector3(2.0f, 7.5f, 55.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall9");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(15.0f, -5.0f, 14.0f)) * glm::scale(vector3(2.0f, 7.5f, 11.0f)));

	//INSIDE WALLS pt.2
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall10");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(55.0f, -5.0f, 63.0f)) * glm::scale(vector3(60.0f, 7.5f, 2.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall11");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(17.0f, -5.0f, 23.0f)) * glm::scale(vector3(68.0f, 7.5f, 2.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall12");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(23.0f, -5.0f, 80.0f)) * glm::scale(vector3(16.0f, 7.5f, 2.0f)));

	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Player");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(0, 0, 0)) * glm::scale(vector3(3.0f, 6.0f, 3.0f)), "Player");

	/*
	//add an entity
	m_pEntityMngr->AddEntity("Minecraft\\Pig.obj", "Pig");
	//set the model matrix and visibility of the last entity added
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(-2.0f,-1.0f,-1.0f)));
	m_pEntityMngr->SetAxisVisibility(true);
	*/

	ShowCursor(false);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
	
	/*
	//Set model matrix to the creeper
	matrix4 mCreeper = glm::translate(m_v3Creeper) * ToMatrix4(m_qCreeper) * ToMatrix4(m_qArcBall);
	m_pEntityMngr->SetModelMatrix(mCreeper, "Creeper");
	

	//Set model matrix to Steve
	matrix4 mSteve = glm::translate(vector3(2.5f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, glm::radians(-55.0f), AXIS_Z);
	m_pEntityMngr->SetModelMatrix(mSteve, "Steve");


	//Move the last entity added slowly to the right
	matrix4 lastMatrix = m_pEntityMngr->GetModelMatrix();// get the model matrix of the last added
	lastMatrix *= glm::translate(IDENTITY_M4, vector3(0.01f, 0.0f, 0.0f)); //translate it
	m_pEntityMngr->SetModelMatrix(lastMatrix); //return it to its owner

	*/

	//Update Entity Manager
	m_pEntityMngr->Update();
		
	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release the entity manager
	m_pEntityMngr->ReleaseInstance();

	//release GUI
	ShutdownGUI();
}