#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SwWindow SwWindow;

SwWindow* sw_window_create(unsigned int width, unsigned int height, const char* title);
void sw_window_destroy(SwWindow* w);
bool sw_window_is_open(const SwWindow* w);
void sw_window_close(SwWindow* w);
void sw_window_display(SwWindow* w);
void sw_window_clear(SwWindow* w, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void sw_window_set_framerate_limit(SwWindow* w, unsigned int limit);

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

#ifdef __cplusplus
}
#endif
