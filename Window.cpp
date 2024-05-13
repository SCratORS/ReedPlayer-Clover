#include "Window.h"

Window::Window(): mSleeping(false)
{

}

Window::~Window()
{

}

bool Window::init(unsigned int width, unsigned int height)
{	
	return Renderer::init(width, height);
}

void Window::deinit()
{
	Renderer::deinit();
}

void Window::swapBuffers()
{
	Renderer::swapBuffers();
}

void Window::renderLoadingScreen()
{

}