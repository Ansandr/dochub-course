#include "document.hpp"
#include <iostream>

Document::Document()
{
    id = -1;
    date = L"0";
    pin = L"0000";
    name = L"";
}

Document::Document(int id, wstring date)
{
    this->id = id;
    this->date = date;
}

Document::Document(int id, wstring date, wstring pin, wstring name)
{
    this->id = id;
    this->date = date;
    this->pin = pin;
    this->name = name;
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

void Document::setName(const wstring& newName)
{
    this->name = newName;
}

wstring Document::getDateString() const
{
    return this->date;
}

wstring Document::getName() const
{
    return this->name;
}

void Document::printInfo() const
{
    wcout << L"Паспорт:\n";
    wcout << L"Ім'я: " << name << "\n";
    wcout << L"Дійсний до: " << date << "\n";
    wcout << L"Номер: " << id << "\n";
}

Document &Document::operator=(const Document &obj)
{
    if (this != &obj) {
        id = obj.id;
        date = obj.date;
    }

    return *this;
}

wstring Document::writeRow() const
{
    wstringstream ss;
    ss << getId() << L',' << getDateString() << L',' << getPin() << L',' << getName();
    return ss.str();
}

wostream &operator<<(wostream &os, const Document &doc)
{
    os << doc.getId() << L',' << doc.getDateString() << L',' << doc.getPin() << L',' << doc.getName();
    return os;
}