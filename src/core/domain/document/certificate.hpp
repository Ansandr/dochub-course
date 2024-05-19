#pragma once

#include "core/domain/document/document.hpp"

#include <string>

using namespace std;

class Certificate : public Document {
public:
    Certificate();
    Certificate(int certId, int docId, const wstring date, const wstring spec);

    int getConnectedDoc() const;
    wstring getSpecitifcation() const;

    void printInfo() const;

    wstring writeRow() const override;

    friend wostream& operator<< (wostream& os, const Certificate& doc);
private:
    int connectedDoc;
    wstring specification;
};