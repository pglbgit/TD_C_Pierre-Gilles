#ifndef I_CRCULAR_BUFFER_REPOSITORY_H
#define I_CIRCULAR_BUFFER_REPOSITORY_H

#include "class.h"

CLASS(circular_buffer);

extern int ICircularBufferRepository_save(circular_buffer cb);
extern circular_buffer ICircularBufferlRepository_get_nth_cb(int rank);
extern void ICircularBufferRepository_close();
extern int ICircularBufferRepository_open(char *name);
extern int ICircularBufferRepository_append(circular_buffer record);

#endif