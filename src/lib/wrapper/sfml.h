#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SwWindow SwWindow;
typedef struct SwRectangle SwRectangle;
typedef struct SwCircle SwCircle;
typedef struct SwTexture SwTexture;
typedef struct SwSprite SwSprite;

SwWindow* sw_window_create(unsigned int width, unsigned int height, const char* title);
void sw_window_destroy(SwWindow* w);
bool sw_window_is_open(const SwWindow* w);
void sw_window_close(SwWindow* w);
void sw_window_display(SwWindow* w);
void sw_window_clear(SwWindow* w, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void sw_window_set_framerate_limit(SwWindow* w, unsigned int limit);
void sw_window_draw_rectangle(SwWindow* w, const SwRectangle* rect);
void sw_window_draw_circle(SwWindow* cw, const SwCircle* circ);
void sw_window_draw_sprite(SwWindow* w, const SwSprite* sprite);

typedef enum {
    SW_EVENT_CLOSED = 0,
    SW_EVENT_KEY_PRESSED,
    SW_EVENT_KEY_RELEASED,
    SW_EVENT_MOUSE_MOVED,
    SW_EVENT_MOUSE_BUTTON_PRESSED,
    SW_EVENT_MOUSE_BUTTON_RELEASED,
    SW_EVENT_COUNT
} SwEventType;

typedef struct {
    SwEventType type;
    int32_t key_code;       // KEY_*
    int32_t mouse_x;        // MOUSE_*
    int32_t mouse_y;
    int32_t mouse_button;   // 0=left, 1=right, 2=middle
} SwEvent;

bool sw_window_poll_event(SwWindow* w, SwEvent* out_event); //true if there is any Event


typedef struct {
    int64_t microseconds; //e.g 0.001
} SwTime;

SwTime sw_time_now(void);
SwTime sw_time_delta_seconds(double seconds);
void sw_sleep(SwTime t);

bool sw_keyboard_is_key_pressed(int32_t key);

SwRectangle* sw_rectangle_create(float width, float height);
void sw_rectangle_destroy(SwRectangle* rect);
void sw_rectangle_set_size(SwRectangle* rect, float width, float height);
void sw_rectangle_set_position(SwRectangle* rect, float x, float y);
void sw_rectangle_move(SwRectangle* rect, float dx, float dy);
void sw_rectangle_set_fill_color(SwRectangle* rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

SwCircle* sw_circle_create(float radius);
void sw_circle_destroy(SwCircle* rect);
void sw_circle_set_size(SwCircle* circ, float radius);
void sw_circle_set_position(SwCircle* circ, float x, float y);
void sw_circle_move(SwCircle* rect, float dx, float dy);
void sw_circle_set_fill_color(SwCircle* circ, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

SwTexture* sw_texture_create(void);
void sw_texture_destroy(SwTexture* tex);
bool sw_texture_load_from_file(SwTexture* tex, const char* path);
void sw_texture_get_size(const SwTexture* tex, unsigned int* w, unsigned int* h);

SwSprite* sw_sprite_create(const SwTexture* tex);
void sw_sprite_destroy(SwSprite* spr);
void sw_sprite_set_texture(SwSprite* spr, const SwTexture* tex);
void sw_sprite_set_position(SwSprite* spr, float x, float y);
void sw_sprite_move(SwSprite* spr, float dx, float dy);
void sw_sprite_set_scale(SwSprite* spr, float sx, float sy);
void sw_sprite_set_rotation(SwSprite* spr, float angle);
void sw_sprite_set_color(SwSprite* spr, uint8_t r, uint8_t g, uint8_t b, uint8_t a);


#ifdef __cplusplus
}
#endif
