#include "pch.h"

#include "glad/gl.h"
#define GLFW_INCLUDE_NONE
#include "GWindow.h"
#include "glfw3native.h"
#include "linmath.h"

#include <thread>
#include <stdlib.h>
#include <stdio.h>


namespace glhost
{
    static const struct
    {
        float x, y;
        float r, g, b;
    }


    vertices[3] =
    {
        { -0.6f, -0.4f, 1.f, 0.f, 0.f },
        {  0.6f, -0.4f, 0.f, 1.f, 0.f },
        {   0.f,  0.6f, 0.f, 0.f, 1.f }
    };


    static const char* vertex_shader_text =
        "#version 110\n"
        "uniform mat4 MVP;\n"
        "attribute vec3 vCol;\n"
        "attribute vec2 vPos;\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
        "    color = vCol;\n"
        "}\n";


    static const char* fragment_shader_text =
        "#version 110\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(color, 1.0);\n"
        "}\n";


    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
    GLFWwindow* mWindow;



    static void error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }


    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }


    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {

    }

    
    void GWindow::RenderProcess()
    {
        glfwMakeContextCurrent(mWindow);
        gladLoadGL(glfwGetProcAddress);
        glfwSwapInterval(1);


        //shader compile
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
        glCompileShader(vertex_shader);

        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
        glCompileShader(fragment_shader);

        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);
      
        //
        mvp_location = glGetUniformLocation(program, "MVP");
        vpos_location = glGetAttribLocation(program, "vPos");
        vcol_location = glGetAttribLocation(program, "vCol");

        glEnableVertexAttribArray(vpos_location);
        glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
        glEnableVertexAttribArray(vcol_location);
        glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)(sizeof(float) * 2));


        // ʹ��ѭ���ﵽѭ����ȾЧ��
        while (1)
        {
            float ratio;
            int width, height;
            mat4x4 m, p, mvp;

            glfwGetFramebufferSize(mWindow, &width, &height);
            ratio = width / (float)height;

            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);

            mat4x4_identity(m);
            mat4x4_rotate_Z(m, m, (float)glfwGetTime());
            mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
            mat4x4_mul(mvp, p, m);

            glUseProgram(program);
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(mWindow);
            glfwPollEvents();
        }
    }


    void GWindow::StartRender()
    {
        std::thread worker = std::thread(&GWindow::RenderProcess, this);
        worker.detach();
    }


	int GWindow::OpenWindow(int parentWindow, int width, int height, bool isVisibile = false)
	{
        if (width == 0 || height == 0) return 0;

        glfwSetErrorCallback(error_callback);
       
        //glfw��ʼ��
        if (!glfwInit()) return -1;

        //��������
        //
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        int visible = isVisibile ? GLFW_TRUE : GLFW_FALSE;
        glfwWindowHint(GLFW_VISIBLE, visible);

        //�򿪴���
        mWindow = glfwCreateWindow(width, height, "", NULL, NULL);
        glfwSetCursorPosCallback(mWindow, cursor_position_callback);
        HWND window_handle = glfwGetWin32Window(mWindow);


        StartRender();

        int handle = (int)window_handle;
        return (int)handle;
	}

}
