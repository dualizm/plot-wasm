#pragma once
#include "text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>

struct plot {
  SDL_Rect position;
  SDL_Texture *background;
  struct text *name;

  struct {
    SDL_FPoint *data;
    size_t length;
    float dx;
    float x0;
  } fft;
};

struct plot *plot_init(SDL_Point position, char const *name);
void plot_free(struct plot *plot);

void plot_fft_update(struct plot *plot, float *data, int length, float dx,
                     float x0);
