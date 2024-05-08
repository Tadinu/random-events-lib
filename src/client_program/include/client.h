#pragma once

#include <memory>
#include <utility>
#include <iostream>
#include "set.h"

class Client {
    Client()
    {
        SetElement ele = SetElement("", nullptr);
        std::cout << "Client" << std::endl;
        std::cout.flush();
    }
};