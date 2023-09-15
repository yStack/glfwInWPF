#include "pch.h"
#include "gl_net_host.h"
#include "glad/glad.h"
#include "glfw3.h"
#include "glfw3native.h"
#include "GWindow.h"


glhost::GWindow w;


EXPORT_API int gl_net_host::open_window(int parent, int width, int height, bool visible = false)
{
	int handle_ = w.OpenWindow(parent, width, height, visible);

	HWND handle = (HWND)handle_;

    long style = GetWindowLongA(handle, GWL_STYLE);
	style &= ~WS_POPUP;      
	style |= WS_CHILDWINDOW; 
	SetWindowLong(handle, GWL_STYLE, style);
	if (parent != 0)
	{
		SetParent(handle, (HWND)parent);
	}

	return handle_;
}



