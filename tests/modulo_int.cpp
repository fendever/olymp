#include <gtest/gtest.h>
#include <iostream>
#include <modulo_int.h>

namespace olymp {

using TestI = modulo::Int<11, uint8_t>;
const modulo::multiply<11> test_mult;
const modulo::add<11> test_add;

TEST(ModuloInt, Addition) {
    {
        TestI x(0);
        x += 5;
        ASSERT_EQ(5, x.get_value());
        x += 5;
        ASSERT_EQ(10, x.get_value());
        x += 5;
        ASSERT_EQ(4, x.get_value());
    }
    {
        TestI x(0);
        x += TestI(5);
        ASSERT_EQ(5, x.get_value());
        x += TestI(5);
        ASSERT_EQ(10, x.get_value());
        x += TestI(5);
        ASSERT_EQ(4, x.get_value());
    }
    {
        unsigned x = 7;
        unsigned y = 5;
        ASSERT_EQ(1, test_add(x, y));
    }
}

TEST(ModuloInt, Subtraction) {
    {
        TestI x(0);
        x -= 5;
        ASSERT_EQ(6, x.get_value());
        x -= 5;
        ASSERT_EQ(1, x.get_value());
        x -= 5;
        ASSERT_EQ(7, x.get_value());
    }
    {
        TestI x(0);
        x -= 60;
        ASSERT_EQ(6, x.get_value());
        x -= 5;
        ASSERT_EQ(1, x.get_value());
        x -= 5;
        ASSERT_EQ(7, x.get_value());
    }
    {
        TestI x(0);
        x += (-5);
        ASSERT_EQ(6, x.get_value());
        x += (-5);
        ASSERT_EQ(1, x.get_value());
        x += (-5);
        ASSERT_EQ(7, x.get_value());
    }
}

TEST(ModuloInt, Multiplication) {
    {
        TestI x(0);
        x *= 2u;
        ASSERT_EQ(0, x.get_value());
        x += 1u;
        x *= 2u;
        ASSERT_EQ(2, x.get_value());
        x *= 3u;
        ASSERT_EQ(6, x.get_value());
        x *= 3u;
        ASSERT_EQ(7, x.get_value());
    }
    {
        TestI x(2);
        x *= -2;
        ASSERT_EQ(7, x.get_value());
    }
    {
        unsigned x = 4;
        unsigned y = 5;
        ASSERT_EQ(9, test_mult(x, y));
    }
}

TEST(ModuloInt, Pre) {
    {
        TestI x(0);
        ASSERT_EQ(1, (++x).get_value());
        ASSERT_EQ(0, (--x).get_value());
        ASSERT_EQ(10, (--x).get_value());
        ASSERT_EQ(0, (++x).get_value());
    }
}

TEST(ModuloInt, Compare) {
    {
        ASSERT_LT(TestI(1), TestI(2));
        ASSERT_EQ(TestI(1), TestI(1));
        ASSERT_LE(TestI(1), TestI(2));
        ASSERT_LE(TestI(1), TestI(1));
        ASSERT_GT(TestI(2), TestI(1));
        ASSERT_NE(TestI(2), TestI(1));
        ASSERT_GE(TestI(2), TestI(1));
        ASSERT_GE(TestI(1), TestI(1));
    }
}

} // namespace olymp
