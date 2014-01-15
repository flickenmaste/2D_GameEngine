// Will Gilstrap - Game Engine
// 1/14/2013

#include <Engine.h>

int main()
{
	as::RunApplication();
	system("pause");
	tiny::parseDoc("settings.xml");
	tiny2::parseDoc("settings.xml");
	Engine::openWindow();
	return 0;
}