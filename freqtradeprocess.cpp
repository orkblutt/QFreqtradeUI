#include "freqtradeprocess.h"
#include <QTextStream>
#include <QDebug>

freqtradeProcess::freqtradeProcess(QObject *parent) : QObject(parent)
{
    connect(&_freqTradeProcess, &QProcess::readyReadStandardOutput,
            this, &freqtradeProcess::onReadyToReadStdout);

    connect(&_freqTradeProcess, &QProcess::readyReadStandardError,
            this, &freqtradeProcess::onReadyToReadStderr);

    connect(&_freqTradeProcess, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
            this, &freqtradeProcess::onExit);

    connect (&_freqTradeProcess, &QProcess::started,
             this, &freqtradeProcess::onStarted);

    _freqTradeProcess.setReadChannel(QProcess::StandardOutput);
}

void freqtradeProcess::start(const QString &cmdLine)
{
    _freqTradeProcess.setWorkingDirectory("D:/freqtrade");
    _freqTradeProcess.start(cmdLine);
}

void freqtradeProcess::stop()
{
    _freqTradeProcess.kill();
    _freqTradeProcess.waitForFinished();
}

void freqtradeProcess::onReadyToReadStdout()
{
    QTextStream stream(&_freqTradeProcess);
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        qDebug() << line;

        emit outputSignal(line);
    }

}

#define BOT_HEARTBEAT "INFO - Bot heartbeat. PID="

void freqtradeProcess::onReadyToReadStderr()
{
    QByteArray array = _freqTradeProcess.readAllStandardError();
    QString line(array);
    if(line.length() > 1)
    {
        QStringList list = line.split(QRegExp("\r\n"), QString::SkipEmptyParts);
        for(int i = 0; i < list.size(); i++)
        {
            emit outputSignal(list.at(i).trimmed());
        }
    }
}

void freqtradeProcess::onExit()
{
    _started = false;
    emit stopedSignal();
}

void freqtradeProcess::onStarted()
{
    _started = true;
    emit startedSignal();
}
