//Author: Alexey Bandura

#pragma once
#include <iostream>



class CString {
public:

    // Constructors
    CString();

    CString(const CString &str);

    explicit CString(char c, int repeatCount = 1);

    CString(const char *str);

    CString(const char *str, int length);

    ~CString();

    int Length() const { return length; }

    bool IsEmpty() const;

    void MakeEmpty();

    void SetBufferLength(int newLength);

    char &GetAt(int index);

    char &operator[](int index);

    const char &operator[](int index) const;

    CString &operator=(const CString &stringSrc);

    CString &operator=(char ch);

    CString &operator=(const char *str);

    bool operator==(const CString &other) const;

    // Append operations
    CString &operator+=(char symbol);

    CString &operator+=(const char *str);

    CString &operator+=(const CString &str);

    void Append(char symbol);

    void Append(const char *str);

    void Append(const CString &str);

    // Strings comparison. Like strCmp
    int Compare(const char *str) const;

    int CompareNoCase(const char *str) const;

    bool EqualsNoCase(const char *str) const;

    // Substring selection
    CString SubString(int firstPos, int count) const;

    CString SubString(int firstPos) const;

    void MakeUpper();

    void MakeLower();

    void MakeReverse();

    // Find symbol position starting from startPos
    int Find(char ch, int startPos = 0) const;

    // Substring search
    int Find(const char *subString, int startPos = 0) const;

    int FindNoCase(const char *subString, int startPos = 0) const;

    // Access to string like to buffer of symbols
    char *GetBuffer() { return buffer; }

    int GetBufferLength() const { return maxCapacity; }

    void StrDel(int pos, int num);

    void StrDel(int pos);

    void StrIns(const char *str, int pos);

    void StrIns(const CString &str, int pos);

    void CharIns(char ch, int pos);

    // will replace characters until the end of the original string this->buffer
    void StrReplace(int pos, const CString &str);

    void StrReplace(int pos, const char *str);



    // Replace all src to newStr
    void ReplaceAll(const char *src, const char *newStr);

    void ReplaceAll(char src, char newSymbol);

    void ReplaceAll(char src, const char *newStr);

    void ReplaceAll(const char *src, char newSymbol);

    friend std::ostream &operator<<(std::ostream &out, const CString &list);


private:
    const double growFactor = 2.0;
    int maxCapacity = 80;
    char *buffer = nullptr;
    int length = 0;

    int getCapacityForGrowByFactor(int length);

    void growByFactor();

    void grow(int newCapacity);
};

CString operator+(const CString &first, const char *second);

CString operator+(const char *first, const CString &second);

CString operator+(char ch, const CString &str);

CString operator+(const CString &str, char ch);

CString operator+(const CString &str1, const CString &str2);

void TestCString();