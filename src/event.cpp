#include "event.h"


Event::Event() {}

Event::~Event() {}

EventType Event::GetEventType()
{
    return eventType;
}

EventClass Event::GetEventClass()
{
    return eventClass;
}

KeyEvent::KeyEvent(int key, int scancode, int action, int mods)
    : key(key), scancode(scancode), action(action), mods(mods)
{
    this->eventClass = EventClass::KEYBOARD_EVENT;
}

KeyEvent::~KeyEvent() {}

MouseButtonEvent::MouseButtonEvent(int button, int action, int mods)
    : button(button), action(action), mods(mods)
{
    this->eventClass = EventClass::MOUSE_EVENT;
}

MouseButtonEvent::~MouseButtonEvent() {}


MouseMotionEvent::MouseMotionEvent(double posX, double posY)
    : posX(posX), posY(posY)
{
    this->eventClass = EventClass::MOUSE_EVENT;
    this->eventType = EventType::MOUSE_MOTION;
}

MouseMotionEvent::~MouseMotionEvent() {}


MouseScrollEvent::MouseScrollEvent(double xoffset, double yoffset)
    : xoffset(xoffset), yoffset(yoffset)
{
    this->eventClass = EventClass::MOUSE_EVENT;
    this->eventType = EventType::MOUSE_SCROLL;
}

MouseScrollEvent::~MouseScrollEvent() {}


WindowCloseEvent::WindowCloseEvent()
{
    this->eventClass = EventClass::WINDOW_EVENT;
    this->eventType = EventType::WINDOW_CLOSED;
}
WindowCloseEvent::~WindowCloseEvent() {}

WindowResizeEvent::WindowResizeEvent(int width, int height)
    : width(width), height(height)
{
    this->eventClass = EventClass::WINDOW_EVENT;
    this->eventType = EventType::WINDOW_RESIZED;
}
WindowResizeEvent::~WindowResizeEvent() {}

