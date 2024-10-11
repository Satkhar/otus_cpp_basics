#include "set_result.h"

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

//----------------------------------------------------------------------

/// @brief функция записи нового результата
/// @param high_scores_filename ссылка на имя файла, куда записать
/// @param name ссылка на имя, кого записать
/// @param name_nubmer ссылка на порядковый номер в файле результатов, куда записать
/// @param new_best ссылка на результат, который надо записать
/// @return 
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
            // новый пользователь, пишем его
            new_file << name << ' ';
            new_file << new_best;
            new_file << std::endl << std::endl; //  один перевод строки - конец пользователя, второй - конец таблицы

            break;
        }

        // пропускаем все строки, пока не встанем на последнюю перед нужной
        if(count != (name_nubmer-1))
        { // Замените на нужное количество строк
            getline(new_file, line);
        }
        else        
        {
            //пропустили все прерыдущие строки и стоим на нужной нам - сюда писать
            new_file << name << ' ';
            new_file << new_best;
            new_file << std::endl;
        }

        count++;
        (void)count;

        if (new_file.fail())
            break;        
    }
    new_file.close();

    return res;
}

//----------------------------------------------------------------------