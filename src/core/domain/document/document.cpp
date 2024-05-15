#include "document.hpp"

Document::Document()
{
    id = -1;
    date = L"0";
}

Document::Document(int id, const wstring &date)
{
    this->id = id;
    this->date = date;
}

int Document::getId() const
{
    return this->id;
}

void Document::setDateString(const wstring date)
{
    this->date = date;
}

wstring Document::getDateString() const
{
    return this->date;
}

time_t Document::getDateTime() const
{
    return NULL; //TODO
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
    os << "\t" << doc.getDateString();
    return os;
}
