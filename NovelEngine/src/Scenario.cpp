#include "Scenario.hpp"

Scenario::Scenario()
    : texts{
        "This is the first line.",
        "This is the second line.",
        "This is the final line."
    }
{
}

const std::string& Scenario::currentText() const
{
    return texts[currentTextIndex];
}

bool Scenario::advance()
{
    if (currentTextIndex + 1 >= texts.size())
    {
        return false;
    }

    ++currentTextIndex;
    return true;
}

bool Scenario::isAtEnd() const
{
    return currentTextIndex + 1 >= texts.size();
}