#include "containerList.hpp"
#include <gtest/gtest.h>

// пустой тест
// TEST(SampleTest, BasicAssertion) {
//     EXPECT_EQ(1, 1);
// }

// создание контейнера
TEST(List, Empty) {
    // Arrange
    MyContainterList<int> list;

    // Act (empty for this test)

    // Assert
    ASSERT_EQ(list.size(), 0);
    ASSERT_TRUE(list.empty());
}

// Попытка создать вектор с большим размером
TEST(List, BigSize) {
    EXPECT_THROW(
        {
            MyContainterList<int> list(1'000'001); //   1'000'001     1'000'000'000  
        },
        std::invalid_argument
    );
}


// Попытка создать вектор с отрицательным размером
TEST(List, NegSize) {
    EXPECT_THROW(
        {
            MyContainterList<int> list(static_cast<size_t>(-1));
        },
        std::invalid_argument
    );
}

// добавление элеммента в конец
TEST(List, PushBack) {
    // Arrange
    const size_t count = 10;
    MyContainterList<size_t> list;

    // Act
    for (size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }
    list.push_back(0x55);

    // Assert
    ASSERT_EQ(list.size(), count+1);
    ASSERT_EQ(list[count], 0x55);
    ASSERT_FALSE(list.empty());
}

// удаление элементов из конца
TEST(List, PopBack) {
    // Arrange 
    const size_t count = 10;
    MyContainterList<size_t> list;

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
TEST(List, PushFront)
{
    // Arrange 
    MyContainterList<int> list;

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
TEST(List, PushMiddle)
{
    // Arrange 
    const int count = 10;
    size_t middle_pos = 0;
    MyContainterList<int> list;

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

    for(size_t i = 0; i < (count+1); ++i)
    {
        if(i < middle_pos)  // до вставки
        {
            ASSERT_EQ(list[i], i);
        }
        else if(i == middle_pos)    // середина
        {
            ASSERT_EQ(list[middle_pos], 20);
            ++i;
        }
        else    // после вставки
        {
            ASSERT_EQ(list[i], i-1);
        }
    }
}

// - удаление элементов из начала
TEST(List, PopFront) 
{
    // Arrange 
    const size_t count = 5;
    MyContainterList<size_t> list;

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
TEST(List, PopMiddle) 
{
    // Arrange 
    const size_t count = 10;
    size_t middle_pos = 0;
    MyContainterList<size_t> list;

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
TEST(List, CheckAt) 
{
    // Arrange 
    const size_t count = 10;
    MyContainterList<size_t> list;
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
TEST(List, CheckSize) 
{
    // Arrange 
    const size_t count = 10;
    MyContainterList<size_t> list;

    for (size_t i = 0; i < count; ++i) 
    {
        list.push_back(i);
    }

    // Act

    // Assert
    ASSERT_EQ(list.size(), count);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}