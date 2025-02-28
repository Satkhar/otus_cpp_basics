#include "containerSerial.hpp"
#include <gtest/gtest.h>

// пустой тест
// TEST(SampleTest, BasicAssertion) {
//     EXPECT_EQ(1, 1);
// }

// создание контейнера
TEST(Serial, Empty) {
    // Arrange
    MyContainterSerial<int> list;

    // Act (empty for this test)

    // Assert
    ASSERT_EQ(list.size(), 0);
    ASSERT_TRUE(list.empty());
}

// Попытка создать вектор с большим размером
TEST(Serial, BigSize) {
    EXPECT_THROW(
        {
            MyContainterSerial<int> list(1'000'001);
        },
        std::invalid_argument
    );
}

// Попытка создать вектор с отрицательным размером
TEST(Serial, NegSize) {
    EXPECT_THROW(
        {
            MyContainterSerial<int> list(static_cast<size_t>(-1));
        },
        std::invalid_argument
    );
}

// добавление элемента в конец
TEST(Serial, PushBack) {
    // Arrange
    const size_t count = 10;
    MyContainterSerial<size_t> list;

    // Act
    for (size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    // Assert
    ASSERT_EQ(list.size(), count);
    ASSERT_FALSE(list.empty());
}

// удаление элементов из конца
TEST(Serial, PopBack) {
    // Arrange 
    const size_t count = 10;
    MyContainterSerial<size_t> list;

    for (size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    // Act
    for (; list.size() > 0; ) 
    {
        list.erase(list.size()-1);
    }

    // Assert
    ASSERT_EQ(list.size(), 0);
    ASSERT_TRUE(list.empty());
}

// вставка в начало
TEST(Serial, PushFront)
{
    // Arrange 
    MyContainterSerial<int> list;

    // Проверяем, что есть пустой контейнер
    EXPECT_TRUE(list.empty());

    // Act
    list.insert(55, 0);
    list.insert(99, 0);

    // Assert
    EXPECT_EQ(list.size(), 2);

    //проверяем порядок чисел
    ASSERT_EQ(list[0], 99);
    ASSERT_EQ(list[1], 55);
}

// - вставка элементов в середину
TEST(Serial, PushMiddle)
{
    // Arrange 
    const int count = 10;
    size_t middle_pos = 0;
    MyContainterSerial<int> list;

    // Проверяем, что есть пустой контейнер
    EXPECT_TRUE(list.empty());

    for (int i = 0; i < count; ++i) 
    {
        list.push_back(i);
    }
    
    // Act

	middle_pos = list.size()/2;
	list.insert(20, middle_pos);

    // Assert

    //проверяем порядок чисел
    EXPECT_EQ(list.size(), count+1);
    ASSERT_EQ(list[middle_pos], 20);
}

// - удаление элементов из начала
TEST(Serial, PopFront) 
{
    // Arrange 
    const size_t count = 5;
    MyContainterSerial<size_t> list;

    for (size_t i = 0; i < count; ++i) 
    {
        list.push_back(i);
    }

    // Act
    list.erase(0);
    
    // Assert
    // count-1 из-за удаления одного элемента
    ASSERT_EQ(list.size(), count-1);
    for (size_t i = 0; i < count-1; ++i) 
    {
        ASSERT_EQ(list[i], i+1);
    }
    // ASSERT_EQ(list[0], 1);
    // ASSERT_EQ(list[1], 2);
    // ASSERT_EQ(list[2], 3);
    // ASSERT_EQ(list[3], 4);
}

// - удаление элементов из середины
TEST(Serial, PopMiddle) 
{
    // Arrange 
    const size_t count = 10;
    size_t middle_pos = 0;
    MyContainterSerial<size_t> list;

    for (size_t i = 0; i < count; ++i) 
    {
        list.push_back(i);
    }

    // Act
    middle_pos = list.size()/2;
    list.erase(middle_pos);
    
    // Assert
    ASSERT_EQ(list.size(), count-1);
    for (size_t i = 0; i < count-1; ++i) 
    {
        if(i >= middle_pos)
            ASSERT_EQ(list[i], i+1);
        else
            ASSERT_EQ(list[i], i);
    }
}

// - получение элементов из контейнера
TEST(Serial, CheckAt) 
{
    // Arrange 
    const size_t count = 10;
    MyContainterSerial<size_t> list;
    size_t compare_arr[10]={0};

    for (size_t i = 0; i < count; ++i) 
    {
        list.push_back(i);
    }

    // Act
    for(size_t i = 0; i < count; ++i)
    {
        compare_arr[i] = list[i];
    }

    // Assert
    for (size_t i = 0; i < count; ++i)
    {
        ASSERT_EQ(compare_arr[i], i);
    }
}

// - получение размера контейнера (фактическое количество элементов)
TEST(Serial, CheckSize) 
{
    // Arrange 
    const size_t count = 10;
    MyContainterSerial<size_t> list;

    for (size_t i = 0; i < count; ++i) 
    {
        list.push_back(i);
    }

    // Act

    // Assert
    ASSERT_EQ(list.size(), count);
}

// int main(int argc, char** argv) {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }