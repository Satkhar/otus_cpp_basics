#include "take_usr_name.h"

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

/// @brief функция приветсвие. спрашивает имя, ищет лучший результат
/// @param name указатель на имя
/// @param size сюда пишет размер имени ???
/// @param best_val сюда пишет лучший результат
/// @return если всё ок возвращает 0
int take_user_name(std::string* name, int* size, uint32_t* best_val)
{
    uint8_t res = 0;
	const std::string high_scores_filename = "high_scores.txt";

	// Ask about name
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;
    uint32_t best_score = 0;

    *name = user_name;
    take_best_val(high_scores_filename, user_name, &best_score);

    std::cout << "Enter your high score:" << best_score << std::endl;

    return res;
}

int take_best_val(const std::string &high_scores_filename, const std::string &searched_name, uint32_t* best_val)
{
    uint8_t res = 0;
    std::string user_name;

    std::ifstream in_file{high_scores_filename};
    if (!in_file.is_open()) {
        std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
        return -1;
    }

    int high_score = 0;
    while (true) 
    {
        // Read the username first
        in_file >> user_name;
        // Read the high score next
        in_file >> high_score;
        // Ignore the end of line symbol
        in_file.ignore();

        if (in_file.fail()) {
            break;
        }

        if(user_name == searched_name)
        {
            // std::cout << user_name << '\t' << high_score << std::endl;
            std::cout << "i find! you are: " << user_name << std::endl;
            *best_val = high_score;
            break;
        }        
    }

    return res;
}