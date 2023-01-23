#pragma once
#include "SDL2/SDL.h"
#include <SDL2/SDL_rect.h>
#include <stdbool.h>

struct rchannel {
  SDL_Point position;
  SDL_Point dpos;
  struct plot *plot0;
  struct plot *plot1;
  bool state;

  struct {
    SDL_Texture *texture;
    SDL_Rect position;
    int32_t value;
  } number;
};

struct rchannel *rchannel_init(SDL_Point position, int32_t channel_number,
                               char const *plot0_name, char const *plot1_name);

void rchannel_free(struct rchannel *rchannel);

struct vec_rchannel {
  struct rchannel **rchs;
  size_t count;
};

struct vec_rchannel *vec_rchannel_init(size_t count, SDL_Point position);
void vec_rchannel_free(struct vec_rchannel *vec);
void off_rchannel(struct vec_rchannel *vec, int rch_idx);
