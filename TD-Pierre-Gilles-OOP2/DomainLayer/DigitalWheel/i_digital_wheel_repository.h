#ifndef I_DIGITAL_WHEEL_REPOSITORY_H
#define I_DIGITAL_WHEEL_REPOSITORY_H

#include "class.h"

CLASS(digital_wheel);
CLASS(twoWheels);
extern int IDigitalWheelRepository_save(twoWheels twoheels);
extern digital_wheel IDigitalWheelRepository_get_nth_wheel(int rank);
extern int IDigitalWheelRepository_delete_nth_wheel(int rank);
extern void IDigitalWheelRepository_close();
extern int IDigitalWheelRepository_open(char *name);
extern int IDigitalWheelRepository_append(digital_wheel record);
extern twoWheels IDigitalWheelRepository_get_nth_two_wheels(int rank);
#endif