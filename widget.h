#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "worker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Form; }
QT_END_NAMESPACE

class QTextEdit;
class QPushButton;
class Widget : public QWidget, public Worker::Delegate
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void Init();

    static Widget* GetInstance();

    Q_INVOKABLE virtual
    void test1() override;
    Q_INVOKABLE virtual
    void test2(int num) override;
    Q_INVOKABLE virtual
    void Add(int num1, int num2) override;
    Q_INVOKABLE virtual
    void test3(data_info info) override;

private:
    Ui::Form* ui_;
    QWidget* other_window_;

    QThread* thread_;
    Worker worker_;

    QTextEdit* tEdit_;
    QPushButton* pBtn_;
    Qt::HANDLE current_thread_id_;

    Q_DISABLE_COPY_MOVE(Widget);
};
#endif // WIDGET_H
