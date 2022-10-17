#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "i_digital_wheel_repository.h"
#include "digital_wheel_infra_file_service.h"
#include "i_digital_wheel.h"

#define INDEX_SUFFIX ".ndx"
#define DATA_SUFFIX ".rec"
#define FILE_DB_REPO "../Persistence/FileDB/DigitalWheel/TWO_WHEELS"

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

struct index
{
    long recordStart;
    size_t recordLength;
};

static FILE *index_stream;
static FILE *data_stream;

int IDigitalWheelRepository_save(twoWheels two)
{
    digital_wheel w1 = two->wheel1;
    digital_wheel w2 = two->wheel2;
    if (!IDigitalWheelRepository_open(FILE_DB_REPO))
        return 0;
    IDigitalWheelRepository_append(w1);
    IDigitalWheelRepository_append(w2);

    return 1;
}

void IDigitalWheelRepository_close(void)
{
    fclose(data_stream);
    fclose(index_stream);
}

static FILE *auxiliary_open(char *prefix, char *suffix)
{
    int prefix_length = strlen(prefix);
    int suffix_length = strlen(suffix);
    char name[prefix_length + suffix_length + 1];
    strncpy(name, prefix, prefix_length);
    strncpy(name + prefix_length, suffix, suffix_length + 1);
    FILE *stream = fopen(name, "r+");
    if (stream == NULL)
        stream = fopen(name, "w+");
    if (stream == NULL)
        perror(name);
    return stream;
}

int IDigitalWheelRepository_open(char *name)
{
    data_stream = auxiliary_open(name, DATA_SUFFIX);
    if (data_stream == NULL)
        return 0;
    index_stream = auxiliary_open(name, INDEX_SUFFIX);
    if (index_stream == NULL)
    {
        fclose(data_stream);
        return 0;
    }
    return 1;
}

int IDigitalWheelRepository_append(digital_wheel record)
{
    struct index index;
    int myRecord[3] = {record->start,
                       record->end, record->current};
    size_t length = sizeof(myRecord);
    fseek(data_stream, 0L, SEEK_END);
    index.recordStart = ftell(data_stream);
    index.recordLength = length;
    fwrite(myRecord, sizeof(int), 3, data_stream);
    fseek(index_stream, 0L, SEEK_END);
    fwrite(&index, sizeof index, 1, index_stream);
    return 1;
}

digital_wheel IDigitalWheelRepository_get_nth_wheel(int rank)
{
    struct index index;
    long shift = (rank - 1) * sizeof index;
    fseek(index_stream, shift, SEEK_SET);
    fread(&index, sizeof index, 1, index_stream);
    fseek(data_stream, index.recordStart, SEEK_SET);
    int myRecord[3];
    fread(myRecord, sizeof myRecord, 1, data_stream);
    //digital_wheel dw = malloc(sizeof(struct digital_wheel));
    digital_wheel dw = DigitalWheel_construct(myRecord[0], myRecord[1]);
    DigitalWheel_change_current_position(dw, myRecord[2]);

    //dw->start = myRecord[0];
    //dw->end = myRecord[1];
    //dw->current = myRecord[2];
    return dw;
}
twoWheels IDigitalWheelRepository_get_nth_two_wheels(int rank)
{
}