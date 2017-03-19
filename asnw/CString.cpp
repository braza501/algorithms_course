//Author: Alexey Bandura

#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <iostream>

#include "CString.h"

using namespace std;


void TestCString() {
    CString str1 = "Harbour Space";
    CString str4("Dollar", 0);
    cout << " is str4 empty? " << std::boolalpha << str4.IsEmpty() << endl;
    cout << str1 << endl;
    str1.MakeUpper();
    cout << str1 << endl;
    str1.MakeLower();
    cout << str1 << endl;
    str1.MakeReverse();
    cout << str1 << endl;
    str1.MakeReverse();
    str1.Append('!');
    str1.Append("=)");
    str1.Append(str4);
    cout << str1 << endl;
    cout << str1.Length() << endl;
    str1 = "Hello world";
    cout << str1 + " from Barcelona! " << endl;
    cout << "Hello, " + str1 << endl;
    cout << '#' + str1 << endl;
    cout << str1 + '*' << endl;
    str4 = " from Space";
    cout << str1 + str4 << endl;
    char ch = '2';
    str1 = ch;
    cout << str1 << endl;
    CString str2 = "Euro/Dollar";
    str1 = str2;
    cout << str1 << endl;
    cout << str1.SubString(0, str1.Find('/')) << endl;
    cout << str1.SubString(str1.Find('/') + 1) << endl;
    cout << str1[4] << endl;
    cout << std::boolalpha << (str1[str1.Length()] == '\0') << endl;
    cout << str1.GetAt(2) << endl;

    str1 = "reality";
    str2 = "ReaLitY";

    cout << std::boolalpha << str1.EqualsNoCase("ReaLitY") << endl;
    cout << std::boolalpha << str1.CompareNoCase("ReaLitY") << endl;
    str1 = "reality";
    cout << str1.Compare("reality") << endl;
    cout << str1.Compare("qeality") << endl;

    str1 = "DogCatDogCat";
    str1.StrDel(9, 3); // 9 points to C letter - the last word Cat
    str1.StrDel(5); // must delete 't'
    cout << str1 << endl;
    str2 = "Elite String Company";
    str2.StrReplace(0, "-----------------------");
    str2.StrReplace(2, str1);
    cout << str2 << endl;
    str1 = "DogCaT";
    cout << str1.GetBuffer() + str1.FindNoCase("cat") << endl;
    str1.StrIns("World", 3);
    CString str3('#', 6);
    str1.StrIns(str3, 0);
    cout << str1 << endl;
    str1 = "dogcatdogcat";
    str1.ReplaceAll('o', '#');
    cout << str1 << endl;
    str1.ReplaceAll("cat", "WORLD");
    cout << str1 << endl;
    str1.ReplaceAll('#', "||");
    cout << str1 << endl;
    str1.ReplaceAll("WORLD", '^');
    cout << str1 << endl;
}

CString::CString() {
    buffer = new char[maxCapacity];
    buffer[0] = 0;
}

CString::CString(char c, int repeatCount) {
    length = repeatCount;
    maxCapacity = getCapacityForGrowByFactor(length) + 1;
    buffer = new char[maxCapacity];
    for (int i = 0; i < length; i++) {
        buffer[i] = c;
    }
    buffer[length] = 0;
}

CString::CString(const char *str, int length) {
    assert(length >= 0 && length <= strlen(str));

    this->length = length;
    maxCapacity = getCapacityForGrowByFactor(length) + 1;
    buffer = new char[maxCapacity];
    strncpy(buffer, str, length);
    buffer[length] = 0;
}

CString &CString::operator=(char ch) {
    delete[] buffer;
    maxCapacity = getCapacityForGrowByFactor(80);
    buffer = new char[maxCapacity];
    buffer[0] = ch;
    buffer[1] = 0;
    length = 1;
    return (*this);
}

CString::CString(const char *cStr) {
    length = strlen(cStr);
    assert(length >= 0);
    maxCapacity = getCapacityForGrowByFactor(length) + 1;
    buffer = new char[maxCapacity];
    strcpy(buffer, cStr);
}

CString::~CString() {
    delete[] buffer;
}

std::ostream &operator<<(std::ostream &out, const CString &str) {
    assert(str.buffer != nullptr);
    out << str.buffer;
    return out;
}

