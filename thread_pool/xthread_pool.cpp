//
// Created by rocky on 2023/8/23.
//
#include <iostream>
#include "xthread_pool.h"

using namespace std;

void XThreadPool::Init(int num) {
    unique_lock<mutex> lock(mux_);
    this->thread_num_ = num;
    cout << "Thread pool Init " << num << endl;
}


void XThreadPool::Start() {
    unique_lock<mutex> lock(mux_);
    if (thread_num_ <= 0) {
        cerr << "Please Init XThreadPool" << endl;
    }
    if (!threads_.empty()) {
        cerr << "Thread pool has start" << endl;
    }
    for (int i = 0; i < thread_num_; ++i) {
        auto th = new thread(&XThreadPool::Run, this);
        threads_.push_back(th);
    }

}

void XThreadPool::Run() {
    cout << "begin Xthread pool Run " << this_thread::get_id << endl;
    while (true) {
        auto task = GetTask();
        if (!task) continue;
        try {
            task->Run();
        } catch (...) {

        }
    }


    cout << "end Xthread pool Run " << this_thread::get_id << endl;
}

void XThreadPool::AddTask(XTask *task) {
    unique_lock<mutex> lock(mux_);
    tasks_.push_back(task);
    lock.unlock();
    cv_.notify_one();
}

XTask *XThreadPool::GetTask() {
    unique_lock<mutex> lock(mux_);
    if (tasks_.empty()) {
        cv_.wait(lock);
    }
    if (tasks_.empty()) {
        return nullptr;
    }
    auto task = tasks_.front();
    tasks_.pop_front();
    return task;
}
