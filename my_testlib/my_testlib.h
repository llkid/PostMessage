#ifndef MY_TESTLIB_H
#define MY_TESTLIB_H

#include "my_testlib_global.h"

#include <QObject>

#include <functional>

class /*MY_TESTLIB_EXPORT*/ My_testlib : public QObject
{
    Q_OBJECT
public:
    My_testlib();

    static void execOnMainThread(std::function<void()>&& f);
    static void execOnMainThreadSync(std::function<void()>&& f);

signals:
    void comming(std::function<void()> f);
    void commingSync(std::function<void()> f);

private slots:
    void exec(std::function<void()> f);
    void execSync(std::function<void()> f);

private:
    void* m_id;

    bool isOnMainThread();
};

extern "C"  {
    bool MY_TESTLIB_EXPORT CreateLib();
    void MY_TESTLIB_EXPORT ReleaseLib();
    void MY_TESTLIB_EXPORT PostTask(void(* f)());
    void MY_TESTLIB_EXPORT ExecTask(void(* f)());
}

#endif // MY_TESTLIB_H
