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
    uint8_t user_finded = 0;

    std::ifstream in_file{high_scores_filename};
    if (!in_file.is_open()) {
        std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
        res = -1;
        return res;
    }

    //  делаем максимальное число
    uint16_t high_score = -1;
    uint16_t high_score_check = -1;
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
            // проверяем и обновляем лучшее значение
            if(high_score < high_score_check)
                high_score_check = high_score;
            
            // если нашли user, то делаем флаш и возвращаем его номер (первый из возможных)
            if(user_finded == 0)
            {
                user_finded = 1;
                *name_nubmer = name_count;
            }
        }        
    }

    // если нашли, то возвращаем 0, если не нашли возвращаем 1
    if(user_finded == 1)    
        res = 0;    
    else
    {
        *name_nubmer = name_count;
        res = 1;
    }

    *best_val = high_score_check;
    
    return res;
}


int view_all_user_name(const std::string &high_scores_filename)
{
    std::ifstream in_file{high_scores_filename};
    if (!in_file.is_open()) {
        std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
        return -1;
    }

    std::cout << "High scores table:" << std::endl;

    std::string username;
    int high_score = 0;
    while (true) {
        // Read the username first
        in_file >> username;
        // Read the high score next
        in_file >> high_score;
        // Ignore the end of line symbol
        in_file.ignore();

        if (in_file.fail()) {
            break;
        }

        // Print the information to the screen
        std::cout << username << '\t' << high_score << std::endl;
    }

    return 0;
}