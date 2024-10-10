#include "set_result.h"

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>


int set_best_val(const std::string &high_scores_filename, const std::string &name, const uint16_t &name_nubmer, const uint16_t &new_best)
{
    int res = 0;
    int16_t count = 0;
    std::string line;

    std::string temp_name;
    int temp_score = 0;

    
    //  
    std::ifstream in_file{high_scores_filename, std::ios_base::in};
    if (!in_file.is_open()) {
        std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
        return -1;
    }

    // We should open the output file in the append mode - we don't want
    // to erase previous results.
    std::ofstream out_file{high_scores_filename, std::ios_base::out};
    if (!out_file.is_open()) {
        std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
        return -1;
    }
    std::cout << "***************** name number is **** " << name_nubmer << std::endl;

    while(1)
    {
        // Пропускаем оставшиеся строки
        if(count < name_nubmer)
        { // Замените на нужное количество строк
            // getline(in_file, line);
            // out_file << line;

            in_file >> temp_name;
            // Read the high score next
            in_file >> temp_score;
            // Ignore the end of line symbol
            in_file.ignore();
            
            out_file << temp_name << ' ';
            out_file << temp_score;
            out_file << std::endl;

            count++;
            (void)count;
        }
        else
        {
            std::cout << "3333" << std::endl;
            out_file << name << ' ';
            out_file << new_best;
            out_file << std::endl;

            // std::cout << "count is: " << count << " getline line is: " << line << "--end" << std::endl;

            //  // Закрытие файлов
            // in_file.close();
            // out_file.close();
            // break;
        }

        if (in_file.fail()) {
            in_file.close();
            out_file.close();
            break;
        }

    }

    // Append new results to the table:
    // out_file << name << ' ';
    // out_file << best_val;
    // out_file << std::endl;
    // end of score here just to mark end of the logic block of code

    return res;
}