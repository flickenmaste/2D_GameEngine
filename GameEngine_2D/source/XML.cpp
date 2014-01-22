// Will Gilstrap - Game Engine
// 1/22/2013

#include <XML.h>

void tiny::parseDoc(const char * filename)
{
	TiXmlDocument doc(filename);

	bool loadOkay = doc.LoadFile();

	if(!loadOkay)
	{
		std::cout << "File is missing." << std::endl;
		std::cin.get();
		std::cin.get();
		return;
	}

	// Get node
	TiXmlNode * settings = doc.FirstChild("settings");
	TiXmlElement * settingsElem = settings->ToElement();

	// Set Difficulty
	TiXmlElement * difficulty = settingsElem->FirstChildElement();
	const char * theDifficulty = difficulty->Attribute("normal");

	// Sound
	TiXmlElement * sound = difficulty->NextSiblingElement("sound");
	
	TiXmlElement * master = sound->FirstChildElement();
	const char * masterSound = master->Attribute("volume");
	master = master->NextSiblingElement();
	const char * soundFX = master->Attribute("volume");
	master = master->NextSiblingElement();
	const char * music = master->Attribute("volume");
	master = master->NextSiblingElement();
	const char * voice = master->Attribute("volume");
	master = master->NextSiblingElement();
	const char * microphone = master->Attribute("volume");

	// Mouse
	TiXmlElement * mouseNode = sound->NextSiblingElement("mouse");

	TiXmlElement * mouse = mouseNode->FirstChildElement();
	const char * mouseX = mouse->Attribute("x");
	const char * mouseY = mouse->Attribute("y");
	mouse = mouse->NextSiblingElement();
	const char * inverted = mouse->Attribute("false");

	// KeyBinds
	TiXmlElement * keyBinds = mouseNode->NextSiblingElement("keys");

	TiXmlElement * key = keyBinds->FirstChildElement();
	const char * forward = key->Attribute("key");
	key = key->NextSiblingElement();
	const char * backward = key->Attribute("key");
	key = key->NextSiblingElement();
	const char * left = key->Attribute("key");
	key = key->NextSiblingElement();
	const char * right = key->Attribute("key");
	key = key->NextSiblingElement();
	const char * jump = key->Attribute("key");
	key = key->NextSiblingElement();
	const char * use = key->Attribute("key");
	key = key->NextSiblingElement();
	const char * speak = key->Attribute("key");
	key = key->NextSiblingElement();
	const char * crouch = key->Attribute("key");
}