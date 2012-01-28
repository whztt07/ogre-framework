#include <string>
#include <vector>

#include <OgreWindowEventUtilities.h>

namespace Ogre { class RenderWindow; }

class Window
{
public:
	Window();
	~Window();

	std::string mWindowTitle;

	size_t mHeight;
	size_t mWidth;
	bool mVSync;
	bool mFullscreen;
	size_t mFSAA;
	
	std::vector< std::pair<size_t, size_t> > mSupportedFullscreenResolutions;
	
	Ogre::WindowEventListener* mListener;

	void recreate();
	void destroy();
	void create();
	
private:
	Ogre::RenderWindow* mWindow;
};
