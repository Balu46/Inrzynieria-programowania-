#pragma once
#include <exception>
#include <string>

class LibraryException : public std::exception {
public:
    LibraryException(const std::string& message) : m_message(message) {}

    const char* what() const noexcept override {
        return m_message.c_str();
    }

private:
    std::string m_message;
};