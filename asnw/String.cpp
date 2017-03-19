
#include "String.h"
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <cctype>

using namespace std;

void TestCString() {
    CString str1 = "test string";
    cout << str1 << endl;
    str1 = "Hello world"; // const char *
    cout << str1.GetMaxCapacity() << endl;

    cout << str1 + " from Barcelona! " << endl;
    cout << "Hello, " + str1 << endl;

    cout << str1 << endl;
    cout << str1.GetMaxCapacity() << endl;

}

CString::CString() {
    buffer = new char[maxCapacity];
    buffer[0] = 0;
}

explicit CString::CString(char c, int repeatCount) {
    length = repeatCount;
    maxCapacity = getCapacityForGrowByFactor(length + 1);
    buffer = new char[maxCapacity];
    for (int i = 0; i < length; i++) {
        buffer[i] = c;
    }
    buffer[length] = 0;
}

CString::CString(const char *str, int length) {
    this.length = length;
    assert(length >= 0);
    maxCapacity = getCapacityForGrowByFactor(length);
    buffer = new char[maxCapacity];
    strncpy(buffer, str, length);
    buffer[length] = 0;
}

CString::CString &operator=(char ch) {
    delete[] buffer;
    maxCapacity = getCapacityForGrowByFactor(80);
    buffer = new char[maxCapacity];
    buffer[0] = ch;
    buffer[1] = 0;
    return *this;
}

CString::CString(const char *cStr) {
    length = strlen(cStr);
    assert(length >= 0);
    maxCapacity = getCapacityForGrowByFactor(length);
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

void CString::operator=(const CString &other) {
    if (this == &other) {
        return;
    }
    delete[] buffer;
    maxCapacity = other.maxCapacity;
    length = other.length;
    buffer = new char[maxCapacity];
    strcpy(buffer, other.buffer);
}

void CString::operator=(const char *str) {
    if (buffer == str) {
        return;
    }
    delete[] buffer;
    length = strlen(str);
    maxCapacity = getCapacityForGrowByFactor(length);
    buffer = new char[maxCapacity];
    strcpy(buffer, str);
}

void CString::operator+=(char a) {
    if (length + 1 >= maxCapacity) {
        growByFactor();
    }
    buffer[length] = a;
    ++length;
    buffer[length] = 0;
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

void CString::operator+=(const char *str) {
    const int otherStrLength = strlen(str);
    if (length + otherStrLength + 1 >= maxCapacity) {
        grow(getCapacityForGrowByFactor(length + otherStrLength));
    }
    strcat(buffer, str);
}

void CString::operator+=(const CString &str) {
    operator+=(str.buffer);
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

void CString::Append(const char *str) {
    operator+=(str);
}

void CString::Append(const CString &str) {
    operator+=(str);
}

int CString::Compare(const char *str) const {
    std::assert(str != nullptr);
    return strcmp(buffer, str);
}

int CString::CompareNoCase(const char *str) const {
    std::assert(str != nullptr);

    CString a(str);
    CString b(buffer);

    for (int i = 0; a[i]; i++) {
        a[i] = std::tolower(a[i]);
    }
    for (int i = 0; b[i]; i++) {
        b[i] = std::tolower(b[i]);
    }
    return strcmp(a.buffer, b.buffer);
}

bool CString::EqualsNoCase(const char *str) const {
    std::assert(str != nullptr);
    return CompareNoCase(str) == 0;
}

char &CString::GetAt(int index) {
    return buffer[index];
}

char &CString::operator[](int index) {
    return buffer[index];
}

const char &CString::operator[](int index) const {
    return buffer[index];
}

bool CString::IsEmpty() const {
    std::assert(buffer != nullptr);
    return buffer[0] == 0;
}

void CString::MakeEmpty() {
    delete[] buffer;
    buffer = new char[maxCapacity];
    buffer[0] = 0;
    length = 0;
}

CString CString::SubString(int firstPos, int count) const {
    CString str;
    for (int i = firstPos; i < firstPos + count && buffer[i]; i++) {
        str += buffer[i];
    }
    return str;
}

CString CString::SubString(int firstPos) const {
    CString str;
    for (int i = firstPos; buffer[i]; i++) {
        str += buffer[i];
    }
    return str;
}

void CString::MakeUpper() {
    while (*buffer = std::toupper(*buffer)) {
        buffer++;
    }
}

void CString::MakeLower() {
    for (i = 0; foo[i]; i++) {
        foo[i] = tolower(foo[i]);
    }
}

void CString::MakeReverse() {

    if (*buffer == 0) {
        return;
    }

    char *start = buffer;
    char *end = start + strlen(buffer) - 1;

    while (end > start) {
        std::swap(*start, *end);
        ++start;
        --end;
    }
}

int CString::Find(char ch, int startPos) const {
    char *pch;
    pch = strchr(buffer + startPos, ch);
    if (pch == nullptr) {
        return -1;
    }
    return pch - buffer;
}

int CString::Find(const char *subString, int startPos = 0) const {
    char *pch;
    pch = strstr(buffer + startPos, subString);
    if (pch == nullptr) {
        return -1;
    }
    return pch - buffer;
}

int CString::FindNoCase(const char *subString, int startPos = 0) const {
    std::assert(str != nullptr);

    CString a(subString);
    //try buffer + startPos
    CString b(buffer);

    for (int i = 0; a[i]; i++) {
        a[i] = std::tolower(a[i]);
    }
    for (int i = 0; b[i]; i++) {
        b[i] = std::tolower(b[i]);
    }
    return b.Find(subString, startPos);
}

CString operator+(char ch, const CString &str) {
    CString temp;
    temp = ch;
    temp += str;
    return temp;
}

CString operator+(const CString &str, char ch) {
    CString temp(str);
    str += ch;
    return temp;
}

CString operator+(const CString &str1, const CString &str2) {
    CString temp(str1);
    str1 += str2;
    return temp;
}

