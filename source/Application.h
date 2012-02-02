#include "BaseApplication.h"

namespace Ogre { class SceneManager; class Viewport; class Camera; }

class Application : public BaseApplication
{
public:
	Application();
	~Application();
	
protected:
	virtual void createScene();
	virtual void onRenderWindowRecreated();
	
	Ogre::SceneManager* mSceneMgr;
	Ogre::Viewport* mViewport;
	Ogre::Camera* mCamera;
};
