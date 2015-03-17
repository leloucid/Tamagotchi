#include "meniteengine.h"

GLvoid executefunction();

int main()
{
    MeniteInit(800, 600, "Menite Engine");

    MeniteExecute(executefunction);

    return 0;
}

GLvoid executefunction()
{
    printf("hi, 55\n");
}