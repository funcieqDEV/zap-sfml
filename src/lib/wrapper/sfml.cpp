#include "sfml.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cstdint>

namespace {
sf::Clock startClock;
}

extern "C" {

struct SwWindow {
    sf::RenderWindow* win;
};

struct SwRectangle {
    sf::RectangleShape* shape;
};

struct SwCircle {
    sf::CircleShape* shape;
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

void sw_window_draw_rectangle(SwWindow* cw, const SwRectangle* rect) {
    if (cw && rect && rect->shape) cw->win->draw(*rect->shape);
}

void sw_window_draw_circle(SwWindow* cw, const SwCircle* circ){
    if (cw && circ && circ->shape) cw->win->draw(*circ->shape);
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

bool sw_keyboard_is_key_pressed(int32_t key) {
    if (key < 0 || key >= sf::Keyboard::KeyCount) return false;
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
}
// shapes
SwRectangle* sw_rectangle_create(float width, float height) {
    SwRectangle* rect = new SwRectangle;
    rect->shape = new sf::RectangleShape(sf::Vector2f(width, height));
    return rect;
}

void sw_rectangle_destroy(SwRectangle* rect) {
    if (!rect) return;
    delete rect->shape;
    delete rect;
}

void sw_rectangle_set_size(SwRectangle* rect, float width, float height) {
    if (rect && rect->shape) rect->shape->setSize(sf::Vector2f(width, height));
}

void sw_rectangle_set_position(SwRectangle* rect, float x, float y) {
    if (rect && rect->shape) rect->shape->setPosition(x, y);
}

void sw_rectangle_move(SwRectangle* rect, float dx, float dy) {
    if (rect && rect->shape) rect->shape->move(dx, dy);
}

void sw_rectangle_set_fill_color(SwRectangle* rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    if (rect && rect->shape) rect->shape->setFillColor(sf::Color(r, g, b, a));
}

SwCircle* sw_circle_create(float radius){
    SwCircle* circ = new SwCircle;
    circ->shape = new sf::CircleShape(radius);
    return  circ;
}

void sw_circle_destroy(SwCircle* circ){
    if(!circ) return;
    delete circ->shape;
    delete circ;
}

void sw_circle_set_size(SwCircle* circ, float radius){
    if (circ && circ->shape) circ->shape->setRadius(radius);
}

void sw_circle_set_position(SwCircle* circ, float x, float y){
    if(circ && circ->shape) circ->shape->setPosition(x,y);
}

void sw_circle_move(SwCircle* circ, float dx, float dy){
    if(circ && circ->shape) circ->shape->move(dx,dy);
}

void sw_circle_set_fill_color(SwCircle* circ, uint8_t r, uint8_t g, uint8_t b, uint8_t a){
    if(circ && circ->shape) circ->shape->setFillColor(sf::Color(r,g,b,a));
}

} // extern "C"
