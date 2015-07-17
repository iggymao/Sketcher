#include "stdafx.h"

#include "../Headers/WindowManager.h"

//constructor
WindowManager::WindowManager()
{
	printf("\nWindow Manager constructor called.");
}

WindowManager::~WindowManager()
{
	printf("\nWindow Manager destructor called.");
}

void WindowManager::Initialize()
{
	printf("\nInitializing the WindowManager.");
	return;
}

void WindowManager::Destroy()
{
	printf("\nDestroying the WindowManager.");
	return;
}

// adds a window to the WinInfo list
void WindowManager::AddWindow()
{
	printf("\nAdd a window to the MemberInfo list.");
}

// search for a window in the list
void WindowManager::SearchWindow()
{
	printf("\nSearch for a window in the MemberInfo list");
}	

// deletes a window from the list
void WindowManager::DeletetWindow()
{
	printf("\nDelete a window from the MemberInfo list");
}	

// moves a window
void WindowManager::MoveWindow()
{
	printf("\nMove a window");
}

// resizes a window
void WindowManager::ResizeWindow()
{
	printf("\nResize a window");
}	

// saves a layout
void WindowManager::SaveLayout()
{

}

// reads a layout
void WindowManager::ReadLayout()
{

}