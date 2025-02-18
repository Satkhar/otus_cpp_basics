#include <iostream>
#include "containerSerial.hpp"
#include "containerList.hpp"

#include "check_container.cpp"

// хочется сделать проверку контейнера шаблоном, но как-то сложно
// хотя, вроде, работает

int main()
{
	std::cout << "Hello, homework 6!" << std::endl;

	// MyContainterSerial<int> container_serial;

	MyContainterSerial<int> container;

	CheckContainer(container);

	std::cout << "---------" << std::endl;

	// MyContainterList<int> container_list;

	MyContainterList<int> container2;

	CheckContainer(container2);
}
