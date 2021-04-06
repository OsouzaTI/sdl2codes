#include "logs.h"

void _logs(int type, const char *file, const char *function, long line, const char *message){   
    switch (type)
    {
    case ERROR:{
        printf(RED);
        printf("[%s -> %s][%ld] -> %s\n", file, function, line, message);
    }break;
    case INFO:{
        printf(GREEN);
        printf("[%s -> %s][%ld] -> %s\n", file, function, line, message);
    }break;
    case WARNING:{
        printf(YELLOW);
        printf("[%s -> %s][%ld] -> %s\n", file, function, line, message);
    }break;
    case DEBUG:{
        printf(BLUE);
        printf("[%s -> %s][%ld] -> %s\n", file, function, line, message);
    }break;    
    default:
        printf(RED "log type undefined\n");
        break;
    }
    printf(RESET);
}