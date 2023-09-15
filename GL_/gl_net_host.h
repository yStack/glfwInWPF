#ifndef _GL_NET_HOST_H_
#define _GL_NET_HOST_H_


#ifdef GL_EXPORTS
#define EXPORT_API extern "C" __declspec(dllexport)
#else
#define EXPORT_API extern "C" __declspec(dllimport)
#endif

#define GLFW_EXPOSE_NATIVE_WIN32



namespace gl_net_host
{
	EXPORT_API int open_window(int parent, int width, int height, bool visible);
}





#endif // _GL_NET_HOST_H_