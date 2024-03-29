#include "service_channel.h"
#include "chart_points.h"
#include "colorscheme.h"
#include "common_functions.h"
#include "text.h"
#include <SDL2/SDL_rect.h>
#include <assert.h>

struct schannel *schannel_init(SDL_Point position, int32_t channel_number,
                               char16_t const *plot0_name,
                               char16_t const *plot1_name) {
  struct schannel *schannel = malloc(sizeof *schannel);

  SDL_Rect pos_num = {.x = position.x + 26, .y = position.y + 67};

  SDL_Point pos_plot0_body = {.x = 130 + pos_num.x, .y = pos_num.y - 25};
  schannel->plot0 = plot_init(pos_plot0_body, plot0_name);

  SDL_Point pos_plot1_body = {.x = pos_plot0_body.x +
                                   schannel->plot0->position.w + 73,
                              .y = pos_num.y - 25};
  schannel->plot1 = plot_init(pos_plot1_body, plot1_name);
  schannel->state = true;

  char channel_number_s[50] = {u'\0'};
  sprintf(channel_number_s, "%d", channel_number);

  // body
  schannel->number = text8_init(
      text_get_font_type(TEXT_FONT_BOLD), 150, COLOR_CHANNEL_NUMBER_ON,
      (SDL_Point){.x = pos_num.x, .y = pos_num.y}, channel_number_s);

  return schannel;
}

void schannel_free(struct schannel *schannel) {
  assert(schannel);

  plot_free(schannel->plot0);
  plot_free(schannel->plot1);
  text8_free(schannel->number);
  free(schannel);
  schannel = NULL;
}

struct vec_schannel *vec_schannel_init(size_t count, SDL_Point position) {
  struct vec_schannel *vec = malloc(sizeof *vec);
  vec->count = count;
  vec->channels = malloc(sizeof(struct schannel *) * count);

  SDL_Point dpos = position;
  for (size_t i = 0; i < count; ++i) {
    vec->channels[i] = schannel_init(dpos, i + 1, u"Tx", u"Rx");

    if (!is_even(i)) {
      dpos.y += 244;
      dpos.x -= 654 * 2;
    }

    dpos.x += 654;
  }

  return vec;
}

void vec_schannel_free(struct vec_schannel *vec) {
  assert(vec);

  for (size_t i = 0; i < vec->count; ++i) {
    schannel_free(vec->channels[i]);
    vec->channels[i] = NULL;
  }

  free(vec->channels);
  vec->channels = NULL;

  free(vec);
}

void off_schannel(struct vec_schannel *vec, int sch_idx) {
  struct schannel *sch = vec->channels[sch_idx];
  if (sch->state == false)
    return;
  sch->state = false;

  text8_change_color(sch->number, COLOR_CHANNEL_NUMBER_OFF);
}

void on_schannel(struct vec_schannel *vec, int sch_idx) {
  struct schannel *sch = vec->channels[sch_idx];
  if (sch->state == true)
    return;
  sch->state = true;

  text8_change_color(sch->number, COLOR_CHANNEL_NUMBER_ON);
}
