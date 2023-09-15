#ifndef _G_WINDOW_H_
#define _G_WINDOW_H_

#define GLFW_EXPOSE_NATIVE_WIN32

#include "glfw3.h"

namespace glhost
{
	class GWindow
	{
	private:
		void RenderProcess();
		void StartRender();

	public:
		int OpenWindow(int parentWindow, int width, int height, bool isVisibile);
	};
}

#endif
