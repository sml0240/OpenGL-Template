#pragma once

#define GET_EVENT_NAME(x) #x

enum class EventType
{
    KEY_PRESSED = 0,
    KEY_RELEASED,
    KEY_REPEAT,
    MOUSE_BUTTON_PRESSED,
    MOUSE_BUTTON_RELEASED,
    MOUSE_MOTION,
    MOUSE_SCROLL,
    WINDOW_RESIZED,
    WINDOW_CLOSED,
};
enum class EventClass
{
    KEYBOARD_EVENT = 0,
    MOUSE_EVENT,
    WINDOW_EVENT,
    APPLICATION_EVENT,
    MOUSE_SCROLL_EVENT,
};

class Event
{
public:
    Event();
    ~Event();
    //// EVENTTYPE IS NOT IN USE
    EventType eventType;
    EventType GetEventType();
    //// EVENTCLASS IS IN USE
    EventClass GetEventClass();
    EventClass eventClass;

    template<typename T>
    inline T EventCast(Event *event)
    {
        return static_cast<T>(event);
    }
};

class KeyEvent : public Event
{
public:
    KeyEvent(int key, int scancode, int action, int mods);
    ~KeyEvent();

    int key = 0, scancode = 0, action = 0, mods = 0;
};

class MouseButtonEvent : public Event
{
public:
    MouseButtonEvent(int button, int action, int mods);
    ~MouseButtonEvent();
    int button = 0, action = 0, mods = 0;
};

class MouseMotionEvent : public Event
{
public:
    MouseMotionEvent(double posX, double posY);
    ~MouseMotionEvent();
    double posX = 0.0, posY = 0.0;
};
class MouseScrollEvent : public Event
{
public:
    MouseScrollEvent(double xoffset, double yoffset);
    ~MouseScrollEvent();
    double xoffset = 0.0, yoffset = 0.0;
};
class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent();
    ~WindowCloseEvent();
    // double posX = 0.0, posY = 0.0;
};
class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(int width, int height);
    ~WindowResizeEvent();
    int width = 0, height = 0;
};