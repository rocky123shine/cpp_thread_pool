#include <iostream>
#include "thread_pool/xthread_pool.h"

class MyTask : public XTask {
public:
    int Run() override {
        std::cout << " MyTask " << name << std::endl;
        return 0;
    }

    std::string name = " ";
};

int main() {
    XThreadPool pool;
    pool.Init(16);
    pool.Start();
    MyTask task1;
    task1.name = "test name 0001";
    pool.AddTask(&task1);
    getchar();
    return 0;
}
