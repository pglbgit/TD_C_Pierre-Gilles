#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "digital_wheel_two_wheels_app_service.h"
#include "i_digital_wheel_repository.h"
#include "generator.h"

#define FILE_DB_REPO "../Persistence/FileDB/DigitalWheel/TWO_WHEELS"

#define MOVE '>'
#define SAVE '!'
#define READ '<'
#define SPEED '#'

twoWheels two_wheels;
static int v1 = 1, v2 = 2;

static void f(int v)
{
    printf("(%d)", v);
}

static void display(twoWheels two_wheels)
{
    printf("<");
    DigitalWheelAppService_two_wheels_display(two_wheels, f);
    printf(">\n");
}

static void generate_next_int()
{
    printf("\n[%d]: ", generator_get_next());
}
int run_use_case(int c)
{

    switch (c)
    {

    case MOVE:
        DigitalWheelAppService_two_wheels_move(two_wheels, v1, v2);

        break;

    case SAVE:
        IDigitalWheelRepository_save(two_wheels);
        IDigitalWheelRepository_close();
        printf("STATE SAVED: ");
        break;

    case READ:
    {
        int rank;
        char number[3];

        /* Input string representation of integer from user. */

        fgets(number, 3, stdin);

        /* Convert string representation of number to integer */
        rank = atoi(number);

        if (!IDigitalWheelRepository_open(FILE_DB_REPO))
            return EXIT_FAILURE;

        twoWheels two = DigitalWheelAppService_get_nth_two_wheels(rank);
        two_wheels = two;
        break;
    }

    case '\n':
        display(two_wheels);
        generate_next_int();

    case ' ':
    case '\t':
        break;

    default:

        break;
    }
}

static void prompt()
{
    puts("************************************");
    puts("* Two Wheels Insttance created *");
    puts("************************************");
    puts("*************************************************************************");
    puts("At any time you could input a char then Enter ");
    puts("*************************************************************************");
    puts("********************************************************************************************************");
    puts("* Menu [ >: move the the wheels, ! : save , < n: read the nth record, ! : Ctr-D: Quit] *");
    puts("* n should be 1, 3, 5, 7,...");
    puts("********************************************************************************************************");
}

int main(int argc, char **argv)
{
    prompt();
    two_wheels = DigitalWheelAppService_two_wheels_construct(0, 9);
    DigitalWheelAppService_two_wheels_initialize(two_wheels);
    puts("Departure:");
    display(two_wheels);
    generate_next_int();

    while (true)
    {

        int c = getchar();
        if (c == EOF)
            break;

        run_use_case(c);
    }

    //GET the two wheels separety from DB
    //digital_wheel w1 = IDigitalWheelRepository_get_nth_wheel(1);
    //digital_wheel w2 = IDigitalWheelRepository_get_nth_wheel(2);

    printf("end\n");
    return EXIT_SUCCESS;
}