CString::CString(const CString &other) {
    maxCapacity = other.maxCapacity;
    length = other.length;
    buffer = new char[maxCapacity];
    strcpy(buffer, other.buffer);
}

bool CString::operator==(const CString &other) const {
    if (length != other.length) {
        return false;
    }
    return strcmp(buffer, other.buffer) == 0;
}

CString &CString::operator=(const CString &other) {
    if (this == &other) {
        return (*this);
    }
    delete[] buffer;
    maxCapacity = other.maxCapacity;
    length = other.length;
    buffer = new char[maxCapacity];
    strcpy(buffer, other.buffer);
    return (*this);
}

CString &CString::operator=(const char *str) {
    if (buffer == str) {
        return (*this);
    }
    delete[] buffer;
    length = strlen(str);
    maxCapacity = getCapacityForGrowByFactor(length) + 1;
    buffer = new char[maxCapacity];
    strcpy(buffer, str);

    return (*this);
}

CString &CString::operator+=(char a) {
    if (length + 1 >= maxCapacity) {
        growByFactor();
    }
    buffer[length] = a;
    ++length;
    buffer[length] = 0;
    return (*this);
}

void CString::growByFactor() {
    grow(getCapacityForGrowByFactor(maxCapacity));
}


int CString::getCapacityForGrowByFactor(int length) {
    return (int) (floor(length * growFactor));
}

void CString::grow(int newCapacity) {
    maxCapacity = newCapacity;
    char *newBuffer = new char[newCapacity];
    strcpy(newBuffer, buffer);
    delete[] buffer;
    buffer = newBuffer;
}

CString &CString::operator+=(const char *str) {
    const int otherStrLength = strlen(str);
    if (length + otherStrLength + 1 >= maxCapacity) {
        grow(getCapacityForGrowByFactor(length + otherStrLength));
    }
    strcat(buffer, str);
    length += otherStrLength;
    return (*this);
}

CString &CString::operator+=(const CString &str) {
    return operator+=(str.buffer);
}

CString operator+(const CString &first, const char *second) {
    CString temp(first);
    temp += second;
    return temp;
}

CString operator+(const char *first, const CString &second) {
    CString temp(first);
    temp += second;
    return temp;
}

void CString::Append(char symbol) {
    operator+=(symbol);
}

void CString::SetBufferLength(int newLength) {
    assert(newLength > maxCapacity);
    char *new_buffer = new char[newLength];
    for (int i = 0; i < length; i++) {
        new_buffer[i] = buffer[i];
    }
    new_buffer[length] = 0;
    if (buffer != nullptr) {
        delete[]buffer;
    }
    buffer = new_buffer;
    maxCapacity = newLength;
}

void CString::Append(const char *str) {
    operator+=(str);
}

void CString::Append(const CString &str) {
    operator+=(str);
}

int CString::Compare(const char *str) const {
    assert(str != nullptr);
    return strcmp(buffer, str);
}

int CString::CompareNoCase(const char *str) const {
    assert(str != nullptr);

    CString a(str);
    CString b(buffer);
    a.MakeLower();
    b.MakeLower();
    return strcmp(a.buffer, b.buffer);
}

bool CString::EqualsNoCase(const char *str) const {
    assert(str != nullptr);
    return CompareNoCase(str) == 0;
}

char &CString::GetAt(int index) {
    assert(index >= 0 && index <= length);
    return buffer[index];
}

char &CString::operator[](int index) {
    assert(index >= 0 && index <= length);
    return buffer[index];
}

const char &CString::operator[](int index) const {
    assert(index >= 0 && index <= length);
    return buffer[index];
}

bool CString::IsEmpty() const {
    assert(buffer != nullptr);
    return buffer[0] == 0;
}

void CString::MakeEmpty() {
    delete[] buffer;
    buffer = new char[maxCapacity];
    buffer[0] = 0;
    length = 0;
}

CString CString::SubString(int firstPos, int count) const {
    assert(firstPos >= 0 && firstPos < length);
    return CString(buffer + firstPos, count);
}

CString CString::SubString(int firstPos) const {
    assert(firstPos >= 0 && firstPos < length);
    return CString(buffer + firstPos);
}

