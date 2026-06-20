#include "sfml.h"
#include <SFML/Graphics.hpp>

namespace {
sf::Clock startClock;
}

extern "C" {

struct SwWindow {
    sf::RenderWindow* win;
};

SwWindow* sw_window_create(unsigned int w, unsigned int h, const char* title) {
    SwWindow* cw = new SwWindow;
    cw->win = new sf::RenderWindow(sf::VideoMode(w, h), title ? title : "");
    return cw;
}

void sw_window_destroy(SwWindow* cw) {
    if (!cw) return;
    delete cw->win;
    delete cw;
}

bool sw_window_is_open(const SwWindow* cw) {
    return cw && cw->win->isOpen();
}

void sw_window_close(SwWindow* cw) {
    if (cw) cw->win->close();
}

void sw_window_display(SwWindow* cw) {
    if (cw) cw->win->display();
}

void sw_window_clear(SwWindow* cw, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    if (cw) cw->win->clear(sf::Color(r, g, b, a));
}

void sw_window_set_framerate_limit(SwWindow* cw, unsigned int limit) {
    if (cw) cw->win->setFramerateLimit(limit);
}

// Events

bool sw_window_poll_event(SwWindow* cw, SwEvent* out) {
    if (!cw || !out) return false;
    sf::Event e;
    bool ok = cw->win->pollEvent(e);
    if (!ok) return false;

    *out = {};
    out->type = SW_EVENT_COUNT;

    switch (e.type) {
    case sf::Event::Closed:
        out->type = SW_EVENT_CLOSED;
        break;
    case sf::Event::KeyPressed:
        out->type = SW_EVENT_KEY_PRESSED;
        out->key_code = static_cast<int32_t>(e.key.code);
        break;
    case sf::Event::KeyReleased:
        out->type = SW_EVENT_KEY_RELEASED;
        out->key_code = static_cast<int32_t>(e.key.code);
        break;
    case sf::Event::MouseMoved:
        out->type = SW_EVENT_MOUSE_MOVED;
        out->mouse_x = e.mouseMove.x;
        out->mouse_y = e.mouseMove.y;
        break;
    case sf::Event::MouseButtonPressed:
        out->type = SW_EVENT_MOUSE_BUTTON_PRESSED;
        out->mouse_x = e.mouseButton.x;
        out->mouse_y = e.mouseButton.y;
        out->mouse_button = static_cast<int32_t>(e.mouseButton.button);
        break;
    case sf::Event::MouseButtonReleased:
        out->type = SW_EVENT_MOUSE_BUTTON_RELEASED;
        out->mouse_x = e.mouseButton.x;
        out->mouse_y = e.mouseButton.y;
        out->mouse_button = static_cast<int32_t>(e.mouseButton.button);
        break;
    default:
        break;
    }

    return true;
}

// Time

SwTime sw_time_now(void) {
    return SwTime{ startClock.getElapsedTime().asMicroseconds() };
}

SwTime sw_time_delta_seconds(double s) {
    return SwTime{ static_cast<int64_t>(s * 1'000'000) };
}

void sw_sleep(SwTime t) {
    sf::sleep(sf::microseconds(t.microseconds));
}

} // extern "C"
