extern "C" {
#include "modmu.h"
#include <py/objtuple.h>
#include <py/runtime.h>
}
#include <ion.h>
#include "apps/apps_container.h"
#include "apps/global_preferences.h"
#include "port.h"
#include "math.h"

#include "kandinsky.h"
#include "escher/palette.h"

static mp_obj_t keydown(mp_obj_t key_o) {
  Ion::Keyboard::Key key = static_cast<Ion::Keyboard::Key>(mp_obj_get_int(key_o));
  Ion::Keyboard::State state = Ion::Keyboard::scan();
  micropython_port_interrupt_if_needed();
  return mp_obj_new_bool(state.keyDown(key));
}

/*
static int keys[] = {4};

static int presses[sizeof(keys) / sizeof(keys[0])][3]; 


static mp_obj_t init_presses(mp_obj_t keys, mp_obj_t presses) {
  for (size_t i = 0; i < sizeof(keys) / sizeof(keys[0]); ++i) {
    presses[i][0] = keys[i];
    presses[i][1] = 0;
    presses[i][2] = 0;    
  }
  return presses;
}

presses = init_presses(keys,presses);


mp_obj_t modmu_presses_update() {
  for (auto& press : presses) {
    press[2] = press[1];
    K = mp_obj_get_int(press[0])
    press[1] = keydown(K);
  }
  return mp_const_none;
}

mp_obj_t modmu_click(mp_obj_t key_o) {
  return presses[key_o][2] && !presses[key_o][1];
}

mp_obj_t modmu_release(mp_obj_t key_o) {
  return presses[key_o][1] && !presses[key_o][2];
}
*/

static mp_obj_t TupleForKDColor(KDColor c) {
  mp_obj_tuple_t * t = static_cast<mp_obj_tuple_t *>(MP_OBJ_TO_PTR(mp_obj_new_tuple(3, NULL)));
  t->items[0] = MP_OBJ_NEW_SMALL_INT(c.red());
  t->items[1] = MP_OBJ_NEW_SMALL_INT(c.green());
  t->items[2] = MP_OBJ_NEW_SMALL_INT(c.blue());
  return MP_OBJ_FROM_PTR(t);
}

mp_obj_t modmu_destroy_ethan() {
  return mp_obj_new_str("Ethan successfully Destroyed!",30);
}

mp_obj_t modmu_fill(size_t n_args, const mp_obj_t * args) {
  MicroPython::ExecutionEnvironment::currentExecutionEnvironment()->displaySandbox();
  KDRect rect(0,0,320,222);
  KDColor kdColor = (n_args >= 1) ? MicroPython::Color::Parse(args[0]) : KDColorWhite;
  KDIonContext::sharedContext()->fillRect(rect, kdColor);
  return mp_const_none;
}

mp_obj_t modmu_set_led(mp_obj_t input) {
  KDColor kdColor = MicroPython::Color::Parse(input);
  Ion::LED::setColor(kdColor);
  return mp_const_none;
}

mp_obj_t modmu_get_led() {
  KDColor Kdcolor = Ion::LED::getColor();
  return TupleForKDColor(Kdcolor); 
}


// TODO :: Reactivate set_blinking function but w/ secret konami code
/*
mp_obj_t modmu_set_blinking(mp_obj_t cycleDuration, mp_obj_t blinkingPerCycle) {
  mp_float_t bpc = mp_obj_get_float(blinkingPerCycle);
  mp_uint_t cd = mp_obj_get_int(cycleDuration);
  Ion::LED::setBlinking(cd, bpc);
  return mp_const_none;
}*/


// Gen Color 

static uint32_t lcg_seed = 0xDEADBEEF; 

uint32_t custom_rand() {
    lcg_seed = lcg_seed * 1103515245 + 12345 + Ion::Timing::millis();
    return static_cast<uint32_t>(lcg_seed / 65536) % 32768;
}

mp_obj_t modmu_gen_color() {
    uint8_t r = custom_rand() % 255 + 1;
    uint8_t g = custom_rand() % 255 + 1;
    uint8_t b = custom_rand() % 255 + 1;
    KDColor c = KDColor::RGB888(r, g, b);
    return TupleForKDColor(c);
}

