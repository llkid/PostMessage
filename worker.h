#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    class Delegate {
    public:
        virtual void test1()=0;
        virtual void test2()=0;

    protected:
        ~Delegate() = default;
    };

    explicit Worker(Delegate* delegate);

    Delegate* delegate() { return delegate_; }
    void DetachDegelate();

    void test1();
    void test2();

protected:
    Worker();

private:
    Delegate* delegate_;
};

#endif // WORKER_H
