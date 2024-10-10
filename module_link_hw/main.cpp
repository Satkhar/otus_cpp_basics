#include "main.h"
#include "take_usr_name.h"

#include <inttypes.h>
#include <iostream>
#include <ctime>

int main(int arg_count, char** arg_value)
{
    uint8_t res = 0;
    uint8_t func = 0;
	// const int max_value = 100;
    int input_val = 0;
    std::string user_name;
    int size_name = 0;
    uint32_t best_val = 0;

    func = take_user_name(&user_name, &size_name, &best_val);
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
	std::cout << random_value << std::endl;

    // получаем число от пользователя
	std::cout << "What a number i'm think? " << std::endl;

    do
    {
        std::cin >> input_val;
        if(input_val == random_value)
        {
            std::cout << "wow!" << std::endl;
            break;
        }
        else if(input_val < random_value)
        {
            std::cout << "too low" << std::endl;
        }
        else
        {
            std::cout << "too hight" << std::endl;
        }


    } while(1);

    return res;
}