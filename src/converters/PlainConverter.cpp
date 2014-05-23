#include "PlainConverter.h"

std::string PlainConverter::decode(const std::string & message) {
    return * new std::string(message);
}

std::string PlainConverter::encode(const std::string & message) {
    return * new std::string(message);
}