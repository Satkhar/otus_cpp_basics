#pragma once

#include <iostream>

// общий шаблон
template <typename T>
class MyContainterSerial
{
public:
    MyContainterSerial(){}
    MyContainterSerial(T v) : value_{v} {}

    ~MyContainterSerial() {};

    // добавить в конец контейнера
    bool push_back(const T &v){}

    // добавить в произвольную точку
    bool insert(const T &v, const size_t pos){}

    // удалить элемент
    bool erase(const size_t pos){}

    // получить размер
    bool size(const size_t &size){}

    // доступ по индексу
    T& operator[](const size_t pos){}

private:
    T value_;
};

// реализация для int
template <>
class MyContainterSerial<int>
{
public:
    MyContainterSerial(int v) : value_{v} {}

    bool push_back(const int &v)
    {
        T *new_region = new T[m_size + 1]; // новая область памяти
        for (size_t i = 0; i < m_size; ++i)
        {
            new_region[i] = m_region[i]; // копирование элементов
        }
        new_region[m_size] = value; // добавление нового элемента
        delete[] m_region;          // удаление старой области
        m_region = new_region;      // сохранение новой в мембер
        m_size += 1;                // обновление информации о размере
    }

        // добавить в произвольную точку
    bool insert(const int &v, const size_t pos){}

    // удалить элемент
    bool erase(const size_t pos){}

    // получить размер
    bool size(const size_t &size){}

    // доступ по индексу
    int& operator[](const size_t pos){}

private:
    int value_;
    size_t m_size;
};

// void
// MyContainter::push_back(T value)
// {
//     T *new_region = new T[m_size + 1]; // новая область памяти
//     for (size_t i = 0; i < m_size; ++i)
//     {
//         new_region[i] = m_region[i]; // копирование элементов
//     }
//     new_region[m_size] = value; // добавление нового элемента
//     delete[] m_region;          // удаление старой области
//     m_region = new_region;      // сохранение новой в мембер
//     m_size += 1;                // обновление информации о размере
// }
