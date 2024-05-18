#include "services/persistence/document_file_repository.hpp"
#include "document_file_repository.hpp"

#include <vector>

DocumentFileRepository::DocumentFileRepository(const std::string &fileName)
: fileName(fileName)
{
    lastId = getLenght();
}

void DocumentFileRepository::createDocument(Document document) {
    wofstream outFile(fileName, ios_base::app);
    if (outFile.is_open()) {
        outFile << ++lastId << "\t" << document.writeRow() << "\n"; //id document
        outFile.close();
        wcout << L"Документ збережений\n";
    }
}

Document *DocumentFileRepository::readDocument(int id) {
    int cid;
    wstring date;
    wstring pin;

    wifstream inFile(fileName);
    if (inFile.is_open()) {
        wstring line;
        while (getline(inFile, line)) {

            wistringstream ss(line);

            ss >> cid;
            ss >> date;
            ss >> pin;

            if(cid == id) {
                Document* doc = new Document(cid, date, pin);
                inFile.close();
                return doc;
            }
        }
        inFile.close();
    }
    return nullptr;
}

void DocumentFileRepository::updateDocument(int id, const Document &newDocument) {
    vector<wstring> lines;
    bool found = false;

    // Читати файл повністю
    wfstream file(fileName, ios_base::in);
    if (file.is_open()) {
        wstring line;
        while (getline(file, line)) {
            int cid;

            wistringstream ss(line);
            
            ss >> cid;

            wostringstream output_string;
            if(cid == id) { // якщо знайдено айді таке ( число)
                output_string << id << "\t" << newDocument; // переписати стрічку, лишивши айді
                line = output_string.str();
                found = true;
            }

            lines.push_back(line); // Додати в вектор лінію
        }
        file.close();
    }

    // Створюєм тимчасовий файл для перезапису, якщо знайдено
    if (found) {
        wofstream tempFile("temp.txt");
        if (tempFile.is_open()) {
            for (wstring l : lines) {
                tempFile << l << "\n";
            }
            tempFile.close();

            remove(fileName.c_str());
            rename("temp.txt", fileName.c_str());
        }
    }
}

void DocumentFileRepository::deleteDocument(int id) {
    vector<wstring> lines;
    bool found = false;

    // Читати файл повністю
    wfstream file(fileName, ios_base::in);
    if (file.is_open()) {
        wstring line;
        while (getline(file, line)) {
            int cid;

            wstringstream ss(line);

            ss >> cid;

            if(cid != id) { // якщо це не айді
                lines.push_back(line); // Додати в вектор лінію
            } else {
                found = true;
            }
            
        }
        file.close();
    }

    // Створюєм тимчасовий файл для перезапису, якщо знайдено
    if (found) {
        wofstream tempFile("temp.txt", ios_base::app);
        if (tempFile.is_open()) {//завжди фалс
            for (wstring l : lines) {
                tempFile << l << "\n";
            }
            tempFile.close();

            remove(fileName.c_str());
            rename("temp.txt", fileName.c_str());
        }
    }
}

int DocumentFileRepository::getLenght()
{
    int lastId = 0;
    wfstream file(fileName);
    if (file.is_open()) {
        file.seekg(-1, std::ios_base::end);
        bool keepLooping = true;
        while(keepLooping) {
            wchar_t ch;
            file.get(ch);                            // Get current byte's data

            if((int)file.tellg() <= 1) {             // If the data was at or before the 0th byte
                file.seekg(0);                       // The first line is the last line
                keepLooping = false;                // So stop there
            }
            else if(ch == '\n') {                   // If the data was a newline
                keepLooping = false;                // Stop at the current position.
            }
            else {                                  // If the data was neither a newline nor at the 0 byte
                file.seekg(-2,ios_base::cur);        // Move to the front of that data, then to the front of the data before it
            }
        }
        
        wstring lastLine;
        getline(file, lastLine);
        int lastId;
        wstringstream ss(lastLine);
        ss >> lastId;
        file.close();
    }
    return lastId;
}
