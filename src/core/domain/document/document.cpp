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

wostream &operator<<(wostream &os, const Document &doc)
{
    os << doc.getId() << "\t" << doc.getDateString();
    return os;
}
