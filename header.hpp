#ifndef RANSOMTEST_HEADER_HPP
#define RANSOMTEST_HEADER_HPP
#pragma once
#include <iostream>

auto main_menu() -> void;

struct Encryptor {
public:
    static auto encryptor(unsigned int num_rounds, uint32_t v[2], uint32_t const key_[4]) -> void;
};

struct Decryptor {
public:
    static auto decryptor(unsigned int num_rounds, uint32_t v[2], uint32_t const key_[4]) -> void;
};

#endif
