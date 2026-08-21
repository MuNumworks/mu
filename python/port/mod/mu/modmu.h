#include <py/obj.h>

mp_obj_t modmu_destroy_ethan();
mp_obj_t modmu_set_led(mp_obj_t input);
mp_obj_t modmu_get_led();
mp_obj_t modmu_gen_color();
//mp_obj_t modmu_set_blinking(mp_obj_t cycleDuration, mp_obj_t blinkingPerCycle);
mp_obj_t modmu_collideRect(mp_obj_t rect1, mp_obj_t rect2);
mp_obj_t modmu_collideCircle(mp_obj_t circle1, mp_obj_t circle2);
mp_obj_t modmu_collideCircleRect(mp_obj_t circle, mp_obj_t rect);
mp_obj_t modmu_logo();
mp_obj_t modmu_fill(size_t n_args, const mp_obj_t * args);
mp_obj_t modmu_get_dir(size_t n_args, const mp_obj_t * args);
mp_obj_t modmu_get_pressed();

// mp_obj_t modmu_brange(size_t n_args, const mp_obj_t * args);
// mp_obj_t modmu_get_nearest(mp_obj_t pos, mp_obj_t list_pos);
// mp_obj_t modmu_presses_update();
// mp_obj_t modmu_click(mp_obj_t key_o);
// mp_obj_t modmu_release(mp_obj_t key_o);
// mp_obj_t modmu_init_presses();
