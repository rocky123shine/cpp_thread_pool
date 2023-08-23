//
// Created by rocky on 2023/8/23.
//

#ifndef THREAD_POOL_XVIDEO_TASK_H
#define THREAD_POOL_XVIDEO_TASK_H


#include "../thread_pool/xthread_pool.h"

class XVideoTask : public XTask {
public:
    std::string in_path;
    std::string out_path;
    int width = 0;
    int height = 0;
private:
    int Run();

};


#endif //THREAD_POOL_XVIDEO_TASK_H
