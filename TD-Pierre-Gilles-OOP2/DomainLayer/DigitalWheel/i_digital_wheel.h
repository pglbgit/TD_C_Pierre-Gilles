#ifndef I_DIGITAL_WHEEL_H
#define I_DIGITAL_WHEEL_H
#include <stdint.h>
#include <stdbool.h>

extern digital_wheel DigitalWheel_construct(int32_t start, int32_t end);
extern void DigitalWhheel_collect(digital_wheel self);

extern void DigitalWheel_initialize(digital_wheel self);
extern bool DigitalWheel_move_to_next_position(digital_wheel self);
extern int32_t DigitalWheel_get_current_position(digital_wheel self);

extern int32_t DigitalWheel_get_end_position(digital_wheel self);
extern int32_t DigitalWheel_get_start_position(digital_wheel self);
void DigitalWheel_change_current_position(digital_wheel self, int32_t current);
#endif