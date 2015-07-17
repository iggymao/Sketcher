// //////////////////////////////
// Git test #2
// ApplicationFramework.cpp : main project file.
#include "stdafx.h"
#include "../Headers/Application.h"
//#include "../Headers/Main.h"							// Include our main header for the application..includes the necessary includes for the application

using namespace System;

int main(array<System::String ^> ^args)
{
	Application application;  // create the application object
	
	application.Initialize(); // initialize the contents to setup the different system managers

	//Console::WriteLine(L"Hello World");			// alternate technique to write to the console
    return application.Main();						// Launches into the main application routine
}
