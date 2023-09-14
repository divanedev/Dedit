#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
std::vector <std::string> Lines;

void OpenFile () {
    char filename[1024];
    FILE *f = popen("zenity --file-selection --file-filter=*.txt", "r");
    fgets(filename, 1024, f);
    std::string FileName;
    for (int i = 0; i < 1024; i++) {
        if (filename[i] == '\0' || filename[i] == '\n')
            break;
        std::cout << filename[i];
        FileName += filename[i];
    }
    std::ifstream stream(FileName);
    std::string line;
    bool cleared = false;
    while (getline(stream, line)) {
        if (!cleared) {
            Lines.clear();
            cleared = true;
        }
        Lines.push_back(line);
    }
    if (Lines.empty())
        Lines.push_back("");
}

void SaveFile () {
    char filename[1024];
    FILE *f = popen("zenity --file-selection --save --confirm-overwrite --file-filter=*.txt", "r");
    fgets(filename, 1024, f);
    std::string FileName;
    for (int i = 0; i < 1024; i++) {
        if (filename[i] == '\0' || filename[i] == '\n')
            break;
        std::cout << filename[i];
        FileName += filename[i];
    }
    std::ofstream stream(FileName);
    if (stream.is_open()) {
        for (std::string Line : Lines) {
            stream << Line;
            stream << '\n';
        }
    }
    stream.close();
}