#pragma once

#include <iostream>
#include <stdexcept>

// последовательный контейнер
template <typename T>
class MyContainterSerial
{
public:
    // конструктор
    MyContainterSerial() : data(nullptr), m_capacity((size_t)2), m_size(0) 
    {
        data = new T[m_capacity];
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
        if (size() == capacity())
        {
            resize_capacity();
        }
        data[m_size++] = value;
    }

    // добавить в произвольную точку
    void insert(const T &value, const size_t pos) 
    {
        if (pos > size()) {
            throw std::out_of_range("To hight position number");
        }

        push_back(value);   // чтобы увеличить размер контейнера

        for(size_t i = (size()-1); i > pos; --i)
        {
            data[i] = data[i-1];
        }
        data[pos] = value;
    }

    // удалить определенный элемент
    void erase(const size_t pos) 
    {
        if (size() == 0) {
            throw std::out_of_range("Vector is empty");
        }

        // Сдвигаем элементы влево, начиная с pos + 1
        for (size_t i = pos; i < size() - 1; ++i) 
        {
            data[i] = data[i + 1];
        }
        --m_size;
    }

    // получить размер
    size_t size() 
    {
        return m_size;
    }

    // получить вместимость
    size_t capacity() 
    {
        return m_capacity;
    }

    // доступ по индексу
    T &operator[](const size_t pos)
    {
        return data[pos];
    }

private:

    // увеличение размера?
    // Увеличивает вместимость контейнера
    void resize_capacity()
    {
        m_capacity *= 2; // Удваиваем вместимость
        T *new_data = new T[m_capacity];  // выделяем новый кусок памяти
        for (size_t i = 0; i < size(); ++i)
        {
            new_data[i] = data[i];  // копируем
        }
        delete[] data;  // удаляем старый(маленький) кусок
        data = new_data;    // теперь указатель на старый кусок указывает на новый кусок
    }

    T *data;         // Указатель на данные
    size_t m_capacity; // Вместимость контейнера
    size_t m_size;     // Текущее количество элементов
};



// списочный контейнер
template <typename T>
class MyContainterList
{
public:
    // конструктор
    MyContainterList() : data(nullptr), m_capacity((size_t)2), m_size(0) 
    {
        data = new T[m_capacity];
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
        if (size() == capacity())
        {
            resize_capacity();
        }
        data[m_size++] = value;
    }

    // добавить в произвольную точку
    void insert(const T &value, const size_t pos) 
    {
        if (pos > size()) {
            throw std::out_of_range("To hight position number");
        }

        push_back(value);   // чтобы увеличить размер контейнера

        for(size_t i = (size()-1); i > pos; --i)
        {
            data[i] = data[i-1];
        }
        data[pos] = value;
    }

    // удалить определенный элемент
    void erase(const size_t pos) 
    {
        if (size() == 0) {
            throw std::out_of_range("Vector is empty");
        }

        // Сдвигаем элементы влево, начиная с pos + 1
        for (size_t i = pos; i < size() - 1; ++i) 
        {
            data[i] = data[i + 1];
        }
        --m_size;
    }

    // получить размер
    size_t size() 
    {
        return m_size;
    }

    // получить вместимость
    size_t capacity() 
    {
        return m_capacity;
    }

    // доступ по индексу
    T &operator[](const size_t pos)
    {
        return data[pos];
    }

private:

    // увеличение размера?
    // Увеличивает вместимость контейнера
    void resize_capacity()
    {
        m_capacity *= 2; // Удваиваем вместимость
        T *new_data = new T[m_capacity];  // выделяем новый кусок памяти
        for (size_t i = 0; i < size(); ++i)
        {
            new_data[i] = data[i];  // копируем
        }
        delete[] data;  // удаляем старый(маленький) кусок
        data = new_data;    // теперь указатель на старый кусок указывает на новый кусок
    }

    T *data;         // Указатель на данные
    size_t m_capacity; // Вместимость контейнера
    size_t m_size;     // Текущее количество элементов
};