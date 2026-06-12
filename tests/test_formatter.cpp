#include <formatter.hpp>
#include <formatter_ex.hpp>

#include <gtest/gtest.h>
#include <string>

TEST(Formatter, SimpleText)
{
    EXPECT_EQ(format("hello"), "hello");
}

TEST(FormatterEx, ContainsText)
{
    std::string result = format_ex("hello");

    EXPECT_NE(result.find("hello"), std::string::npos);
}
