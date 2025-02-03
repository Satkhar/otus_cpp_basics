#include <iostream>
#include "container.hpp"

// static void main();
static void i;

// хочется сделать проверку контейнера шаблоном, но как-то сложно
template <typename T>
void CheckSerialContainer(T &input)
{
// 1. create container
	T container = input;

	// 2. add val
	for(int i = 0; i < 10; ++i)
	{
		// const int k = i;
		// container.push_back(k);
		container.push_back(i);
	}
	
	// 3. view container
	for(int i = 0; i < 10; ++i)
	{
		std::cout << container[i] << " ";
	}
	std::cout << std::endl;


	// 4. check size
	std::cout << "size is: " << container.size() << std::endl;

	// 5. delete values
	std::cout << "delete 3, 5, 7 val" << std::endl;

	// 5.1 create container with delete positions  
	T need_del_num;

	need_del_num.push_back((size_t)3);
	need_del_num.push_back((size_t)5);
	need_del_num.push_back((size_t)7);

	// проходим с конца и удаляем с самого старшего ненужного элемента
	for(size_t k = (container.size()-1), del_count = (need_del_num.size()-1); k > 0; --k)
	{
		if(k == need_del_num[del_count])
		{
			container.erase(k-1);
			--del_count;
		}
	}

	// 6. view new container
	std::cout << "new container: " << std::endl;
	for(int i = 0; i < container.size(); ++i)
	{
		std::cout << container[i] << " ";
	}
	std::cout << std::endl;

	// 7. add 10 at 0 position
	std::cout << "add new val at 0 position" << std::endl;

	container.insert(10, 0);

	// 8. view new container
	std::cout << "new container: " << std::endl;
	for(int i = 0; i < container.size(); ++i)
	{
		std::cout << container[i] << " ";
	}
	std::cout << std::endl;


	// 9. add 20 at middle position
	std::cout << "add new val at middle position" << std::endl;
	size_t middle_pos = container.size()/2;	// можно в одну строчку написать, но так читабельнее
	container.insert(20, middle_pos);

	// 10. view new container
	std::cout << "new container: " << std::endl;
	for(int i = 0; i < container.size(); ++i)
	{
		std::cout << container[i] << " ";
	}
	std::cout << std::endl;

	// 11. add 30 at end position
	container.push_back(30);

	// 12. view new container
	std::cout << "new container: " << std::endl;
	for(int i = 0; i < container.size(); ++i)
	{
		std::cout << container[i] << " ";
	}
	std::cout << std::endl;
	return;
}


void main()
{
	std::cout << "Hello, homework 6!" << std::endl;

	MyContainterSerial<int> container;

	CheckSerialContainer(container);

	// return 0;
}
