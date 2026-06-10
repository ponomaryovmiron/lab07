#include "formatter_ex.hpp"

#include <formatter.hpp>

std::string format_ex(const std::string& text)
{
    return "----------------\n" + format(text) + "\n----------------";
}
