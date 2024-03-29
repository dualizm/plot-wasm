#pragma once
#include "chart_points.h"
#include "text.h"
#include <SDL2/SDL.h>

struct plot {
  SDL_Rect position;
  SDL_Texture *background;
  struct text16 *name;
  struct chart_points *vcharts;
  struct chart_points *hcharts;
  int index;

  struct {
    SDL_FPoint *data;
    size_t length;
    float dx;
    float x0;
  } fft;
};

struct plot *plot_init(SDL_Point position, char16_t const *name);
void plot_free(struct plot *plot);

void plot_fft_update(struct plot *plot, float const *data, int length, float dx,
                     float x0);
