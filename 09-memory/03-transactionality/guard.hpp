#pragma once

class ScopeGuard {
private:
    void (*rollback_func)();

public:
    ScopeGuard(void (*rollback_func)()): rollback_func(rollback_func) {} 

    ~ScopeGuard() {
        if (rollback_func != nullptr) {
            rollback_func();
        }
    }

    void cancel_rollback() {
        rollback_func = nullptr;
    }
};