mp_obj_t modmu_collideRect(mp_obj_t rect1, mp_obj_t rect2) {
  mp_obj_t *rect1_items, *rect2_items;

  mp_obj_get_array_fixed_n(rect1, 5, &rect1_items);
  mp_obj_get_array_fixed_n(rect2, 5, &rect2_items);

  int x1 = mp_obj_get_int(rect1_items[0]);
  int y1 = mp_obj_get_int(rect1_items[1]);
  int w1 = mp_obj_get_int(rect1_items[2]);
  int h1 = mp_obj_get_int(rect1_items[3]);

  int x2 = mp_obj_get_int(rect2_items[0]);
  int y2 = mp_obj_get_int(rect2_items[1]);
  int w2 = mp_obj_get_int(rect2_items[2]);
  int h2 = mp_obj_get_int(rect2_items[3]);

  w1 += x1;
  h1 += y1;
  w2 += x2;
  h2 += y2;

  return mp_obj_new_bool(x1 < w2 && w1 > x2 && y1 < h2 && h1 > y2);
}

mp_obj_t modmu_collideCircle(mp_obj_t circle1, mp_obj_t circle2) {
  mp_obj_t *circle1_items, *circle2_items;     

  mp_obj_get_array_fixed_n(circle1,4,&circle1_items);
  mp_obj_get_array_fixed_n(circle2,4,&circle2_items);

  int x1 = mp_obj_get_int(circle1_items[0]);
  int y1 = mp_obj_get_int(circle1_items[1]);
  int r1 = mp_obj_get_int(circle1_items[2]);

  int x2 = mp_obj_get_int(circle2_items[0]);
  int y2 = mp_obj_get_int(circle2_items[1]);
  int r2 = mp_obj_get_int(circle2_items[2]);

  int distance_squared = pow((x1 - x2),2) + pow((y1 - y2),2);
  return mp_obj_new_bool(distance_squared <= pow((r1 + r2),2));
}

mp_obj_t modmu_collideCircleRect(mp_obj_t circle, mp_obj_t rect) {
  mp_obj_t *circle_items, *rect_items;

  mp_obj_get_array_fixed_n(circle,4,&circle_items);
  mp_obj_get_array_fixed_n(rect,5,&rect_items);

  int x1 = mp_obj_get_int(circle_items[0]);
  int y1 = mp_obj_get_int(circle_items[1]);
  int r1 = mp_obj_get_int(circle_items[2]);

  int x2 = mp_obj_get_int(rect_items[0]);
  int y2 = mp_obj_get_int(rect_items[1]);
  int w2 = mp_obj_get_int(rect_items[2]);
  int h2 = mp_obj_get_int(rect_items[3]);

  int distance_squared = pow((x1 - x2),2) + pow((y1 - y2),2);
  int x_min = x2;
  int y_min = y2;
  int x_max = x2+w2;
  int y_max = y2+h2;

  // return mp_obj_new_bool(pow((x_min - x2),2) + pow((y_min - y1),2) <= r1*r1 || pow((x_max - x2),2) + pow((y_min - y1),2) <= r1*r1 || pow((x_min - x1),2) + pow((y_max - y1),2) <= r1*r1 || pow((x_max - x1),2) + pow((y_max - y1),2) <= r1*r1 || distance_squared <= r1*r1);
  return mp_obj_new_bool(pow(x_min - x1, 2) + pow(y_min - y1, 2) <= pow(r1, 2) || pow(x_max - x1, 2) + pow(y_min - y1, 2) <= pow(r1, 2) || pow(x_min - x1, 2) + pow(y_max - y1, 2) <= pow(r1, 2) || pow(x_max - x1, 2) + pow(y_max - y1, 2) <= pow(r1, 2) || distance_squared <= pow(r1, 2));

}

mp_obj_t modmu_logo() {
  MicroPython::ExecutionEnvironment::currentExecutionEnvironment()->displaySandbox();
  KDRect rect1(0,0,333,222);
  KDIonContext::sharedContext()->fillRect(rect1, KDColorBlack);
  KDRect rect2(110,50,100,10);
  KDIonContext::sharedContext()->fillRect(rect2,KDColorWhite);
  KDRect rect3(145,50,10,100);
  KDIonContext::sharedContext()->fillRect(rect3,KDColorWhite);
  KDRect rect4(110,140,100,10);
  KDIonContext::sharedContext()->fillRect(rect4,KDColorWhite);
  KDRect rect5(120,95,70,10);
  KDIonContext::sharedContext()->fillRect(rect5,KDColorWhite);
  KDRect rect6(180,95,10,50);
  KDIonContext::sharedContext()->fillRect(rect6,KDColorWhite);
  const char * text = "- Kojiverse -";
  const KDFont * font = KDFont::LargeFont;
  KDPoint point(95,150);
  KDIonContext::sharedContext()->drawString(text, point, font, KDColorWhite, KDColorBlack);
  return mp_const_none;
}

