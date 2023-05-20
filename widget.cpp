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
          worker_.test2();
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

void Widget::test2()
{
    if (current_thread_id_  != QThread::currentThreadId()) {
        return (void)QMetaObject::invokeMethod(this, "test2");
    }
    qDebug() << __FUNCTION__ << QThread::currentThreadId();
    tEdit_->append(__FUNCTION__);
}

