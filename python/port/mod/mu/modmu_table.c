#include "modmu.h"

STATIC MP_DEFINE_CONST_FUN_OBJ_0(modmu_destroy_ethan_obj, modmu_destroy_ethan);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(modmu_get_led_obj, modmu_get_led);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(modmu_set_led_obj, modmu_set_led);
// STATIC MP_DEFINE_CONST_FUN_OBJ_2(modmu_set_blinking_obj, modmu_set_blinking);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(modmu_gen_color_obj, modmu_gen_color);
STATIC MP_DEFINE_CONST_FUN_OBJ_2(modmu_collideRect_obj, modmu_collideRect);
STATIC MP_DEFINE_CONST_FUN_OBJ_2(modmu_collideCircle_obj, modmu_collideCircle);
STATIC MP_DEFINE_CONST_FUN_OBJ_2(modmu_collideCircleRect_obj, modmu_collideCircleRect);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(modmu_logo_obj, modmu_logo);
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(modmu_fill_obj,0,1,modmu_fill);
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(modmu_get_dir_obj,2,3,modmu_get_dir);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(modmu_get_pressed_obj, modmu_get_pressed);
// STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(modmu_brange_obj, 1,3,modmu_brange);

STATIC const mp_rom_map_elem_t modmu_module_globals_table[] = {
  { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_mu) },
  { MP_ROM_QSTR(MP_QSTR_destroy_ethan), (mp_obj_t)&modmu_destroy_ethan_obj },
  { MP_ROM_QSTR(MP_QSTR_set_led), (mp_obj_t)&modmu_set_led_obj },
  { MP_ROM_QSTR(MP_QSTR_get_led), (mp_obj_t)&modmu_get_led_obj },
  { MP_ROM_QSTR(MP_QSTR_gen_color), (mp_obj_t)&modmu_gen_color_obj },
  //{ MP_ROM_QSTR(MP_QSTR_set_blinking), (mp_obj_t)&modmu_set_blinking_obj },
  { MP_ROM_QSTR(MP_QSTR_collideRect), (mp_obj_t)&modmu_collideRect_obj },
  { MP_ROM_QSTR(MP_QSTR_collideCircle), (mp_obj_t)&modmu_collideCircle_obj },
  { MP_ROM_QSTR(MP_QSTR_collideCircleRect), (mp_obj_t)&modmu_collideCircleRect_obj },
  { MP_ROM_QSTR(MP_QSTR_logo), (mp_obj_t)&modmu_logo_obj },
  { MP_ROM_QSTR(MP_QSTR_fill), (mp_obj_t)&modmu_fill_obj },
  { MP_ROM_QSTR(MP_QSTR_get_dir), (mp_obj_t)&modmu_get_dir_obj}, 
  { MP_ROM_QSTR(MP_QSTR_get_pressed), (mp_obj_t)&modmu_get_pressed_obj }
  // { MP_ROM_QSTR(MP_QSTR_brange), (mp_obj_t)&modmu_brange_obj }

};

STATIC MP_DEFINE_CONST_DICT(modmu_module_globals, modmu_module_globals_table);

const mp_obj_module_t modmu_module = {
  .base = { &mp_type_module },
  .globals = (mp_obj_dict_t*)&modmu_module_globals,
};