mp_obj_t modmu_get_dir(size_t n_args, const mp_obj_t * args) {
  mp_obj_t *pos1, *pos2;
  mp_obj_get_array_fixed_n(args[0], 2, &pos1);
  mp_obj_get_array_fixed_n(args[1], 2, &pos2);
  double speed = (n_args >= 3)  ? mp_obj_get_int(args[2]) : 1;
  
  float x1 = mp_obj_get_float(pos1[0]);
  float y1 = mp_obj_get_float(pos1[1]);

  float x2 = mp_obj_get_float(pos2[0]);
  float y2 = mp_obj_get_float(pos2[1]);

  double x_diff = x2 - x1;
  double y_diff = y2 - y1;

  double norme = sqrt(pow(x_diff,2)+pow(y_diff,2))+0.000001;

  mp_obj_t dir[2];

  dir[0] = mp_obj_new_float(x_diff / norme * speed);
  dir[1] = mp_obj_new_float(y_diff / norme * speed);

  return mp_obj_new_tuple(2,dir);
}

struct key2mp
{
    Ion::Keyboard::Key key;
    mp_obj_t string;
};

const static key2mp keyMapping[] =
{
    { Ion::Keyboard::Key::Left, MP_ROM_QSTR(MP_QSTR_left) },
    { Ion::Keyboard::Key::Right, MP_ROM_QSTR(MP_QSTR_right) },
    { Ion::Keyboard::Key::Down, MP_ROM_QSTR(MP_QSTR_down) },
    { Ion::Keyboard::Key::Up, MP_ROM_QSTR(MP_QSTR_up) },
    { Ion::Keyboard::Key::OK, MP_ROM_QSTR(MP_QSTR_OK) },
    { Ion::Keyboard::Key::Back, MP_ROM_QSTR(MP_QSTR_back) },

    { Ion::Keyboard::Key::Home, MP_ROM_QSTR(MP_QSTR_home) },
    { Ion::Keyboard::Key::OnOff, MP_ROM_QSTR(MP_QSTR_onOff) },

    { Ion::Keyboard::Key::Shift, MP_ROM_QSTR(MP_QSTR_shift) },
    { Ion::Keyboard::Key::Alpha, MP_ROM_QSTR(MP_QSTR_alpha) },
    { Ion::Keyboard::Key::XNT, MP_ROM_QSTR(MP_QSTR_xnt) },
    { Ion::Keyboard::Key::Var, MP_ROM_QSTR(MP_QSTR_var) },
    { Ion::Keyboard::Key::Toolbox, MP_ROM_QSTR(MP_QSTR_toolbox) },
    { Ion::Keyboard::Key::Backspace, MP_ROM_QSTR(MP_QSTR_backspace) },

    { Ion::Keyboard::Key::Exp, MP_ROM_QSTR(MP_QSTR_exp) },
    { Ion::Keyboard::Key::Ln, MP_ROM_QSTR(MP_QSTR_ln) },
    { Ion::Keyboard::Key::Log, MP_ROM_QSTR(MP_QSTR_log) },
    { Ion::Keyboard::Key::Imaginary, MP_ROM_QSTR(MP_QSTR_imaginary) },
    { Ion::Keyboard::Key::Comma, MP_ROM_QSTR(MP_QSTR_comma) },
    { Ion::Keyboard::Key::Power, MP_ROM_QSTR(MP_QSTR_power) },

    { Ion::Keyboard::Key::Sine, MP_ROM_QSTR(MP_QSTR_sin) },
    { Ion::Keyboard::Key::Cosine, MP_ROM_QSTR(MP_QSTR_cos) },
    { Ion::Keyboard::Key::Tangent, MP_ROM_QSTR(MP_QSTR_tan) },
    { Ion::Keyboard::Key::Pi, MP_ROM_QSTR(MP_QSTR_pi) },
    { Ion::Keyboard::Key::Sqrt, MP_ROM_QSTR(MP_QSTR_sqrt) },
    { Ion::Keyboard::Key::Square, MP_ROM_QSTR(MP_QSTR_square) },

    { Ion::Keyboard::Key::Seven, MP_ROM_QSTR(MP_QSTR_7) },
    { Ion::Keyboard::Key::Eight, MP_ROM_QSTR(MP_QSTR_8) },
    { Ion::Keyboard::Key::Nine, MP_ROM_QSTR(MP_QSTR_9) },
    { Ion::Keyboard::Key::LeftParenthesis, MP_ROM_QSTR(MP_QSTR__paren_open_) },
    { Ion::Keyboard::Key::RightParenthesis, MP_ROM_QSTR(MP_QSTR__paren_close_) },

    { Ion::Keyboard::Key::Four, MP_ROM_QSTR(MP_QSTR_4) },
    { Ion::Keyboard::Key::Five, MP_ROM_QSTR(MP_QSTR_5) },
    { Ion::Keyboard::Key::Six, MP_ROM_QSTR(MP_QSTR_6) },
    { Ion::Keyboard::Key::Multiplication, MP_ROM_QSTR(MP_QSTR__star_) },
    { Ion::Keyboard::Key::Division, MP_ROM_QSTR(MP_QSTR__slash_) },

    { Ion::Keyboard::Key::One, MP_ROM_QSTR(MP_QSTR_1) },
    { Ion::Keyboard::Key::Two, MP_ROM_QSTR(MP_QSTR_2) },
    { Ion::Keyboard::Key::Three, MP_ROM_QSTR(MP_QSTR_3) },
    { Ion::Keyboard::Key::Plus, MP_ROM_QSTR(MP_QSTR__plus_) },
    { Ion::Keyboard::Key::Minus, MP_ROM_QSTR(MP_QSTR__hyphen_) },

    { Ion::Keyboard::Key::Zero, MP_ROM_QSTR(MP_QSTR_0) },
    { Ion::Keyboard::Key::Dot, MP_ROM_QSTR(MP_QSTR__dot_) },
    { Ion::Keyboard::Key::EE, MP_ROM_QSTR(MP_QSTR_EE) },
    { Ion::Keyboard::Key::Ans, MP_ROM_QSTR(MP_QSTR_Ans) },
    { Ion::Keyboard::Key::EXE, MP_ROM_QSTR(MP_QSTR_EXE) },
};

