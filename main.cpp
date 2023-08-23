#include <iostream>
#include "thread_pool/xthread_pool.h"
#include "xvideo/xvideo_task.h"

int main() {
    XThreadPool pool;
    pool.Init(16);
    pool.Start();
    auto task = std::make_shared<XVideoTask>();
    task->in_path = "test.mp4";
    task->out_path = "640.mp4";
    task->width = 640;
    task->height = 480;
    pool.AddTask(task);
    task->GetReturn();
    return 0;
}
