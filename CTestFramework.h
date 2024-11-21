#include <iostream>
#include <vector>
#include <functional>

#define __GET_UNIQUE_NAME2__(name, num) name##num
#define __GET_UNIQUE_NAME1__(name, num) __GET_UNIQUE_NAME2__(name, num)
#define UNIQUE_NAME(base) __GET_UNIQUE_NAME1__(base, __COUNTER__)

#define LOG(format,args...) \
do { \
    printf(format,##args); \
} while (0);


#define TEST_CASE(name) \
    static TestResult name(); \
    static TestRegister UNIQUE_NAME(register_)(name, #name); \
    static TestResult name()

enum TestResult {
    CASE_SUCCESS = 0,
    CASE_FAIL
};

class TestRegistry {
public:
    TestResult registry_result;
    static TestRegistry& getInstance() {
        static TestRegistry instance;
        return instance;
    }

    void addTest(TestResult(*testFunc)(), const char* testName) {
        tests.push_back({testFunc, testName});
    }

    void runTests() {
        int fail_count = 0;
        registry_result = CASE_SUCCESS;

        for (auto& test : tests) {
            std::cout << "Running test: " << test.name << std::endl;
            test.result = test.func();
            if (test.result != CASE_SUCCESS) {
                fail_count++;
            }
        }

        LOG("==================================== Test Result ====================================\n");
        LOG("Total tests run: %ld Failed: %d\n", tests.size(), fail_count);
        if (fail_count != 0) {
            registry_result = CASE_FAIL;
            for (auto &test: tests) {
                if (test.result != CASE_SUCCESS) {
                    LOG("Test %s failed, result = %d\n", test.name, test.result);
                }
            }
        }
    }

    TestResult getResult() {
        return registry_result;
    }

private:
    struct Test {
        TestResult (*func)();
        const char* name;
        TestResult result;
    };

    std::vector<Test> tests;
};

class TestRegister {
public:
    TestRegister(TestResult(*testFunc)(), const char* testName) {
        TestRegistry::getInstance().addTest(testFunc, testName);
    }
};

int main() {
    TestRegistry::getInstance().runTests();
    return TestRegistry::getInstance().getResult();
}
