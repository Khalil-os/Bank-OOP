#pragma once
#include "clsLoginScreen.h"

class clsLogOutScreen
{
public:
	static void LogOut()
	{
		system("cls");
		clsLoginScreen::ShowLoginScreen();
	}
};