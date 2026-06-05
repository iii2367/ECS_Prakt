#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <cstdint>

struct Component
{
    std::string type;
    int8_t* buffer;
};

#endif
