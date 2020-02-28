/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Event
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

enum
{
	PLAY_BUTTON,
	CONFIG_BUTTON,
	HTP_BUTTON,
	CREDIT_BUTTON,
	MENU_BUTTON,
	PASS_BUTTON,
	PLAYER1OK_BUTTON,
	PLAYER2OK_BUTTON,
	PLAYER3OK_BUTTON,
	PLAYER4OK_BUTTON,
	CHOOSEMAP_BUTTON,
	PLAYER1_BUTTON,
	PLAYER2_BUTTON,
	PLAYER3_BUTTON,
	PLAYER4_BUTTON,
	MAP1_BUTTON,
	MAP2_BUTTON,
	MAP3_BUTTON,
	SAVE_BUTTON,
	LOAD_BUTTON
};

class Event : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent &event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		{
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			return (true);
		}

		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			switch (event.GUIEvent.EventType)
			{
			case irr::gui::EGET_BUTTON_CLICKED:
			{
				switch (id)
				{
				case PLAY_BUTTON:
					idButton = "play";
					return true;
				case CONFIG_BUTTON:
					idButton = "config";
					return true;
				case HTP_BUTTON:
					idButton = "htp";
					return true;
				case CREDIT_BUTTON:
					idButton = "credit";
					return true;
				case MENU_BUTTON:
					idButton = "menu";
					return true;
				case PASS_BUTTON:
					idButton = "pass";
					return true;
				case PLAYER1OK_BUTTON:
					idButton = "player1ok";
					return true;
				case PLAYER2OK_BUTTON:
					idButton = "player2ok";
					return true;
				case PLAYER3OK_BUTTON:
					idButton = "player3ok";
					return true;
				case PLAYER4OK_BUTTON:
					idButton = "player4ok";
					return true;
				case CHOOSEMAP_BUTTON:
					idButton = "chooseMap";
					return true;
				case PLAYER1_BUTTON:
					idButton = "player1";
					return true;
				case PLAYER2_BUTTON:
					idButton = "player2";
					return true;
				case PLAYER3_BUTTON:
					idButton = "player3";
					return true;
				case PLAYER4_BUTTON:
					idButton = "player4";
					return true;
				case MAP1_BUTTON:
					idButton = "map1";
					return true;
				case MAP2_BUTTON:
					idButton = "map2";
					return true;
				case MAP3_BUTTON:
					idButton = "map3";
					return true;
				case SAVE_BUTTON:
					idButton = "save";
					return true;
				case LOAD_BUTTON:
					idButton = "load";
					return true;

				default:
					return false;
				}
			}
			}
		}

		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	Event()
	{
		for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

	std::string getIdButton()
	{
		return idButton;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	std::string idButton;
};

#endif /* !EVENT_HPP_ */
