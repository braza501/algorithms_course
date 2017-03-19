// dynamic array
#include <cassert>
#include <iostream>

#include "ArrayOfInts.h"

CArray::CArray() {
    maxCapacity = 18;
    size = 0;
    buffer = new int[maxCapacity];
}

CArray::~CArray() {

    if (buffer != nullptr) {
        delete[]buffer;
    }
}

int CArray::Size() const {
    return size;
}

int CArray::BufferSize() const {
    return maxCapacity;
}

bool CArray::IsEmpty() const {
    return size == 0;
}

int *CArray::GetPtr() {
    if (size == 0) {
        return nullptr;
    }
    return buffer;
}

const int *CArray::GetPtr() const {
    if (size == 0) {
        return nullptr;
    }
    return buffer;
}

int &CArray::operator[](int index) {
    assert(index >= 0 && index < size);
    return buffer[index];
}

const int &CArray::operator[](int index) const {
    assert(index >= 0 && index < size);
    return buffer[index];
}

const int &CArray::Last() const {
    if (IsEmpty()) {
        throw "emtpy array!";
    }
    return buffer[size - 1];
}

int &CArray::Last() {
    if (IsEmpty()) {
        throw "emtpy array!";
    }
    return buffer[size - 1];
}

// First element
const int &CArray::First() const {
    if (IsEmpty()) {
        throw "emtpy array!";
    }
    return buffer[0];

}

int &CArray::First() {
    if (IsEmpty()) {
        throw "emtpy array!";
    }
    return buffer[0];
}

void CArray::Add(const int &anElem) {
    if(size == maxCapacity){
        Grow(2*size);
    }
    buffer[size++] = anElem;
}

void CArray::Add(const int &anElem, int count) {
    if(size == maxCapacity){
        Grow(2*(size + count));
    }
    for (int i = 0; i < count; i++) {
        buffer[size++] = anElem;
    }
}

void CArray::Add(const CArray &ar) {
    if(size == maxCapacity){
        Grow(2*(size + ar.Size()));
    }
    for (int i = 0; i < ar.Size(); i++) {
        buffer[size++] = ar[i];
    }
}

bool CArray::IsValidIndex(int index) const {
    return (index >= 0 && index < size);
}


void CArray::InsertAt(const int &what, int location) {
    InsertAt(what, location, 1);
}

void CArray::InsertAt(const int &what, int location, int count) {
    if (size + count > maxCapacity) {
            Grow(2*(size + count));
    }

    for (int i = size + count - 1; i > location + count - 1; i--) {
        buffer[i] = buffer[i - count];
    }
    for (int i = location; i < location + count; i++) {
        buffer[i] = what;
    }
    size += count;
}

void CArray::InsertAt(const CArray &what, int location) {
    if (size + what.Size() > maxCapacity) {
        Grow(2*(size + what.Size()));
    }

    for (int i = size + what.Size() - 1; i > location + what.Size() - 1; i--) {
        buffer[i] = buffer[i - what.Size()];
    }
    int j = 0;
    for (int i = location; i < location + what.Size(); i++) {
        buffer[i] = what[j++];
    }
    size += what.Size();
}


void CArray::DeleteLast() {
    assert(!IsEmpty());
    size--;
    buffer[size] = int();
}

void CArray::DeleteAll() {
    for (int i = 0; i < size; i++) {
        buffer[i] = int();
    }
    size = 0;
}


void CArray::FreeBuffer() {
    if (buffer == nullptr)
        return;

    delete[] buffer;
    buffer = nullptr;
    size = 0;
    maxCapacity = 0;
}

void CArray::CopyTo(CArray &dest) const {
    dest.FreeBuffer();
    dest.SetBufferSize(maxCapacity);
    dest.SetSize(size);
    for (int i = 0; i < size; i++) {
        dest[i] = buffer[i];
    }
}

void CArray::MoveTo(CArray &dest) {
    if (size + dest.Size() > dest.BufferSize()) {
        dest.SetBufferSize(size + dest.Size());
    }
    int old_size = dest.Size();
    dest.SetSize(size + dest.Size());
    int j = 0;
    for (int i = old_size; i < dest.Size(); i++) {
        dest[i] = buffer[j++];
    }
}

