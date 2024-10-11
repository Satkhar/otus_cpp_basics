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

    std::fstream new_file{high_scores_filename};    // std::ios_base::in | std::ios_base::out
    if (!new_file.is_open()) {
        std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
        return -1;
    }

    std::cout << "***************** name number is **** " << name_nubmer << std::endl;

    while(1)
    {
        // если первая запись в файл
        if(name_nubmer == 0)
        {
            //пропустили все прерыдущие строки и стоим на нужной нам - сюда писать
            std::cout << " that new data :";
            // нашли строчку, теперь берем имя, меняем результат
            new_file << name << ' ';
            new_file << new_best;
            new_file << std::endl;

            std::cout  << name << ' ';
            std::cout  << new_best;
            std::cout  << std::endl;
            break;
        }

        // пропускаем все строки, пока не встанем на последнюю перед нужной
        if(count != (name_nubmer-1))
        { // Замените на нужное количество строк
            getline(new_file, line);
            std::cout << "old data :" << line << std::endl;  // второй вывод т.к. последняя строка "нулевая" только из /n         
        }
        else        
        {
            //пропустили все прерыдущие строки и стоим на нужной нам - сюда писать
            std::cout << " that new data :";
            // нашли строчку, теперь берем имя, меняем результат
            new_file << name << ' ';
            new_file << new_best;
            new_file << std::endl;

            std::cout  << name << ' ';
            std::cout  << new_best;
            std::cout  << std::endl;
        }

        count++;
        (void)count;

        if (new_file.fail())
            break;        
    }
    new_file.close();

    return res;
}