#include "Application.h"

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

Application::~Application()
{
	
}


void Application::createScene()
{
	mSceneMgr = Root::getSingleton().createSceneManager(ST_GENERIC);
	
	mCamera = mSceneMgr->createCamera("Camera");
	
	mViewport = mWindow->addViewport(mCamera);
	mViewport->setBackgroundColour(ColourValue(0.2, 0.2, 0.2, 1.0));
}

bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    mOISKeyboard->capture();
    mOISMouse->capture();

	return !mShutdown;
}


bool Application::mouseMoved(const OIS::MouseEvent& event)
{
	return true;
}

bool Application::mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID id)
{
	return true;
}

bool Application::mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID id)
{
	return true;
}

bool Application::keyPressed(const OIS::KeyEvent& event)
{
    if (event.key == OIS::KC_ESCAPE)
		mShutdown = true;
	return true;
}

bool Application::keyReleased(const OIS::KeyEvent& event)
{
	return true;
}

