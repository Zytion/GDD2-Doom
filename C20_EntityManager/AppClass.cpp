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
	

	//Player must be the first object
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Player");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(5, -3, 15)) * glm::scale(vector3(3.0f, 6.0f, 3.0f)), "Player");
	//creeper
	
	/*
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
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall_Floor");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(0.0f, -5.0f, 0.0f)) * glm::scale(vector3(140.0f, 1.0f, 100.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(0.0f, -4.0f, 0.0f)) * glm::scale(vector3(140.0f, 10.0f, 1.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(0.0f, -4.0f, 99.0f)) * glm::scale(vector3(140.0f, 10.0f, 1.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(139.0f, -4.0f, 1.0f)) * glm::scale(vector3(1.0f, 10.0f, 98.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(0.0f, -4.0f, 1.0f)) * glm::scale(vector3(1.0f, 10.0f, 98.0f)));

	//INSIDE WALLS
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(113.0f, -4.0f, 43.0f)) * glm::scale(vector3(2.0f, 7.5f, 20.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(113.0f, -4.0f, 1.0f)) * glm::scale(vector3(2.0f, 7.5f, 33.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(70.0f, -4.0f, 73.0f)) * glm::scale(vector3(2.0f, 7.5f, 26.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(23.0f, -4.0f, 25.0f)) * glm::scale(vector3(2.0f, 7.5f, 55.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(15.0f, -4.0f, 14.0f)) * glm::scale(vector3(2.0f, 7.5f, 11.0f)));

	//INSIDE WALLS pt.2
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(55.0f, -4.0f, 63.0f)) * glm::scale(vector3(60.0f, 7.5f, 2.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(17.0f, -4.0f, 23.0f)) * glm::scale(vector3(68.0f, 7.5f, 2.0f)));
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(23.0f, -4.0f, 80.0f)) * glm::scale(vector3(16.0f, 7.5f, 2.0f)));


	//ADD ENEMIES
	
	m_pEntityMngr->AddEntity("Minecraft\\Creeper.obj", "Enemy1");
	m_pEntityMngr->SetAxisVisibility(true, "Enemy1"); //set visibility of the entity's axis
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(20.0f, -2.5f, 10.0f)));

	m_enemies.push_back(m_pEntityMngr->GetEntity());
	m_enemies[0]->m_destinations.push_back(vector3(5, -3.75, 5));
	m_enemies[0]->m_destinations.push_back(vector3(40, -3.75, 5));
	m_enemies[0]->m_destinationCount = 2;

	m_pEntityMngr->AddEntity("Minecraft\\Creeper.obj", "Enemy1");
	m_pEntityMngr->SetAxisVisibility(true, "Enemy1"); //set visibility of the entity's axis
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(20.0f, 30.0f, 10.0f)));

	m_enemies.push_back(m_pEntityMngr->GetEntity());
	m_enemies[1]->m_destinations.push_back(vector3(5, -3.75, 40));
	m_enemies[1]->m_destinations.push_back(vector3(5, -3.75, 10));
	m_enemies[1]->m_destinationCount = 2;


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

	ProcessMouseClick();	

	static float fTimer = 0;	//store the new timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer

	m_pEntityMngr->timer = fTimer;
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
	m_pMeshMngr->AddSkyboxToRenderList("Skybox_Hell.png");
	
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