#include "document.hpp"
#include <iostream>

Document::Document()
{
    id = -1;
    date = L"0";
    pin = L"1234";
}

Document::Document(int id, const wstring &date)
{
    this->id = id;
    this->date = date;
}

Document::Document(int id, const wstring &date, wstring pin) : Document(id, date)
{
    this->pin = pin;
}

int Document::getId() const
{
    return this->id;
}

wstring Document::getPin() const
{
    return pin;
}

void Document::setDateString(const wstring date)
{
    this->date = date;
}

void Document::setPin(const wstring& newPin)
{
    this->pin = newPin;
}

void Document::setId(const int newId)
{
    this->id = newId;
}

wstring Document::getDateString() const
{
    return this->date;
}

void Document::printInfo() const
{
    wcout << "Document:\n";
    wcout << "id: " << id << "\n";
    wcout << "date: " << date << "\n";
}

Document &Document::operator=(const Document &obj)
{
    if (this != &obj) {
        id = obj.id;
        date = obj.date;
    }
}

wostream &operator<<(wostream &os, const Document &doc)
{
    os << "\t" << doc.getDateString() << "\t" << doc.getPin();
    return os;
}