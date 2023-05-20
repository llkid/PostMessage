#include "worker.h"

Worker::Worker(Delegate *delegate) :  delegate_(delegate)
{
}

void Worker::DetachDegelate()
{
    if (delegate_)
        delegate_ = nullptr;
}

void Worker::test1()
{
    if (delegate_)
        delegate_->test1();
}

void Worker::test2(int num)
{
    if (delegate_)
        delegate_->test2(num);
}

void Worker::Add(int num1, int num2)
{
    if (delegate_)
        delegate_->Add(num1, num2);
}

void Worker::test3(data_info info)
{
    if (delegate_)
        delegate_->test3(info);
}
