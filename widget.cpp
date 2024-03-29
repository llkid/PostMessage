#include "widget.h"
#include "./ui_Widget.h"

#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QThread>
#include <QDebug>
#include <QtConcurrent>
#include <QMetaObject>

Q_GLOBAL_STATIC(Widget, g_instance);

#define CHECK_AND_CALL()

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      worker_(this),
      current_thread_id_(QThread::currentThreadId()),
      ui_(new Ui::Form)
{
//    ui_->setupUi(this);
    other_window_ = new QWidget();
    ui_->setupUi(other_window_);

    QVBoxLayout* layout = new QVBoxLayout(this);
    pBtn_ = new QPushButton("测试", this);
    tEdit_ = new QTextEdit(this);
    layout->addWidget(pBtn_);
    layout->addWidget(tEdit_);
    this->setLayout(layout);

    connect(pBtn_, &QPushButton::clicked, [=]{

        QFuture<void> f = QtConcurrent::run([=]{
            qDebug() << __FUNCTION__ << QThread::currentThreadId();

          worker_.test1();
          QThread::currentThread()->sleep(1);
          worker_.test2(QRandomGenerator::global()->bounded(1, 100));
          worker_.Add(1, 2);
          worker_.test3({1, "test3"});
        });
        f.then([]{qDebug() << "Ok.";});
    });
}

Widget::~Widget()
{
    if (thread_) {
        thread_->quit();
        thread_->wait();
        thread_->deleteLater();
    }
    if (other_window_)
        delete other_window_;
    delete ui_;
}

void Widget::Init()
{
    thread_ = new QThread();
    worker_.moveToThread(thread_);
    thread_->start();
    qDebug() << "Main thread id:" << QThread::currentThreadId();

//    other_window_->show();
}

Widget *Widget::GetInstance()
{
    return g_instance();
}

void Widget::test1()
{
    if (current_thread_id_  != QThread::currentThreadId()) {
        return (void)QMetaObject::invokeMethod(this, "test1");
    }
    qDebug() << __FUNCTION__ << QThread::currentThreadId();
    tEdit_->append(__FUNCTION__);
}

void Widget::test2(int num)
{
    if (current_thread_id_  != QThread::currentThreadId()) {
        return (void)QMetaObject::invokeMethod(this, "test2", Q_ARG(int, num));
    }
    qDebug() << __FUNCTION__ << QThread::currentThreadId();
    tEdit_->append(QString("%1:%2").arg(__FUNCTION__).arg(num));
}

void Widget::Add(int num1, int num2)
{
    if (current_thread_id_ != QThread::currentThreadId()) {
        return (void)QMetaObject::invokeMethod(this, "Add", Q_ARG(int, num1), Q_ARG(int, num2));
    }
    qDebug() << __FUNCTION__ << QThread::currentThreadId();
    tEdit_->append(QString("%1+%2=%3").arg(num1).arg(num2).arg(num1+num2));
}

void Widget::test3(data_info info)
{
    qRegisterMetaType<data_info>("data_info");
    if (current_thread_id_ != QThread::currentThreadId()) {
        return (void)QMetaObject::invokeMethod(this, "test3", Qt::QueuedConnection, Q_ARG(data_info, info));
    }
    qDebug() << __FUNCTION__ << QThread::currentThreadId();
    tEdit_->append(QString("id:%1,name:%2").arg(info.id).arg(info.name));
}

