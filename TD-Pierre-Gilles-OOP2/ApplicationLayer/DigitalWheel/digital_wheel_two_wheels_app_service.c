#include <stdlib.h>
#include <stdio.h>
#include "instantiate.h"
#include "i_digital_wheel_repository.h"
#include "digital_wheel_two_wheels_app_service.h"
#include "digital_wheel_infra_file_service.h"

struct digital_wheel
{
    int start;
    int end;
    int current;
};

struct twoWheels
{
    digital_wheel wheel1;
    digital_wheel wheel2;
};

static void
display(digital_wheel wheel, void (*f)(int));

twoWheels DigitalWheelAppService_two_wheels_construct(int start, int max)
{
    INSTANTIATE(twoWheels);
    self->wheel1 = DigitalWheel_construct(start, max);
    self->wheel2 = DigitalWheel_construct(start, max);
    return self;
}
void DigitalWheelAppService_two_wheels_collect(twoWheels self)
{
    free(self->wheel1);
    free(self->wheel2);
    free(self);
}

void DigitalWheelAppService_two_wheels_initialize(twoWheels self)
{
    DigitalWheel_initialize(self->wheel1);
    DigitalWheel_initialize(self->wheel2);
}

void DigitalWheelAppService_two_wheels_move(twoWheels self, int wheel_speed1, int wheel_speed2)
{
    while (wheel_speed1-- > 0)
        DigitalWheel_move_to_next_position(self->wheel1);

    while (wheel_speed2-- > 0)
        DigitalWheel_move_to_next_position(self->wheel2);
}

void DigitalWheelAppService_two_wheels_display(twoWheels self, void (*f)(int))
{
    display(self->wheel1, f);
    display(self->wheel2, f);
}

static void display(digital_wheel wheel, void (*f)(int))
{

    f(DigitalWheel_get_current_position(wheel));
}

twoWheels DigitalWheelAppService_get_nth_two_wheels(int rank)
{
    /* another way: call IDigitalWheelRepository_get_nth_two_wheels *
    /* to construct a two_wheels directly.But,I did not implement it */

    digital_wheel wheel1 = IDigitalWheelRepository_get_nth_wheel(rank);
    digital_wheel wheel2 = IDigitalWheelRepository_get_nth_wheel(rank + 1);

    twoWheels tw = DigitalWheelAppService_two_wheels_construct(DigitalWheel_get_start_position(wheel1),
                                                               DigitalWheel_get_end_position(wheel1));
    DigitalWheel_change_current_position(tw->wheel1, DigitalWheel_get_current_position(wheel1));
    DigitalWheel_change_current_position(tw->wheel2, DigitalWheel_get_current_position(wheel2));

    return tw;
}
