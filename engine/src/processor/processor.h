/*
 * processor.h
 *
 *  Created on: Jan 4, 2016
 *      Author: chenzhen
 */

#ifndef PROCESSOR_H_
#define PROCESSOR_H_
#include <sys/file.h>
#include <atomic>
#include <sys/time.h>
#include "model/basic.h"
#include "model/model.h"
#include "model/frame.h"
#include "log/log_val.h"
#include "debug_util.h"


namespace dg {

/// The basic processor interface. It defines the
/// interfaces each derived processor must to implement.
const int RECORD_UNIT = 1000;
class Processor {
 public:
    Processor()
        : next_(0), performance_(0) {

    }
    virtual ~Processor() {
        if (next_)
            delete next_;
        next_ = NULL;
    }

    Processor *SetNextProcessor(Processor *proc) {
        DLOG(INFO) << "set next processor" << endl;
        Processor *old = next_;
        next_ = proc;
        return old;
    }

    Processor *GetNextProcessor() {
        return next_;
    }

/// Update the input Frame.
    virtual void Update(Frame *frame) {
        if (beforeUpdate(frame)) {
            gettimeofday(&start_ts_, NULL);
            process(frame);
            gettimeofday(&end_ts_, NULL);
            printProcessorCost();
        }
        processNext(frame);
    }

/// Update the input FrameBatch.
/// A FrameBatch is a package of one or more Frame.
    virtual void Update(FrameBatch *frameBatch) {
        if (beforeUpdate(frameBatch)) {
            gettimeofday(&start_ts_, NULL);
            process(frameBatch);
            gettimeofday(&end_ts_, NULL);
            printProcessorCost();
        }
        processNext(frameBatch);
    }

 protected:
    /// The interfaces derived class must to implement
    virtual bool beforeUpdate(Frame *frame) { return true; }
    virtual bool beforeUpdate(FrameBatch *frameBatch) { return true; };

    virtual bool process(Frame *frame) = 0;
    virtual bool process(FrameBatch *frame) = 0;

    virtual bool checkStatus(Frame *frame) { return true; };
    virtual bool checkStatus(FrameBatch *frameBatch) { return true; };


 private:
/// This method will invoke the next processor chained to the
/// current processor.
/// Each processor must invoke Proceed to drive the engine running.
    void processNext(Frame *frame) {
        if (next_ != NULL) {
            next_->Update(frame);
        }
    }
/// This method will invoke the next processor chained to the
/// current processor.
/// Each processor must invoke Proceed to drive the engine running.
    void processNext(FrameBatch *frameBatch) {
        if (next_ != NULL) {
            next_->Update(frameBatch);
        }
    }
    virtual bool RecordFeaturePerformance() = 0;
    virtual string processorName() = 0;

    inline void printProcessorCost() {
        VLOG(VLOG_PROCESS_COST)
        << "Processor " << processorName() << " cost " << TimeCostInMs(start_ts_, end_ts_) << "ms" << endl;
    }

 protected:
    Processor *next_;
    unsigned long long performance_;
    struct timeval start_ts_;
    struct timeval end_ts_;
};
}
#endif /* PROCESSOR_H_ */
