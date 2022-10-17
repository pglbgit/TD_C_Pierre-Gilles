#ifndef I_CIRCULAR_BUFFER_H
#define I_CIRCULAR_BUFFER_H

extern circular_buffer CircularBuffer_construct(unsigned long size);
extern void CircularBuffer_collect(circular_buffer self);
extern void CircularBuffer_append_char_at_head(circular_buffer self, char c);
extern void CircularBuffer_set_current_to_head(circular_buffer self);
extern char CircularBuffer_get_char_before_current(circular_buffer self);
extern unsigned long CircularBuffer_get_buffer_length(circular_buffer self);

#endif