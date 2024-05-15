#pragma once

#include <string>
#include <chrono>

using namespace std;

static const string dateFormat = "%Y-%m-%d"; 

class Document {
public:
    Document();
    Document(int id, const wstring& date);


    int getId() const;

    void setDateString(const wstring date);

    wstring getDateString() const;
    time_t getDateTime() const;

    Document& operator=(const Document& obj);


    friend wostream& operator<<(wostream& os, const Document& doc);


private:
    // auto increment
    int id;
    wstring date;
};