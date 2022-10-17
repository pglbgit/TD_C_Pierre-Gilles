#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "circular_buffer_app_service.h"
#include "circular_buffer_infra_file_service.h"
#include "i_circular_buffer_repository.h"
#include "i_circular_buffer.h"

struct circular_buffer
{
    char *tail;
    unsigned long length;
    char *head;
    char *current;
    bool isFull;
};

static circular_buffer cb;
//static circular_buffer cb;
static void generate_next_int()
{
    printf("\n[%d]: ", generator_get_next());
}

static void create(int length)
{
    cb = CircularBuffer_construct(length);
}

void CircularBufferAppService_run_use_case(int c)
{
    if (cb == NULL)
        generate_next_int();

    switch (c)
    {
    case GO_TO_HEAD:
        CircularBuffer_set_current_to_head(cb);
        break;

    case DISPLAY_PRECEDENT:
        printf("(%c)", CircularBuffer_get_char_before_current(cb));
        break;

    case DESTROY_CIRCULAR_BUFFER:
        CircularBuffer_collect(cb);
        break;

    case NEW_CIRCULAR_BUFFER:
        create(CIRCULAR_BUFFER_LENGTH);
        break;

    case SAVE_CIRCULAR_BUFFER:
        ICircularBufferRepository_save(cb);
        ICircularBufferRepository_close();
        break;

    case '\n':
        generate_next_int();
    case ' ':
    case '\t':
        break;

    default:
        CircularBuffer_append_char_at_head(cb, c);
        break;
    }
}
