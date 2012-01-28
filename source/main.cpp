#include "Application.h"
#include "PathManager.h"

#include <OgrePlatform.h>
#include <OgreException.h>
#include <OISException.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	#include <windows.h>
	int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nCmdShow)
#else
	int main(int argc, char* argv[])
#endif
{
	PathManager::init();
	
	Application app;
	
	try
	{
		app.run();
	}
	catch (Ogre::Exception& e)
	{
		std::cerr << e.getFullDescription().c_str() << std::endl;
	}
	catch (OIS::Exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
		
	return 0;
}
