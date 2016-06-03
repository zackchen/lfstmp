//
// Created by chenzhen on 6/2/16.
//

#ifndef PROJECT_ENGINE_POOL_H
#define PROJECT_ENGINE_POOL_H

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include "../model/common.pb.h"

namespace dg {

using namespace std;
using namespace ::dg::model;

class CallData {
public:
    CallData() : finished_(false) {
    }

    MatrixError Wait() {
        std::unique_lock<std::mutex> lock(m_);
        cond_.wait(lock, [this]() { return this->finished_; });
        return result_;
    }


    void Finish() {
        finished_ = true;
        cond_.notify_all();
    }


    void Error(string msg) {
        result_.set_code(-1);
        result_.set_message(msg);
        Finish();
    }

    void Run() {
        result_ = func();
        Finish();
    }


    std::function<MatrixError()> func;
    void *apps;

private:
    volatile bool finished_;
    MatrixError result_;
    std::mutex m_;
    std::condition_variable cond_;

};

template<typename EngineType>
class MatrixEnginesPool {
public:

    MatrixEnginesPool(Config *config) : config_(config) {

    }

    void Run() {
        if (!stop_) {
            LOG(ERROR) << "The engine pool already runing" << endl;
            return;
        }

        int gpuNum = (int) config_->Value("System/GpuNum");
        gpuNum = gpuNum == 0 ? 1 : gpuNum;

        for (int gpuId = 0; gpuId < gpuNum; ++gpuId) {

            config_->AddEntry("System/GpuId", AnyConversion(gpuId));
            int threadNum = (int) config_->Value("System/ThreadsPerGpu");
            threadNum = threadNum == 0 ? 1 : threadNum;

            for (int i = 0; i < threadNum; ++i) {
                string name = "apps_" + to_string(gpuId) + "_" + to_string(i);
                EngineType *engine = new EngineType(config_, name);
                cout << "Start thread: " << name << endl;

                workers_.emplace_back([this, engine] {
                  for (; ;) {
                      CallData *task;
                      {

                          std::unique_lock<std::mutex> lock(queue_mutex_);
                          condition_.wait(lock, [this] {
                            return (this->stop_ || !this->tasks_.empty());
                          });

                          if (this->stop_ || this->tasks_.empty()) {
                              continue;
                          }

                          task = this->tasks_.front();
                          this->tasks_.pop();
                          lock.unlock();
                      }
                      cout << "Process in thread: " << std::this_thread::get_id() << endl;
                      // assign the current engine instance to task
                      task->apps = (void *) engine;
                      // task first binds the engine instance to the specific member methods
                      // and then invoke the binded function
                      task->Run();
                      cout << "finish process: " << endl;
                  }
                });
            }

        }

        cout << "Engine pool worker number: " << workers_.size() << endl;
        stop_ = false;
    }

    bool enqueue(CallData *data) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            if (stop_) {
                data->Error("Engine pool not running");
                return false;
            }
            tasks_.push(data);
        }
        condition_.notify_one();
        return true;
    }

private:
    Config *config_;
    queue<CallData *> tasks_;
    vector<std::thread> workers_;
    std::mutex queue_mutex_;
    std::condition_variable condition_;
    bool stop_;

};

}


#endif //PROJECT_ENGINE_POOL_H
