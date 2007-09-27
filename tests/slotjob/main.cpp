#include <QApplication>
#include <QDebug>
#include <QThread>
class Q43Thread : public QThread{public:void run(){exec();}}; /// qt < 4.3 backwards compatibility

#include <QxtSlotJob>
#include <QxtFuture>


class Bla : public QObject
{
Q_OBJECT
public slots:
    void say(QString a)
    {
        qDebug()<<a;
    }
};

int main(int argc,char **argv)
{
    QApplication app(argc,argv);

    Q43Thread thread;
    thread.start();
    Bla q;
    QxtFuture f= QxtSlotJob::detach(&thread,&q,SLOT(say(QString)),Q_ARG(QString, "hi"));
    qDebug()<<"waiting"<<f.wait(3000);
    thread.quit();
    thread.wait();
    return 0;
}

#include "main.moc"
