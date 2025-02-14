#pragma once
#include <vector>
#include <string>

#include "Camera.h"
#include "SceneCamera.h"

class CameraManager
{
private:
    typedef std::vector<Camera*> CameraList;
    typedef std::vector<SceneCamera*> SceneCameraList;

private:
    SceneCamera* selectedSceneCamera;
    Camera* mainCamera;
    CameraList cameraList;
    SceneCameraList sceneCameraList;

public:
    Camera* getActiveCamera();
    SceneCamera* getSceneCamera();
    SceneCamera* getSceneCameraByIndex(int index);
    std::vector<SceneCamera*> getSceneCameras();
    void setMainCamera(Camera* camera);
    void setMainCameraByIndex(int index);
    void setSceneCameraProjection(int type);
    void updateSceneCamera(float deltaTime);
    void addCamera(Camera* camera);
    void addSceneCamera(SceneCamera* camera);
    void removeSceneCamera(SceneCamera* camera);
    void removeCamera(Camera* camera);

private:
    static CameraManager* P_SHARED_INSTANCE;

private:
    CameraManager();
    ~CameraManager();
    CameraManager(const CameraManager&);
    CameraManager& operator = (const CameraManager&);

public:
    static CameraManager* getInstance();
    static void initialize();
    static void destroy();
};
