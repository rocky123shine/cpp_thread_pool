//
// Created by rocky on 2023/8/23.
//

#ifndef THREAD_POOL_XTHREAD_POOL_H
#define THREAD_POOL_XTHREAD_POOL_H

#include <thread>
#include <mutex>
#include <vector>
#include <list>

class XTask {
public:
    virtual int Run() = 0;
};

class XThreadPool {
public:
    /// @param num线程池的数量
    void Init(int num);

    /// 启动所有线程  必须先 Init
    void Start();

    void AddTask(XTask *task);

    XTask *GetTask();

private:
    ///线程池线程的入口函数
    void Run();

    int thread_num_ = 0;//现成数量
    std::mutex mux_;
    std::vector<std::thread *> threads_;
    std::list<XTask *> tasks_;
    std::condition_variable cv_;
};


#endif //THREAD_POOL_XTHREAD_POOL_H
