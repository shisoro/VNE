#pragma once

#include <cstddef>
#include <string>
#include <vector>

class Scenario
{
public:
    Scenario();

    // '&' コピーせず、元の文字列への参照を返す
    // &が無いとコピーになってしまう
    // 先頭のconst 呼び出し側から文字列を変更できない
    // 末尾のconst Scenario自体の状態を変更しない
    const std::string& currentText() const;
    bool advance();
    bool isAtEnd() const;

private:
    std::vector<std::string> texts;
    std::size_t currentTextIndex = 0;
};