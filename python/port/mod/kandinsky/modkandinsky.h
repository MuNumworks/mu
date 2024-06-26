#include <py/obj.h>

mp_obj_t modkandinsky_color(size_t n_args, const mp_obj_t *args);
mp_obj_t modkandinsky_get_pixel(mp_obj_t x, mp_obj_t y);
mp_obj_t modkandinsky_set_pixel(mp_obj_t x, mp_obj_t y, mp_obj_t color);
mp_obj_t modkandinsky_draw_string(size_t n_args, const mp_obj_t *args);
mp_obj_t modkandinsky_draw_line(size_t n_args, const mp_obj_t *args);
mp_obj_t modkandinsky_draw_circle(size_t n_args, const mp_obj_t *args);
mp_obj_t modkandinsky_fill_rect(size_t n_args, const mp_obj_t *args);
mp_obj_t modkandinsky_fill_circle(size_t n_args, const mp_obj_t *args);
mp_obj_t modkandinsky_fill_polygon(size_t n_args, const mp_obj_t *args);
mp_obj_t modkandinsky_wait_vblank();
mp_obj_t modkandinsky_get_keys();
mp_obj_t modkandinsky_get_palette();
// mp_obj_t modkandinsky_gen_color();
