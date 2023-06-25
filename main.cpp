#include "widget.h"

#include <QApplication>
#include <QDebug>
#include <QThread>

#include "my_testlib/my_testlib.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(600, 400);
    w.Init();
    w.show();

    {
        if (CreateLib()) {
            std::thread arr_thread[5];
            for (int i =0; i< 5; i++) {
                arr_thread[i] = std::thread([=]{
                    PostTask([]{
                        static int i = 0;
                        qDebug().nospace() << "tester" << i++ << " funtion called";
                    });
                });
            }
            for (int i = 0; i < 5; i++)
                arr_thread[i].join();
            ReleaseLib();
        }
    }

    std::thread arr[5];
    for (int i =0; i< 5; i++) {
        arr[i] = std::thread([=]{
            ExecTask([]{
                static int i = 5;
                qDebug().nospace() << "tester" << i++ << " funtion called";
            });
        });
    }

    int exit_code = a.exec();

    for (int i = 0; i < 5; i++)
        arr[i].join();

    return exit_code;
}
