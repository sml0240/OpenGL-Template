#pragma once
#include "pch.h"
#include "event.h"


// Forward declare GLFWwindow to avoid including glfw3.h
struct GLFWwindow;

struct WindowAttributes
{
    WindowAttributes(const std::string &title, int width, int height)
        : Title(title), Width(width), Height(height)
    {
    }

public:
    std::string Title;
    int Width;
    int Height;
};


class Window
{

public:
    using EventCallbackFn = std::function<void(Event &)>;

    Window(const std::string &title, int width, int height);
    ~Window();

    bool shouldClose() const;

    void OnUpdate();

    void pollEvents() const;

    void swapBuffers() const;

    void SetSwapInterval(int interval) const;

    void SetWindowHint(int hint, int value) const;

    void SetDefaultWindowHints() const;
    
    std::pair<int, int> getWindowSize() const;

    void SetWindowSizeChanged(int width, int height);

    inline GLFWwindow *GetWindow() { return wnd; }
    inline int getWidth() { return m_Attributes.Width; }
    inline int getHeight() { return m_Attributes.Height; }
    void SetEventCallback(const EventCallbackFn &fn);
    void SetUserData(std::string &title, int width, int height, EventCallbackFn &callback);

private:
    const int OPENGL_MAJOR_VERSION = 4;
    const int OPENGL_MINOR_VERSION = 5;

    struct UserData
    {
        std::string title;
        int width, height;
        EventCallbackFn callback;
    };

    UserData userData;
    GLFWwindow *wnd;
    WindowAttributes m_Attributes;
    bool glfwInitialized = false;
public:

    inline UserData *GetUserData() { return &userData; }
};