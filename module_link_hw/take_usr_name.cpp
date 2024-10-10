#include "take_usr_name.h"

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

/// @brief функция приветсвие. спрашивает имя, ищет лучший результат
/// @param high_scores_filename ссылка на имя файла с результатами
/// @param name ссылка на имя ользователя
/// @param size сюда пишет размер имени ???
/// @param best_val сюда пишет лучший результат
/// @return если всё ок возвращает 0
int take_user_name(const std::string &high_scores_filename, std::string* name, uint16_t* name_nubmer, uint16_t* best_val)
{
    int res = 0;
    int func = 0;

	// Ask about name
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;
    uint16_t best_score = 0;
    const std::string high_scores_filename1 = "high_scores.txt";

    *name = user_name;
    func = take_best_val(high_scores_filename1, user_name, name_nubmer, &best_score);
    
    // если нет такого
    // дадим максимальное количество - будто не очень умный пользователь
    if(func == 1)
        best_score = -1;
    
    // ошибка открытия файла (добавить создание?) а пока - вернуть -1
    if(func == -1)
        return func;

    // если нашли
    if(func == 0)    
        std::cout << "Your high score:" << best_score << std::endl;
    
    *best_val = best_score;

    return res;
}

int take_best_val(const std::string &high_scores_filename, const std::string &searched_name, uint16_t* name_nubmer, uint16_t* best_val)
{
    int res = 0;
    uint16_t name_count = 0;
    std::string user_name;

    std::ifstream in_file{high_scores_filename};
    if (!in_file.is_open()) {
        std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
        res = -1;
        return res;
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
        name_count++;

        if (in_file.fail()) {
            break;
        }

        if(user_name == searched_name)
        {
            // std::cout << user_name << '\t' << high_score << std::endl;
            std::cout << "i find! you are: " << user_name << std::endl;
            *best_val = high_score;
            *name_nubmer = name_count;
            return 0;   //  нашли и возвращаем число очков и позицию в файле
        }        
    }
    *name_nubmer = name_count;
    res = 1;    // не нашли - возвращаем 1
    return res;
}