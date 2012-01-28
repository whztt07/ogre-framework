#include <OgreWindowEventUtilities.h>
#include <OgreFrameListener.h>

namespace Ogre { class Root; class RenderWindow; }

class BaseApplication : public Ogre::WindowEventListener, public Ogre::FrameListener
{
public:
	BaseApplication();
	~BaseApplication();
	
	void run();
	
protected:
	void recreateWindow();

	void windowResized(Ogre::RenderWindow* rw);
	void windowClosed(Ogre::RenderWindow* rw);
	
	size_t mWidth;
	size_t mHeight;
	
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		
	bool mShutdown;

	Ogre::Root* mRoot;

	Ogre::RenderWindow* mWindow;
	//Ogre::RenderWindow* mBackgroundWindow;
};
