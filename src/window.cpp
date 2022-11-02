#include "core.h"
#include "window.h"
//#include "event.h"
//#include <GLFW/glfw3.h>
#include <signal.h>

void ErrorCallback(int error, const char *description)
{
    std::cout << "[Window Error] "
        << "Error: " << error << "\n"
        << description << std::endl;
}

Window::Window(const std::string &title, int width, int height)
    : m_Attributes(WindowAttributes(title, width, height))
{
    userData.title = title;
    userData.title = width;
    userData.title = height;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // if already initted (probably another window), do not init again
    if (!glfwInitialized)
    {
    // glfw needs to be innited correctly before window can be created
        int result = glfwInit();
        PASSERT(result);

        glfwInitialized = true;
    }

    wnd = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(wnd);

    glfwSetWindowUserPointer(wnd, &userData);
    glfwSetErrorCallback(ErrorCallback);
    //glfwSwapInterval(1);
    //SetSwapInterval(1);
    glfwSetKeyCallback(wnd, [](GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            UserData &udata = *(UserData *)glfwGetWindowUserPointer(window);

            KeyEvent event(key, scancode, action, mods);
            switch (action)
            {
            case GLFW_PRESS:
                event.eventType = EventType::KEY_PRESSED;
                break;
            case GLFW_RELEASE:
                event.eventType = EventType::KEY_RELEASED;
                break;
            case GLFW_REPEAT:
                event.eventType = EventType::KEY_REPEAT;
                break;
            }

            udata.callback(event);
        });

    glfwSetMouseButtonCallback(wnd, [](GLFWwindow *window, int button, int action, int mods)
        {
            UserData &udata = *(UserData *)glfwGetWindowUserPointer(window);
            MouseButtonEvent event(button, action, mods);
            switch (action)
            {
            case GLFW_PRESS:
                event.eventType = EventType::MOUSE_BUTTON_PRESSED;
                break;
            case GLFW_RELEASE:
                event.eventType = EventType::MOUSE_BUTTON_RELEASED;
                break;
            }
            udata.callback(event);
        });

    glfwSetCursorPosCallback(wnd, [](GLFWwindow *window, double xpos, double ypos)
        {
            UserData &udata = *(UserData *)glfwGetWindowUserPointer(window);
            MouseMotionEvent event(xpos, ypos);

            udata.callback(event);
        });

    glfwSetScrollCallback(wnd, [](GLFWwindow *window, double xoffset, double yoffset)
        {

            UserData &udata = *(UserData *)glfwGetWindowUserPointer(window);
            MouseScrollEvent event(xoffset, yoffset);
            udata.callback(event);
        });

    // glfwSetWindowSizeCallback(wnd, [](GLFWwindow *window, int width, int height)
    //     {
    //         UserData &udata = *(UserData *)glfwGetWindowUserPointer(window);
    //         WindowResizeEvent event(width, height);
    //         udata.width = width;
    //         udata.height = height;
    //         udata.callback(event);
    //     });

    glfwSetFramebufferSizeCallback(wnd, [](GLFWwindow *window, int width, int height)
        {
            UserData &udata = *(UserData *)glfwGetWindowUserPointer(window);
            WindowResizeEvent event(width, height);
            udata.width = width;
            udata.height = height;
            udata.callback(event);
        });

    SetDefaultWindowHints();
}

Window::~Window()
{
    glfwDestroyWindow(wnd);
    glfwTerminate();
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(wnd) != 0;
}

void Window::pollEvents() const
{
    glfwPollEvents();
}

void Window::OnUpdate()
{
    swapBuffers();
    pollEvents();
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(wnd);
}

void Window::SetSwapInterval(int interval) const
{
    glfwSwapInterval(interval);
}

void Window::SetWindowHint(int hint, int value) const
{
    glfwWindowHint(hint, value);
}

void Window::SetDefaultWindowHints() const
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
void Window::SetWindowSizeChanged(int width, int height)
{
    m_Attributes.Width = width;
    m_Attributes.Height = height;
}
std::pair<int, int> Window::getWindowSize() const
{
    std::pair<int, int> sz{ m_Attributes.Width, m_Attributes.Height };
    return sz;
}

void Window::SetEventCallback(const EventCallbackFn &fn)
{
    userData.callback = fn;
}