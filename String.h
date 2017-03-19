// Author: Vladislav Vorotilov
#pragma once
#include <iostream>

class CString {
public:
    CString();
    CString( const char* cStr );
    CString( const CString& other );
    void operator=( const CString& other );
    void operator=( const char* str );
    bool operator==( const CString& other ) const;
    int Length() const { return length; }
    ~CString();

    void operator+= ( char a );
    void operator+= ( const char* str );
    void operator+= ( const CString& str );



    const char * GetBuffer() { return buffer; }
    int GetMaxCapacity() const { return maxCapacity; }

    // my enhancements
    void Append( char symbol );
    void Append( const char* str );
    void Append( const CString& str );

    int Compare( const char* str ) const;
    int CompareNoCase( const char* str ) const;
    bool EqualsNoCase( const char* str ) const;

    char& GetAt( int index );
    char& operator[]( int index );
    const char& operator[]( int index ) const;
    bool IsEmpty() const;
    void MakeEmpty();
    CString SubString( int firstPos, int count ) const;
    CString SubString( int firstPos ) const;
    friend std::ostream& operator<< (std::ostream& out, const CString& list);
    void MakeUpper();
    void MakeLower();
    void MakeReverse();
    int Find( char ch, int startPos = 0 ) const;

    int Find( const char* subString, int startPos = 0 ) const;
    int FindNoCase( const char* subString, int startPos = 0 ) const;

    explicit CString( char c, int repeatCount = 1 );
    CString( const char* str, int length );

    CString& operator=( char ch );


private:
    const double growFactor = 1.5;
    int maxCapacity = 80;
    char* buffer = nullptr;
    int length = 0;

    int getCapacityForGrowByFactor( int length );
    void growByFactor();
    void grow( int newCapacity );
};

CString operator+( const CString& first, const char* second );
CString operator+( const char* first, const CString& second );
CString operator+( char ch, const CString& str );
CString operator+( const CString& str, char ch );
CString operator+( const CString& str1, const CString& str2 );

void TestCString();