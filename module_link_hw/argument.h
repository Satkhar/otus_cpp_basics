#ifndef ARGUMENT_H
#define ARGUMENT_H

//----------------------------------------------------------------------

/// @brief enum для выбора уровня сложности
typedef enum
{
    win = 0,    //  0 всегда
    first,      //  до 5
    second,     //  до 10
    third,      //  до 100
    fourth,     //  до 1000
    fifth       //  до 65535
}
avoid_levels_e;

//----------------------------------------------------------------------

int check_arg(int argc, char** argv, int* par);

//----------------------------------------------------------------------

#endif  //ARGUMENT_H