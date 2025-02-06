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

    // конструктор копирования
    MyContainterSerial(const MyContainterSerial& other) : m_size(other.m_size) 
    {
        data = new int[m_size]; // Выделяем новую память
        m_capacity = other.m_capacity;
        std::copy(other.data, other.data + m_size, data); // Копируем данные
    }

    // оператор =
    MyContainterSerial& operator= (const MyContainterSerial& other) 
    {
        if (this != &other) { // Защита от самоприсваивания
            delete[] data; // Освобождаем старую память

            m_size = other.m_size;          // размер такой же?
            m_capacity = other.m_capacity;  // вместимость?

            data = new int[m_size]; // Выделяем новую память
            std::copy(other.data, other.data + m_size, data); // Копируем данные
        }
        return *this;
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

// для списочного, шаблон узла
template <typename T>
struct Node 
{
    T data;       // данные узла
    Node* next;   // указатель на следующий узел
    Node* prev;   // указатель на предыдущий узел

    // конструктор
    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

// списочный контейнер
template <typename T>
class MyContainterList
{
public:
    // конструктор
    MyContainterList() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

    // деструктор
    ~MyContainterList() 
    {
        // clear();
    }

    // добавить в конец контейнера
    void push_back(const T& value) 
    {
        Node<T>* newNode = new Node<T>(value);
        // Если список пуст
        if (!m_head) 
        { 
            m_head = m_tail = newNode;
        } 
        else 
        {
            m_tail->next = newNode; // указываем на след узел
            newNode->prev = m_tail; // говорим след узлу кто предыдущий
            m_tail = newNode;       // обновляем указатель на последний узел, т.к. старый m_tail уже больше не последний
        }
        ++m_size;
    }

        // добавить в начало
    void push_front(const T& value) 
    {
        Node<T>* newNode = new Node<T>(value);
        // если список пуст
        if (!m_head) 
        { 
            m_head = m_tail = newNode;
        } 
        else 
        {
            newNode->next = m_head;
            m_head->prev = newNode;
            m_head = newNode;
        }
        ++m_size;
    }

    // добавить в произвольную точку
    void insert(const T &value, const size_t pos) 
    {
        if (pos > size()) 
        {
            throw std::out_of_range("Index out of range");
        }

        Node<T>* newNode = new Node<T>(value);

        if (size() == 0) 
        {
            // Если список пуст, новый элемент становится головой и хвостом
            m_head = m_tail = newNode;
        } 
        else if (pos == 0) 
        {
            // Вставка в начало

            push_front(value);
            return;

            // newNode->next = m_head;
            // m_head->prev = newNode;
            // m_head = newNode;
        } 
        else if (pos == size()) 
        {
            // Вставка в конец

            push_back(value);
            return;

            // newNode->prev = tail;
            // tail->next = newNode;
            // tail = newNode;
        } 
        else 
        {
            // Вставка в середину
            Node<T>* current = m_head;
            for (size_t i = 0; i < pos; ++i) 
            {
                current = current->next;
            }

            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
        }

        ++m_size;
    }

    // TODO надо
    // смотрим откуда ближе идти удалять и идём удалять?
    // удалить определенный элемент
    void erase(const size_t pos) 
    {
        // if (size() == 0) {
        //     throw std::out_of_range("Vector is empty");
        // }

        // // Сдвигаем элементы влево, начиная с pos + 1
        // for (size_t i = pos; i < size() - 1; ++i) 
        // {
        //     data[i] = data[i + 1];
        // }
        if (pos >= size()) 
        {
            throw std::out_of_range("Index out of range");
        }

        Node<T>* toRemove = m_head;
        for (size_t i = 0; i < pos; ++i) 
        {
            toRemove = toRemove->next;
        }

        if (toRemove->prev) 
        {
            toRemove->prev->next = toRemove->next;
        } 
        else 
        {
            m_head = toRemove->next; // Удаляем голову
        }

        if (toRemove->next) 
        {
            toRemove->next->prev = toRemove->prev;
        } 
        else 
        {
            m_tail = toRemove->prev; // Удаляем хвост
        }

        delete toRemove;


        --m_size;
    }

    // получить размер
    size_t size() 
    {
        return m_size;
    }

    // доступ по индексу
    T &operator[](const size_t pos)
    {
        // return data[pos];
        if (pos >= size()) {
            throw std::out_of_range("Index out of range");
        }

        Node<T>* current = m_head;
        // можно улучшить - смотрим откуда ближе(начало или конец) и оттуда двигаемся
        for (size_t i = 0; i < pos; ++i) 
        {
            current = current->next;
        }
        return current->data;
    }



private:
    Node<T>* m_head;    // тут указатель на первый узел
    Node<T>* m_tail;    // тут указатель на последний узел
    size_t m_size;      // тут размер списка
};