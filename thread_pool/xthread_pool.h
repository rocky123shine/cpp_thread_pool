//
// Created by rocky on 2023/8/23.
//

#ifndef THREAD_POOL_XTHREAD_POOL_H
#define THREAD_POOL_XTHREAD_POOL_H

#include <thread>
#include <mutex>
#include <vector>
#include <list>
#include <functional>
#include <future>

class XTask {
public:
    virtual int Run() = 0;

    std::function<bool()> is_exit = nullptr;

    auto GetReturn() {
        ///阻塞等待 返回value
        return p_.get_future().get();
    }

    void SetValue(int v) {
        p_.set_value(v);
    };

private:
    ///用来接受返回值
    std::promise<int> p_;
};

class XThreadPool {
public:
    /// @param num线程池的数量
    void Init(int num);

    /// 启动所有线程  必须先 Init
    void Start();

    void Stop();

    //void AddTask(XTask *task);
    void AddTask(std::shared_ptr<XTask> task);

    std::shared_ptr<XTask> GetTask();

    bool is_exit() { return is_exit_; }

    int task_run_count() { return task_run_count_; }

    ~XThreadPool() {
        Stop();
    }

private:
    ///线程池线程的入口函数
    void Run();

    int thread_num_ = 0;//现成数量
    std::mutex mux_;
    //std::vector<std::thread *> threads_;
    //使用智能指针
    std::vector<std::shared_ptr<std::thread>> threads_;
//    std::list<XTask *> tasks_;
    std::list<std::shared_ptr<XTask>> tasks_;
    std::condition_variable cv_;
    bool is_exit_ = false;
    std::atomic<int> task_run_count_ = {0};
};


#endif //THREAD_POOL_XTHREAD_POOL_H
