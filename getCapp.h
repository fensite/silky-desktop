#ifndef GETCAPP_H
#define GETCAPP_H

#endif // GETCAPP_H
#include <QString>


class UkuiChineseLetter
{
public:
    UkuiChineseLetter();
    static bool In(wchar_t start, wchar_t end, wchar_t code);

    static char Convert(int n);

    // 获取第一个汉字的首字母
    static QString getFirstLetter(const QString &src);

    // 获取所有汉字的首字母
    static QString getFirstLetters(const QString &src);

    static QString getFirstLettersAll(const QString &src);

    // 获取一个汉字编码的汉语拼音
    static QString getPinyin(int code);

    // 获取所有汉字的汉语拼音
    static QString getPinyins(const QString& text);
};
