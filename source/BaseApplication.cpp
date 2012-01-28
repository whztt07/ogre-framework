#include "BaseApplication.h"
#include "PathManager.h"

#include <OgreRoot.h>
#include <OgreRenderWindow.h>

#define WINDOW_TITLE "OgreFramework"

using namespace Ogre;

BaseApplication::BaseApplication() :
	mWindow(0), mWidth(1024), mHeight(768)
{

}

//------------------------------------------------------------------------------//

BaseApplication::~BaseApplication()
{
	
}

//------------------------------------------------------------------------------//

void BaseApplication::recreateWindow()
{
	if (mWindow)
	{
		WindowEventUtilities::removeWindowEventListener(mWindow, this);
		mRoot->getRenderSystem()->destroyRenderWindow(WINDOW_TITLE);
	}
	
	//!todo do not hardcore the window settings
	NameValuePairList settings;
	settings.insert(std::make_pair("title", WINDOW_TITLE));
	settings.insert(std::make_pair("FSAA", "0"));
	settings.insert(std::make_pair("vsync", "true"));

	mWindow = mRoot->createRenderWindow(WINDOW_TITLE, mWidth, mHeight, false, &settings);
	WindowEventUtilities::addWindowEventListener(mWindow, this);
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

	// Create the application window
	recreateWindow();
	
	mRoot->addFrameListener(this);
	
	// Start the rendering loop
	mRoot->startRendering();
	
	// Shutdown
	WindowEventUtilities::removeWindowEventListener(mWindow, this);
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

bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return !mShutdown;
}
