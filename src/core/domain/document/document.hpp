#pragma once

#include <string>
#include <chrono>

using namespace std;

static const string dateFormat = "%Y-%m-%d"; 

class Document {
public:
    Document();
    Document(int id, const wstring& date);
    Document(int id, const wstring& date, wstring pin);


    int getId() const;
    wstring getPin() const;
    void setPin(const wstring& newPin);
    void setId(const int newId);

    void setDateString(const wstring date);

    wstring getDateString() const;
    time_t getDateTime() const;

    void printInfo() const;

    Document& operator=(const Document& obj);

    virtual wstring writeRow() const;

    friend wostream& operator<< (wostream& os, const Document& doc);

protected:
    // auto increment
    int id;
    wstring date;
    wstring pin;
};