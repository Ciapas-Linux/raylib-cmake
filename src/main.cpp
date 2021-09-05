// ###############################
// #    CIAPAS DUPA        	   #
// ###############################

#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "Intro.h"

int main()
{
    Intro intro(1920/2+300, 1080/2+200, "window");
    intro.Run();
    
    return 0;
}

