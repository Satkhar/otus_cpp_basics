#include <iostream>
#include <string>

#include "argument.h"

//----------------------------------------------------------------------

/// @brief функция обработки аргументов
/// @param argc argument count - сколько аругментов
/// @param argv argument value сам аргумент
/// @param par возвращаемое число. 
// -1 при какой-то ошибке 
// -2 для вывода справки 
// >0 максимальное значение случайного числа 
/// @return 0 если нет ошибки
int check_arg(int argc, char** argv, int* par)
{
    // argc - it is a count of arguments
	// But there is some detail - OS always pass one system argument - the name of the executable
	// So, is the application was executed without arguments at all, argc will be still == 1

	// Let's print this argument
	// if (argc > 0) {
	// 	std::cout << "We have at least one argument!" << std::endl;
	// 	std::cout << "argv[0] = " << argv[0] << std::endl;
	// }

	// To check - does use print some other argument we should check if the argc >= 2
	if (argc >= 2) 
    {
		// std::cout << "We have one more argument!" << std::endl;
		// std::cout << "argv[1] = " << argv[1] << std::endl;

		std::string arg1_value{ argv[1] };

        if (arg1_value == "-h") 
        {
			if (argc > 2) 
            {
				std::cout << "Wrong usage! The argument '-h' no requires some value!" << std::endl;
				return -1;
			}
            std::cout << "How to use 'Guess the number' \n" << std::endl;

			// We need to parse the string to the int value
            std::cout << "Enter '-h' - for view that text" << std::endl;
			std::cout << "Enter '-max' <value>, where value - maximum range of guess number. max valid 65534" << std::endl;
			std::cout << "Enter '-level' <value>, where value - difficulty level [0 - you win, 1 - beginner ... 5 - max] " << std::endl;
			std::cout << "Enter '-table' - for output table of scores" << std::endl;
            *par = -2;
            return 0;
		}

        if (arg1_value == "-table") 
        {
			if (argc > 2) 
            {
				std::cout << "Wrong usage! The argument '-table' no requires some value!" << std::endl;
				return -1;
			}
            *par = -1;
            return 0;
		}

		if (arg1_value == "-max") 
        {
			// We've detected the '-parameter' argument. And we extect that after this argument there is a value:
			int parameter_value = 0;
			if (argc < 3) {
				std::cout << "Wrong usage! The argument '-max' requires some value!" << std::endl;
				return -1;
			}
            // проверка на число? и на диапазон чисел
			// We need to parse the string to the int value
			parameter_value = std::stoi(argv[2]);

            if(parameter_value == 0)     
				std::cout << "That is too low. max set to " << ++parameter_value << std::endl;
            
            *par = ++parameter_value;
		}

        if (arg1_value == "-level") 
        {
			// We've detected the '-parameter' argument. And we extect that after this argument there is a value:
			avoid_levels_e parameter_value;
			if (argc < 3) {
				std::cout << "Wrong usage! The argument '-level' requires some value!" << std::endl;
				return -1;
			}
            // проверка на число? и на диапазон чисел
			// We need to parse the string to the int value
			parameter_value = (avoid_levels_e)std::stoi(argv[2]);
			std::cout << "The choosed level = ";
            switch(parameter_value)
            {
                case win: *par = 1; std::cout << "you win" << std::endl; break;
                case first: *par = 10; std::cout << "first level" << std::endl; break;
                case second: *par = 50; std::cout << "second level" << std::endl; break;
                case third: *par = 100; std::cout << "third level" << std::endl; break;
                case fourth: *par = 1000; std::cout << "fourth level" << std::endl; break;
                case fifth: *par = 65535; std::cout << "max level" << std::endl; break;
                
                default: *par = 65535; std::cout << "set max level" << std::endl; break;
            }
            return 0;
		}
	}

    return 0;
}

//----------------------------------------------------------------------