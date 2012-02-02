#include "Application.h"
#include "Window.h"

#include <OgreSceneManager.h>
#include <OgreViewport.h>
#include <OgreCamera.h>
#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreColourValue.h>

using namespace Ogre;

Application::Application()
{
	
}

//------------------------------------------------------------------------------//

Application::~Application()
{
	
}

//------------------------------------------------------------------------------//

void Application::createScene()
{
	mSceneMgr = Root::getSingleton().createSceneManager(ST_GENERIC);
	
	mCamera = mSceneMgr->createCamera("Camera");
	
	onRenderWindowRecreated();
}

//------------------------------------------------------------------------------//

void Application::onRenderWindowRecreated()
{
	mViewport = mWindow->mRenderWindow->addViewport(mCamera);
	mViewport->setBackgroundColour(ColourValue(0.2, 0.2, 0.2, 1.0));
}
