#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void RewriteFile(std::string filename = "Cs-137.dat", std::string newFilename = "Cs-137.bin"){
    // Otwieranue pliku
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr << "File not found" << std::endl;
        return;
    }
    else{
        std::cout << "File opened" << std::endl;
    }

    // Tworzenie nowego pliku
    std::ofstream newFile(newFilename, std::ios::binary | std::ios::out);
    if(!newFile.is_open()){
        std::cerr << "File not created" << std::endl;
        return;
    }
    else{
        std::cout << "File created" << std::endl;
    }

    // Zapisywanie danych do nowego pliku
    double a;
    while(file >> a){
        newFile.write((char*)&a, sizeof(double));
    }

    file.close();
    newFile.close();

    std::cout << "File rewritten" << std::endl;
    
    // Sprawdzanie zawartości nowego pliku
    std::ifstream newFileCheck(newFilename);
    if(!newFileCheck.is_open()){
        std::cerr << "File not found" << std::endl;
        return;
    }
    else{
        std::cout << "File checking" << std::endl;
    }

    double b;
    while(newFileCheck.read((char*)&b, sizeof(double))){
        std::cout << b << std::endl;
    }

    newFileCheck.close();

    std::cout << "File checked" << std::endl;

}