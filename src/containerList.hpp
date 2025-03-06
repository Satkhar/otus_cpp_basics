#pragma once

#include <iostream>
#include <stdexcept>

//----------------------------------------------------------------------------

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

//----------------------------------------------------------------------------

// списочный контейнер
template <typename T>
class MyContainterList
{
public:
    // конструктор
    MyContainterList() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

    // если задан размер
    MyContainterList(size_t m_size) : m_head(nullptr), m_tail(nullptr) 
    {
        if (m_size > MAX_ALLOWED_SIZE) {
            throw std::invalid_argument("Invalid size");
        }


        try {
            for (size_t i = 0; i < m_size; ++i) {
                push_back(T()); // Добавляем пустые элементы
            }
        } catch (const std::bad_alloc&) {
            throw std::runtime_error("Failed to allocate memory for list container");
        }
    }

    // деструктор
    ~MyContainterList() 
    {
        std::cout << "List container destroy" << std::endl;
        while(size())
        {
            erase(0);
        }
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
        } 
        else if (pos == size()) 
        {
            // Вставка в конец
            push_back(value);
            return;
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

    // смотрим откуда ближе идти удалять и идём удалять?
    // удалить определенный элемент
    void erase(const size_t pos) 
    {
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
        if (pos > size()) {
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

    bool empty()
    {
        return !m_size;
    }

private:
    Node<T>* m_head;    // тут указатель на первый узел
    Node<T>* m_tail;    // тут указатель на последний узел
    size_t m_size;      // тут размер списка

    static constexpr size_t MAX_ALLOWED_SIZE = 1'000'000;
};

//----------------------------------------------------------------------------