int CArray::Find(const int &what, int startPos) const {
    for (int i = startPos; i < size; i++) {
        if (buffer[i] == what) {
            return i;
        }
    }
    return -1;
}

void CArray::DeleteAt(int location, int num) {
    assert(IsValidIndex(location));
    assert(location + num <= size);

    for (int i = location; i < size - num; i++) {
        buffer[i] = buffer[i + num];
    }

    for (int i = size - num; i < size; i++) {
        buffer[i] = int();
    }
    size -= num;
}

bool CArray::Has(const int &what) const {
    for (int i = 0; i < size; i++) {
        if (buffer[i] == what) {
            return true;
        }
    }
    return false;
}


void CArray::SetBufferSize(int nElements) {
    assert(nElements > maxCapacity);

    int *new_buffer = new int[nElements];
    for (int i = 0; i < size; i++) {
        new_buffer[i] = buffer[i];
    }
    if (buffer != nullptr) {
        delete[]buffer;
    }
    buffer = new_buffer;
    maxCapacity = nElements;
}

// Increases buffer size according to grow politics
void CArray::Grow(int newSize) {
    SetBufferSize(newSize);
}

// Replace element at index. Old element is deleted with destructor
// New element copied with copy constructor
void CArray::ReplaceAt(const int &newElem, int location) {
    assert(IsValidIndex(location));

    buffer[location] = newElem;
}

void CArray::SetSize(int newSize) {
    assert(newSize <= maxCapacity);
    if (newSize > size) {
        size += newSize;
    } else {
        for (int i = size; i > size - newSize; i--) {
            buffer[i] = int();
        }
        size -= newSize;
    }
}

int main() {

    CArray array;
    CArray arrayB;
    arrayB.Add(-4);
    arrayB.Add(-3);
    arrayB.Add(-2);

    array.Add(3);
    array.Add(4);
    array.Add(6);
    array.Add(7);
    array.Add(8);
    array.Add(1);
    array.Add(23, 2);
    array.Add(arrayB);

    for (int i = 0; i < array.Size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "add two copies of 77 to 6th position" << std::endl;
    array.InsertAt(77, 6, 2);

    for (int i = 0; i < array.Size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "add copy of 101 to 0th position" << std::endl;
    array.InsertAt(101, 0);
    for (int i = 0; i < array.Size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "replace elem in the 7th position with 333 " << std::endl;
    array.ReplaceAt(333, 7);
    for (int i = 0; i < array.Size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Size and capacity of the array: " << std::endl;

    std::cout << array.Size() << " ";
    std::cout << array.BufferSize() << std::endl;;

    array.DeleteLast();
    std::cout << "Remove the last element " << std::endl;
    for (int i = 0; i < array.Size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "The first element :  " << array.First() << std::endl;

    array.CopyTo(arrayB);
    std::cout << "First element of the array " << array.First() << std::endl;
    std::cout << "Content of A was copied to ArrayB :  " << std::endl;
    for (int i = 0; i < arrayB.Size(); i++) {
        std::cout << arrayB[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Size and capacity of the arrayB: " << std::endl;

    std::cout << arrayB.Size() << " ";
    std::cout << arrayB.BufferSize() << std::endl;
    std::cout << std::endl;
    std::cout << "position of 333 : " << array.Find(333) << " " << std::boolalpha << array.Has(333) << std::endl;
    std::cout << std::endl;
    array.DeleteAll();
    arrayB.MoveTo(array);
    for (int i = 0; i < array.Size(); i++) {
        std::cout << array[i] << " ";
    }
    array.DeleteAt(5, 7);
    std::cout << std::endl;
    for (int i = 0; i < array.Size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::boolalpha << array.IsValidIndex(4) << std::endl;
    std::cout << std::boolalpha << array.IsValidIndex(120) << std::endl;

    CArray arrayC;

    for(int i =0; i< 16; i++){
        arrayC.Add(i);
    }

    std::cout << std::endl;
    for (int i = 0; i < arrayC.Size(); i++) {
        std::cout << arrayC[i] << " ";
    }
    arrayC.InsertAt(77,3,20);
    std::cout << std::endl;
    for (int i = 0; i < arrayC.Size(); i++) {
        std::cout << arrayC[i] << " ";
    }
    return 0;
}
