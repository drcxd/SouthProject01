/* Program entrance of game.
 */

#include <string>

#include "Game.h"

#include "tinyxml.h"

// Variables which control the window and FPS
int FPS;
int X;
int Y;
int SCREEN_WIDTH;
int SCREEN_HEIGHT; 
std::string title;
unsigned FRAME_TIME;

int main(int argc, char *argv[])
{
	// Get general system info include: 
	// title, screen width and height, x and y position etc.
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile("scripts/environment.xml"))
	{
		std::cerr << "Falied load envrioment xml file. Error: " << xmlDoc.ErrorDesc() << std::endl;
		return -1;
	}
	else
	{
		TiXmlElement *pRoot = xmlDoc.RootElement();
		TiXmlElement *e = pRoot->FirstChildElement();
		e->Attribute("x", &X);
		e = e->NextSiblingElement();
		e->Attribute("y", &Y);
		e = e->NextSiblingElement();
		e->Attribute("screen_width", &SCREEN_WIDTH);
		e = e->NextSiblingElement();
		e->Attribute("screen_height", &SCREEN_HEIGHT);
		e = e->NextSiblingElement();
		e->Attribute("fps", &FPS);
		e = e->NextSiblingElement();
		title = e->Attribute("title");
	}
	FRAME_TIME = 1000 / FPS;
	// Info generated
	
	unsigned int total_frames = 0; // variable to count total frame 
	unsigned start_time = 0, finish_time = 0; // Timer to calculate actual frame time

    TheGame::Instance()->init(title.c_str(), X, Y, SCREEN_WIDTH, SCREEN_HEIGHT, 0); 

     while (TheGame::Instance()->running()) 
     {
		 start_time = SDL_GetTicks(); // get start time of per frame
		 TheGame::Instance()->handleEvents();
		 TheGame::Instance()->update();
		 TheGame::Instance()->render();
		 finish_time = SDL_GetTicks(); // get end time of per frame
		 if (finish_time - start_time < FRAME_TIME)
		 {
			 SDL_Delay(FRAME_TIME - (finish_time - start_time)); // Pause game if actual frame time is less than frame time.
		 }
     }
     TheGame::Instance()->clean();

     return 0;
}
