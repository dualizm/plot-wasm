#pragma once
#include "channel.h"
#include <SDL2/SDL.h>
#include <stdint.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_KEEPALIVE
#endif
void set_fps(int fps);

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_KEEPALIVE
#endif
void push_data(char const *data);

void handle_events(void);

typedef struct Graphics {
  int32_t const width;
  int32_t const height;
  int32_t const width_mid;
  int32_t const height_mid;
  int32_t fps;
  // channel_t **
  channel_t **channels;
} graphics_t;

graphics_t *Graphics_init(int32_t width, int32_t height, int32_t fps);
void Graphics_free(graphics_t *graphics);