mp_obj_t modmu_get_pressed() {
  micropython_port_interrupt_if_needed();

  Ion::Keyboard::State keys = Ion::Keyboard::scan();
  mp_obj_t result = mp_obj_new_set(0, nullptr);

  for (unsigned i = 0; i < sizeof(keyMapping)/sizeof(key2mp); i++) {
      if (keys.keyDown(keyMapping[i].key)) {
          // Ajouter la valeur numérique de la touche à l'ensemble
          mp_obj_set_store(result, MP_OBJ_NEW_SMALL_INT(static_cast<mp_int_t>(keyMapping[i].key)));
      }
  }

  return result;
}

/* What is this shit ? */
// mp_obj_t modmu_brange(size_t n_args, const mp_obj_t * args) {
//   int start = (n_args >= 2)  ? mp_obj_get_int(args[0]) : 1;  
//   int stop = (n_args >= 2)  ? mp_obj_get_int(args[1])+1 : mp_obj_get_int(args[0])+1;  
//   int step = (n_args>=3) ? mp_obj_get_int(args[2]) : 1;
//   size_t size = (stop - start + step - 1) / step; 
//   if (step == 0) {
//       mp_raise_ValueError("step cannot be 0");
//   }

//   if ((step > 0 && start >= stop) || (step < 0 && start <= stop)) {
//     size = 0;
//     return nullptr;
//   }

//   mp_obj_t *items = m_new(mp_obj_t, size); 

//   for (size_t i = 0; i < size; ++i) {
//         items[i] = mp_obj_new_int(start + i * step);
//     }

//     mp_obj_t my_list = mp_obj_new_list(size, items);

//     m_del(mp_obj_t, items, size);

//     return my_list;
// }
