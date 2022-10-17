#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "i_circular_buffer_repository.h"
#include "circular_buffer_infra_file_service.h"
#include "i_circular_buffer.h"

#define MAX_RECORD 1024
#define INDEX_SUFFIX ".ndx"
#define DATA_SUFFIX ".rec"
#define FILE_DB_REPO "../Persistence/FileDB/CircularBuffer/CIRCULAR_BUFFER"

struct RECORD_CB
{
    unsigned long data_length;
    int offset_head;
    int offset_current;
    char data[]; //new in c99 !!
};

struct circular_buffer
{
    char *tail;
    unsigned long length;
    char *head;
    char *current;
    bool isFull;
};

struct index
{
    long recordStart;
    size_t recordLength;
};

static FILE *index_stream;
static FILE *data_stream;

int ICircularBufferRepository_save(circular_buffer cb)
{
    if (!ICircularBufferRepository_open(FILE_DB_REPO))
        return 0;
    ICircularBufferRepository_append(cb);
    return 1;
}

void ICircularBufferRepository_close(void)
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

int ICircularBufferRepository_open(char *name)
{
    data_stream = auxiliary_open(name, DATA_SUFFIX);
    if (data_stream == NULL)
        return 0;
    index_stream = auxiliary_open(name, INDEX_SUFFIX);
    if (index_stream == NULL)
    {
        fclose(index_stream);
        return 0;
    }
    return 1;   
}


 void auxiliary_get_offset(circular_buffer cb, int *Record)
{
    char * current = cb->current;
    char * head = cb->head;
    cb->current = cb->tail;
    int i_current = 0;
    int i_head = 0;

    for(int i = 0; i < cb->length ; i++){
        if(cb->current == current)
           i_current = i;
        if(cb->current == head)
           i_head = i;
        Record[i+4] = (int)cb->current ;
        cb->current++;
    }
    

    Record[2] = i_head;
    Record[3] = i_current;

  
}
// Comme on ne peut pas sauvegarder des pointeurs, j'ai choisi d'utiliser des indices, on connait le numéro de la case pointée.
// les quatres première cases de record contiennent les quatres valeurs que l'on souhaite conserver: 
// length, isFull, l'indice de head, et l'indice de current. L'indice de tail est inutile, il vaut toujours 0
// Puis on ajoute le buffer, pour le sauvegarder
int ICircularBufferRepository_append(circular_buffer cb)
{
   struct index index;
   int myRecord[4+cb->length];
   myRecord[0] = cb->length;
   myRecord[1] = cb->isFull;
   for(int i = 2; i < cb->length; i++){ // La boucle for sert a eviter un warning, elle n'a pas d'utilite 
    myRecord[i] = 0;
   }
   auxiliary_get_offset(cb, myRecord);

   size_t length = sizeof(myRecord);
   fseek(data_stream, 0L, SEEK_END);
   index.recordStart = ftell(data_stream);
   index.recordLength = length;
   fwrite(myRecord, sizeof(int), 3, data_stream);
   fseek(index_stream, 0L, SEEK_END);
   fwrite(&index, sizeof index, 1, index_stream);
    
   return 1;

}

