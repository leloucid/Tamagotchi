#include "meniteengine.h"

static int number = 0;

GLvoid executefunction();

int main()
{
    MeniteInit(800, 600, "Menite Engine");

    MeniteExecute(executefunction);

    return 0;
}

GLvoid executefunction()
{
    printf("hi, %d\n", number++);
}