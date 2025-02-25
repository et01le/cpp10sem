#include "guard.hpp"

#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <iostream>
#include <cassert>

bool nuclear_launch_authorized = false;

void authorize_nuclear_launch() {
    nuclear_launch_authorized = true;
}

void unauthorize_nuclear_launch() {
    nuclear_launch_authorized = false;
}

bool launch_result;

void launch() {
    std::srand(std::time(nullptr));
    launch_result = std::rand() % 2;
    if (!launch_result) {
        std::cout << "FAILURE: Rollback is expected\n";
        throw std::runtime_error(std::string());
    }
    std::cout << "SUCCESS: No rollback expected\n";
}

int main() {
    try {
        authorize_nuclear_launch();
        ScopeGuard guard = ScopeGuard(unauthorize_nuclear_launch);
        launch();
        guard.cancel_rollback();
    } catch (std::exception&) {}
    assert(launch_result == nuclear_launch_authorized);
    return 0;
}
