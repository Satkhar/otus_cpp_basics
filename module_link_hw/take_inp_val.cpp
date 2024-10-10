// // #include "main.h"

// #include <inttypes.h>
// #include <iostream>
// #include <ctime>

// /// @brief функция для получения от пользователя
// /// @param arg_count 
// /// @param arg_value 
// /// @return 
// int take_input_value(int arg_count, char** arg_value)
// {
//     uint8_t res = 0;
// 	// const int max_value = 100;
//     int input_val = 0;

//     // инициализируем rand. timespec_get для nsec - чтобы чаще rand менялся
//     std::timespec ts;
//     std::timespec_get(&ts, TIME_UTC);
    
// 	std::srand(ts.tv_nsec); 
// 	// std::srand(std::time(nullptr)); 

//     // получаем случайное значение и сохраняем его в статическую память
// 	const int random_value = std::rand() % 100;

//     // выводит случайное число, для дебага
// 	std::cout << random_value << std::endl;

//     // получаем число от пользователя
// 	std::cout << "What a number i'm think? " << std::endl;

//     do
//     {
//         std::cin >> input_val;
//         if(input_val == random_value)
//         {
//             std::cout << "wow!" << std::endl;
//             break;
//         }
//         else if(input_val < random_value)
//         {
//             std::cout << "too low" << std::endl;
//         }
//         else
//         {
//             std::cout << "too hight" << std::endl;
//         }
//         // std::cout << "wow, its: " <<input_val << std::endl;

//     } while(1);

//     return res;
// }