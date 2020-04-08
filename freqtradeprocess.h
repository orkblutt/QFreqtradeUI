#ifndef FREQTRADEPROCESS_H
#define FREQTRADEPROCESS_H

#include <QObject>
#include <QProcess>


class freqtradeProcess : public QObject
{
    Q_OBJECT
public:
    explicit freqtradeProcess(QObject *parent = nullptr);

    void start(const QString& cmdLine);
    void stop();

    bool isRunning(){return _started;};

private:
    QProcess _freqTradeProcess;
    bool _started = false;

    qint64 _pid = 0;

private slots:

    void onReadyToReadStdout();
    void onReadyToReadStderr();

    void onExit();
    void onStarted();

signals:

    void startedSignal();
    void stopedSignal();

    void outputSignal(const QString& msg);
};

#endif // FREQTRADEPROCESS_H
