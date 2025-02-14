#include "CameraManager.h"

#include "SceneCamera.h"

CameraManager* CameraManager::P_SHARED_INSTANCE = NULL;

Camera* CameraManager::getActiveCamera()
{
	//TODO : if (EngineState != PLAY)
	return this->getSceneCamera();
}

SceneCamera* CameraManager::getSceneCamera()
{
	return this->selectedSceneCamera;
}

SceneCamera* CameraManager::getSceneCameraByIndex(int index)
{
	if (index > sceneCameraList.size())
	{
		return NULL;
	}
	return this->sceneCameraList[index];
}

std::vector<SceneCamera*> CameraManager::getSceneCameras()
{
	return this->sceneCameraList;
}

void CameraManager::setMainCamera(Camera* camera)
{
	mainCamera = camera;
}

void CameraManager::setMainCameraByIndex(int index)
{
	if (index > cameraList.size())
	{
		return;
	}
	setMainCamera(cameraList[index]);
}

void CameraManager::setSceneCameraProjection(int type)
{
	//this->selectedSceneCamera->setProjectionType(type);
}

void CameraManager::updateSceneCamera(float deltaTime)
{
	this->selectedSceneCamera->UpdateCamera(1, deltaTime);
}

void CameraManager::addCamera(Camera* camera)
{
	if (mainCamera == NULL)
		setMainCamera(camera);
	this->cameraList.push_back(camera);
}

void CameraManager::addSceneCamera(SceneCamera* camera)
{
	if (this->selectedSceneCamera == NULL)
		this->selectedSceneCamera = camera;

	this->sceneCameraList.push_back(camera);
}

void CameraManager::removeSceneCamera(SceneCamera* camera)
{
	int index = -1;

	for (int i = 0; i < this->sceneCameraList.size() && index == -1; i++)
	{
		if (this->sceneCameraList[i] == camera)
			index = i;
	}

	if (index != -1)
	{
		this->sceneCameraList.erase(this->sceneCameraList.begin() + index);
	}
}

void CameraManager::removeCamera(Camera* camera)
{
	int index = -1;

	for (int i = 0; i < this->cameraList.size() && index == -1; i++)
	{
		if (this->cameraList[i] == camera)
			index = i;
	}

	if (index != -1)
	{
		this->cameraList.erase(this->cameraList.begin() + index);
	}
}

CameraManager::CameraManager()
{
	this->selectedSceneCamera = new SceneCamera("Scene Camera");
	/*this->selectedSceneCamera->setPosition(0, 1, -8);
	this->selectedSceneCamera->updateViewMatrix();*/
	this->addCamera(this->selectedSceneCamera);
}

CameraManager::~CameraManager()
{
	P_SHARED_INSTANCE = nullptr;
}

CameraManager::CameraManager(const CameraManager&) {}

CameraManager* CameraManager::getInstance() {
	return P_SHARED_INSTANCE;
}

void CameraManager::initialize()
{
	if (P_SHARED_INSTANCE) {}
	P_SHARED_INSTANCE = new CameraManager();
}

void CameraManager::destroy()
{
	if (P_SHARED_INSTANCE != NULL)
	{
		delete P_SHARED_INSTANCE;
	}
}
