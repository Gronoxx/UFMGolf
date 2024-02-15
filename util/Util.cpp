//
// Created by davi on 12/2/22.
//

#include "Util.hpp"


 std::string Util::getSeparator() {
#ifdef _WIN32
    return "/";
#else
    return "/";
#endif
}
