#include "my_testlib.h"

#include <QThread>
#include <QDebug>

Q_GLOBAL_STATIC(My_testlib, g_ins_);
static My_testlib& g_ins = *g_ins_;

My_testlib::My_testlib() : m_id(QThread::currentThreadId())
{
    qDebug() << "My_testlib:" << m_id;
    connect(this, &My_testlib::comming, this, &My_testlib::exec, Qt::QueuedConnection);
    connect(this, &My_testlib::commingSync, this, &My_testlib::execSync, Qt::BlockingQueuedConnection);
}

void My_testlib::execOnMainThread(std::function<void ()> &&f)
{
    g_ins.exec(std::move(f));
}

void My_testlib::execOnMainThreadSync(std::function<void ()> &&f)
{
    g_ins.execSync(std::move(f));
}

void My_testlib::exec(std::function<void ()> f)
{
    if (isOnMainThread())
    {
        qDebug() << "Call funtion f on main thread.";
        f();
    }
    else
    {
        qDebug() << "Post task";
        emit comming(f);
    }
}

void My_testlib::execSync(std::function<void ()> f)
{
    if (isOnMainThread())
    {
        qDebug() << "Call funtion f on main thread.";
        f();
    }
    else
    {
        qDebug() << "Wait the task results...";
        emit commingSync(f);
    }
}

bool My_testlib::isOnMainThread()
{
    return (QThread::currentThreadId() == m_id);
}

bool CreateLib()
{
    return true;
}

void ReleaseLib()
{

}

void PostTask(void (*f)())
{
    if (f) {
        g_ins.execOnMainThread(f);
    }
}

void ExecTask(void (*f)())
{
    if (f) {
        g_ins.execOnMainThreadSync(f);
    }
}