void CString::MakeUpper() {
    for (int i = 0; buffer[i]; i++) {
        buffer[i] = toupper(buffer[i]);
    }
}

void CString::MakeLower() {
    for (int i = 0; buffer[i]; i++) {
        buffer[i] = tolower(buffer[i]);
    }
}

void CString::MakeReverse() {

    if (*buffer == 0) { return; }

    char *start = buffer;
    char *end = start + length - 1;
    for (; start < end; ++start, --end) {
        std::swap(*start, *end);
    }
}

int CString::Find(char ch, int startPos) const {
    assert(startPos >= 0 && startPos <= length);
    char *pch = strchr(buffer + startPos, ch);
    return (pch == nullptr) ? -1 : (pch - buffer);
}

int CString::Find(const char *subString, int startPos) const {
    assert(subString != nullptr);
    assert(startPos >= 0 && startPos < length);
    char *pch = strstr(buffer + startPos, subString);
    return (pch == nullptr) ? -1 : (pch - buffer);
}

int CString::FindNoCase(const char *subString, int startPos) const {
    assert(subString != nullptr);
    assert(startPos >= 0 && startPos < length);

    CString a(subString);
    CString b(buffer);
    a.MakeLower();
    b.MakeLower();

    return b.Find(subString, startPos);
}

void CString::StrDel(int pos, int num) {
    assert(pos + num <= length);
    assert(num >= 1);

    CString string(buffer, pos);
    string += (buffer + (pos + num));
    operator=(string);
    length -= num;
}

void CString::StrDel(int pos) {
    StrDel(pos, 1);
}

void CString::StrIns(const char *str, int pos) {
    CString string(this->buffer, pos);
    string += str;
    string += (buffer + pos);
    operator=(string);
}

void CString::StrIns(const CString &str, int pos) {
    StrIns(str.buffer, pos);
}

void CString::StrReplace(int pos, const CString &str) {
    StrReplace(pos, str.buffer);
}

void CString::StrReplace(int pos, const char *str) {
    assert(str != nullptr);
    const int otherStrLength = strlen(str);
    assert(pos < length);
    for (int i = pos; i < pos + otherStrLength && buffer[i]; i++) {
        buffer[i] = str[i - pos];
    }
}

void CString::CharIns(char ch, int pos) {
    if (length + 1 >= maxCapacity) {
        growByFactor();
    }
    for (int i = length; i > pos; i--) {
        buffer[i] = buffer[i - 1];
    }
    buffer[pos] = ch;
    ++length;
    buffer[length] = 0;
}

void CString::ReplaceAll(char src, char newSymbol) {
    char *strPtr = buffer;
    while ((strPtr = strchr(strPtr, src)) != nullptr)
        *strPtr++ = newSymbol;
}

void CString::ReplaceAll(char src, const char *newStr) {
    char ch[2] = {src, '\0'};
    ReplaceAll(ch, newStr);
}


void CString::ReplaceAll(const char *src, const char *newStr) {

    /* Another possible solution
     int otherLength = strlen(src);
     int newStrLength = strlen(newStr);
     int k = 0;
     while (k < length && (k = Find(src,k)) != -1){
         StrDel(k,otherLength);
         StrIns(newStr,k);
         k+=newStrLength;
    }*/

    CString string;
    char *p;
    if (!(p = strstr(buffer, src))) {
        return;
    }

    int i = 0;
    int scrLength = strlen(src);
    while (buffer[i]) {
        if (!(p = strstr(buffer + i, src))) break;
        string += CString(buffer + i, (p - buffer) - i);
        string += newStr;
        i = (p - buffer) + scrLength;
    }

    if (buffer[i]) {
        string += (buffer + i);
    }
    operator=(string);
}

void CString::ReplaceAll(const char *src, char newSymbol) {
    char ch[2] = {newSymbol, '\0'};
    ReplaceAll(src, ch);
}

CString operator+(char ch, const CString &str) {
    CString temp;
    temp = ch;
    temp += str;
    return temp;
}

CString operator+(const CString &str, char ch) {
    CString temp(str);
    temp += ch;
    return temp;
}

CString operator+(const CString &str1, const CString &str2) {
    CString temp(str1);
    temp += str2;
    return temp;
}

int main() {
    TestCString();
    return 0;
}