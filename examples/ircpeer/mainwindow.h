#include <QMainWindow>
#include <QHash>
#include "ircpeer.h"
#include "dialog.h"

class QAction;
class QGridLayout;
class QLineEdit;
class QMenuBar;
class QPushButton;
class QTabWidget;
class QTextBrowser;

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow();
protected:
    bool eventFilter(QObject* obj, QEvent* event);
private slots:
    void lateInit();
    void peerConnected();
    void peerError ( QAbstractSocket::SocketError );
    void receiveMessage(IRCName, QByteArray, QByteArray);
    void receiveNotice(IRCName, QByteArray, QByteArray);
    void receiveAction(IRCName, QByteArray, QByteArray);
    void logMessage(IRCName, QByteArray, QByteArray, QString);
    void send();
    void tabActivated(int index);
    void partCurrentChannel();
signals:
    void sendMessage(IRCName, QByteArray, QByteArray);
private:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QHash <QByteArray,QTextBrowser*> channels;
    IRCPeer irc;
    ConnectDialog condiag;

};

