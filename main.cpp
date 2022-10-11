#include <iostream>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "header.hpp"

#define BLOCK_SIZE 8

auto main() -> int {
    unsigned int key[4] = { 0xFACE, 0xDEAD, 0xBABE, 0xD00D };
    std::string path = "/home/draco/TobeEncrypted";

    bool main_loop = true;
    int user_input;

    while (main_loop) {
        main_menu();
        std::cout << "\n> ";
        std::cin >> user_input;

        switch (user_input) {
            case 1:
                for (const auto& entry : std::filesystem::directory_iterator(path)) {
                    std::fstream file(entry.path(), std::ios::in | std::ios::out | std::ios::binary);

                    //Check if file is correctly opened
                    if (std::filesystem::is_directory(entry.path())) {
                        std::cout << "Opening file: " << entry.path().stem().string() << std::endl;
                        std::filesystem::directory_iterator files(entry.path());
                        entry.path().string();
                    }

                    else if (!std::filesystem::is_directory(entry.path())) {
                        std::cout << "Opened File " << entry.path().stem().string() << std::endl;
                        file.seekg(0, std::ios::end);
                        unsigned file_size = file.tellg(); //Get file size
                        std::cout << "File size: " << file_size << " bytes" << std::endl;
                        file.seekg(std::ios::beg);
                        file.clear();

                        //Calculate number of blocks to be encrypted/decrypted
                        auto block_number = file_size / BLOCK_SIZE;
                        if (file_size % BLOCK_SIZE != 0) { ++block_number; }
                        std::cout << "Number of blocks: " << block_number << std::endl;

                        //Declare data array for file operations
                        unsigned char data_array[BLOCK_SIZE];
                        unsigned file_position = file.tellg();

                        std::cout << "Starting encryption..." << std::endl;
                        for (int i = 0; i < block_number; i++) {
                            //Get data from file
                            file.seekg(file_position);
                            file.read((char*)data_array, BLOCK_SIZE);

                            //Encrypt
                            Encryptor::encryptor(32, (uint32_t *) data_array, key);

                            //Write to file
                            file.seekp(file_position);
                            file.write((char*)data_array, BLOCK_SIZE);

                            //Zero out the data array and increase the pos counter
                            memset(data_array, 0, BLOCK_SIZE);
                            file_position += BLOCK_SIZE;
                        }

                        //Close file
                        file.close();
                        std::cout << "Closing file" << std::endl;
                    }
                }
                break;

            case 2:
                for (const auto& entry : std::filesystem::directory_iterator(path)) {
                    std::fstream file(entry.path(), std::ios::in | std::ios::out | std::ios::binary);

                    //Check if file is correctly opened
                    if (std::filesystem::is_directory(entry.path())) {
                        std::cout << "Opening file: " << entry.path().stem().string() << std::endl;
                        std::filesystem::directory_iterator files(entry.path());
                        entry.path().string();
                    }

                    else if (!std::filesystem::is_directory(entry.path())) {
                        std::cout << "Opened File " << entry.path().stem().string() << std::endl;
                        file.seekg(0, std::ios::end);
                        unsigned file_size = file.tellg(); //Get file size
                        std::cout << "File size: " << file_size << " bytes" << std::endl;
                        file.seekg(std::ios::beg);
                        file.clear();

                        //Calculate number of blocks to be encrypted/decrypted
                        auto block_number = file_size / BLOCK_SIZE;
                        if (file_size % BLOCK_SIZE != 0) { ++block_number; }
                        std::cout << "Number of blocks: " << block_number << std::endl;

                        //Declare data array for file operations
                        unsigned char data_array[BLOCK_SIZE];
                        unsigned file_position = file.tellg();

                        std::cout << "Starting decryption..." << std::endl;
                        for (int i = 0; i < block_number; i++) {
                            //Get data from file
                            file.seekg(file_position);
                            file.read((char*)data_array, BLOCK_SIZE);

                            //Encrypt
                            Decryptor::decryptor(32, (uint32_t *) data_array, key);

                            //Write to file
                            file.seekp(file_position);
                            file.write((char*)data_array, BLOCK_SIZE);

                            //Zero out the data array and increase the pos counter
                            memset(data_array, 0, BLOCK_SIZE);
                            file_position += BLOCK_SIZE;
                        }

                        //Close file
                        file.close();
                        std::cout << "Closing file" << std::endl;
                    }
                }
                break;

            case 0:
                main_loop = false;
                break;

            default:
                std::cout << "[-] Invalid command, Please try again" << std::endl;
        }
    }
}

auto main_menu() -> void {
    std::cout << "[1] Encrypt" << std::endl;
    std::cout << "[2] Decrypt" << std::endl;
    std::cout << "[0] Exit" << std::endl;
}
