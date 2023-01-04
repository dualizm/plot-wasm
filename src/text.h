#pragma once

#include <SDL2/SDL_ttf.h>
#include <stdint.h>

#define TEXT_FONT_REGULAR "res/Gilroy-Regular.ttf"
#define TEXT_FONT_BOLD "res/Gilroy-Bold.ttf"

struct text {
  TTF_Font *font;
  SDL_Texture *texture;
  SDL_Color color;
  SDL_Rect position;
};

struct text *text_crealloc(char const *font_path, int32_t font_size,
                           SDL_Color color, SDL_Rect position,
                           char const *text);
void text_free(struct text *text);

void text_change(struct text *text, char const *info);
