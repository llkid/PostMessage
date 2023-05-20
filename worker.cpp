#include "worker.h"

#include <QTimer>
#include <QThread>
#include <QDebug>

Worker::Worker(Delegate *delegate) :  delegate_(delegate)
{
//    QTimer::singleShot(3000, [=]{
//        qDebug() << "worker thread id:" << QThread::currentThreadId();
//        this->test1();
//        QThread::currentThread()->sleep(1);
//        this->test2();
//    });
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

void Worker::test2()
{
    if (delegate_)
        delegate_->test2();
}
