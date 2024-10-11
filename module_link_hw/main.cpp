#include "main.h"
#include "take_usr_name.h"
#include "set_result.h"

#include <inttypes.h>
#include <iostream>
#include <ctime>

int main(int arg_count, char** arg_value)
{
    uint8_t res = 0;
    uint8_t func = 0;
	// const int max_value = 100;   //  TODO добавить
    uint16_t new_best = 0;
    int input_val = 0;
    std::string user_name;
    uint16_t user_number = 0;
    uint16_t best_val = 0;

    const std::string high_scores_filename = "high_scores.txt";

    func = take_user_name(high_scores_filename, &user_name, &user_number, &best_val);
    if(func)
    {
        std::cout << "something wrong in user name" << std::endl;
        return 1;   
    }

    std::cout << "your name is " << user_name << std::endl;

    // инициализируем rand. timespec_get для nsec - чтобы чаще rand менялся
    std::timespec ts;
    std::timespec_get(&ts, TIME_UTC);
    
	std::srand(ts.tv_nsec); 
	// std::srand(std::time(nullptr)); 

    // получаем случайное значение и сохраняем его в статическую память
	const int random_value = std::rand() % 100;

    // выводит случайное число, для дебага
	std::cout << "debug ------- " <<random_value << std::endl;

    // получаем число от пользователя
	std::cout << "What a number i'm think? " << std::endl;

    do
    {
        std::cin >> input_val;
        if(input_val == random_value)
        {
            new_best++;
            std::cout << "Yes, you win! \n" << std::endl;
            break;
        }
        else if(input_val < random_value)
        {
            new_best++;
            std::cout << "too low" << std::endl;
        }
        else
        {
            new_best++;
            std::cout << "too hight" << std::endl;
        }

    } while(1);

    if(new_best < best_val)
    {
        std::cout << "New hight result: " << new_best << std::endl;
        func = set_best_val(high_scores_filename, user_name, user_number, new_best);

        if(func != 0)
            std::cout << "something wrong in set record " << std::endl;
    }

    func = view_all_user_name(high_scores_filename);
    if(func != 0)
        std::cout << "something wrong in view score table" << std::endl;

    return res;
}