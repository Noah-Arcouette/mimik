#include <unistd.h>
#include <stdio.h>

int 
main (void) {
    puts(getlogin());
    return 0;
}
