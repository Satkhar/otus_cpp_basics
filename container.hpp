#pragma once

#include <iostream>
#include <stdexcept>

// общий шаблон
template <typename T>
class MyContainterSerial
{
public:
    // конструктор
    MyContainterSerial() : data(nullptr), capacity((size_t)2), size(0) 
    {
        data = new T[capacity];
    }

    //деструктор
    ~MyContainterSerial() 
    {
        delete[] data;
    };

    // добавить в конец контейнера
    void push_back(const T &value) 
    {
        // проверяем есть ли куда класть данные
        if (size == capacity) 
        {
            resize_capacity();
        }
        data[size++] = value;
    }

    // добавить в произвольную точку
    void insert(const T &value, const size_t pos) 
    {
        T temp = value;

        for(size_t i = pos; i < size; i++)
        {
            // data[]
        }
    }

    // удалить элемент
    void erase(const size_t pos) 
    {
        if (size == 0) {
            throw std::out_of_range("Vector is empty");
        }
        --size;
    }

    // получить размер
    size_t size() 
    {
        return size;
    }

    // получить вместимость
    size_t capacity() 
    {
        return capacity;
    }

    // доступ по индексу
    T &operator[](const size_t pos) 
    {
        return data[index];
    }

private:
    T value_;

    // увеличение размера?
    // Увеличивает вместимость контейнера
    void resize_capacity()
    {
        capacity *= 2; // Удваиваем вместимость
        T *new_data = new T[capacity];  // выделяем новый кусок памяти
        for (size_t i = 0; i < size; ++i)
        {
            new_data[i] = data[i];  // копируем
        }
        delete[] data;  // удаляем старый(маленький) кусок
        data = new_data;    // теперь указатель на старый кусок указывает на новый кусок
    }

    T *data;         // Указатель на данные
    size_t capacity; // Вместимость контейнера
    size_t size;     // Текущее количество элементов
};

// реализация для int
template <>
class MyContainterSerial<int>
{
public:
    MyContainterSerial(int v) : value_{v} {}

    // bool push_back(const int &v)
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

    // добавить в произвольную точку
    bool insert(const int &v, const size_t pos) {}

    // удалить элемент
    bool erase(const size_t pos) {}

    // получить размер
    bool size(const size_t &size) {}

    // доступ по индексу
    int &operator[](const size_t pos) {}

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
