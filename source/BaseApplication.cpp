#include "BaseApplication.h"
#include "PathManager.h"
#include "Window.h"
#include "InputManager.h"
#include "HWMouse.h"

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OIS/OIS.h>

using namespace Ogre;

//------------------------------------------------------------------------------//

BaseApplication::BaseApplication() :
	mWindow(0), mWidth(1024), mHeight(768)
{

}

//------------------------------------------------------------------------------//

BaseApplication::~BaseApplication()
{
	
}

//------------------------------------------------------------------------------//

void BaseApplication::run()
{	
	// Construct Ogre::Root
	// We handle our stuff manually, so don't want to use any of the files
	mRoot = new Root(
		/* plugins.cfg file*/	"",
		/* config file */ 		"", 
		/* log file */ 			""
	);
	
	// Set render system
	//!todo do not hardcode render system
	mRoot->loadPlugin(PathManager::ogre_plugin_dir + "/RenderSystem_GL");
	RenderSystem* rs = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	mRoot->setRenderSystem(rs);
	
	// Fire up Ogre::Root
	mRoot->initialise(false);

	// Create a hidden background window to keep resources
	NameValuePairList params;
	params.insert(std::make_pair("hidden", "true"));
	RenderWindow *wnd = mRoot->createRenderWindow("InactiveHidden", 1, 1, false, &params);
	wnd->setActive(false);

	// Create input system
	mInputManager = new InputManager();

	// Create the application window
	mWindow = new Window();
	mWindow->mListener = static_cast<WindowEventListener*>(this);
	mWindow->mInputManager = mInputManager;
	mWindow->create();
	
	// Bootstrap resources
	//!todo put the data path into pathmanager (and do not hardcode it)
	ResourceGroupManager::getSingleton().addResourceLocation("../data", "FileSystem", "General");
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	
	// HW cursor
	mMouse = new HWMouse(mWindow->mID, 0, 0, "cursor.png");
		
	// Start the rendering loop
	createScene();
	mRoot->addFrameListener(this);
	mRoot->startRendering();
	
	// Shutdown
	delete mMouse;
	delete mWindow;
	delete mInputManager;
	mRoot->removeFrameListener(this);
	delete mRoot;
}

//------------------------------------------------------------------------------//

void BaseApplication::windowResized(RenderWindow* rw)
{
	
}

//------------------------------------------------------------------------------//

void BaseApplication::windowClosed(RenderWindow* rw)
{
	mShutdown = true;
}

//------------------------------------------------------------------------------//

void BaseApplication::recreateWindow()
{
	delete mMouse;
	
	mWindow->recreate();
	onRenderWindowRecreated();
	
	mMouse = new HWMouse(mWindow->mID, 0, 0, "cursor.png");
}

//------------------------------------------------------------------------------//

bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{	
	InputEvent* ev;
	
	mInputManager->process();
	
	while (true)
	{
		ev = mInputManager->pollEvents();
		
		if (ev == 0) break;
				
		if (ev->eventType == ET_Keyboard)
		{
			KeyEvent* kev = static_cast<KeyEvent*>(ev);
			
			// sample key handlers:
			// Esc: shutdown
			// R: recreate window
			// F: toggle fullscreen
			if (kev->keyEventType == KeyPressed)
			{
				if (kev->keyCode == OIS::KC_ESCAPE)
					mShutdown = true;
				else if (kev->keyCode == OIS::KC_R)
					recreateWindow();
				else if (kev->keyEventType == KeyPressed && kev->keyCode == OIS::KC_F) {
					mWindow->mFullscreen = !mWindow->mFullscreen; recreateWindow(); }
			}
		}

		delete ev;
	}
	
	return !mShutdown;
}
