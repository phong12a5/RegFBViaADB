#include "ADBCommand.h"

ADBCommand* ADBCommand::m_instance = nullptr;

ADBCommand::ADBCommand(QObject *parent) : QObject(parent)
{

}

ADBCommand *ADBCommand::instance()
{
    if(!m_instance) {
        m_instance = new ADBCommand();
    }
    return m_instance;
}

QString ADBCommand::screenShot(QString fileName, QString path)
{
    LOG << "Path: " << path  << " --- FileName: " << fileName;
    QProcess proc;
    proc.start(QString("adb shell screencap -p %1screen.png").arg(IMAGE_FOLDER));
    proc.waitForFinished(-1);
    proc.start(QString("adb pull %1screen.png %2").arg(IMAGE_FOLDER).arg(path));
    proc.waitForFinished(-1);
    return path + "/" + fileName;
}

void ADBCommand::swipeScreen(QPoint sourcePoint, QPoint desPoint)
{
    LOG << "Swiping from " << sourcePoint << " to" << desPoint;
    QProcess proc;
    proc.start(QString("adb shell input swipe %1 %2 %3 %4")\
               .arg(sourcePoint.x())\
               .arg(sourcePoint.y())\
               .arg(desPoint.x())\
               .arg(desPoint.y()));
    proc.waitForFinished(-1);
    return;
}

bool ADBCommand::requestShowApp(QString packageName, QString activity)
{
    LOG << "packageName: " << packageName << " --- activity: " << activity;
    QProcess proc;
    proc.start(QString("adb shell am start -n %1/%2").arg(packageName).arg(activity));
    proc.waitForFinished(-1);
    if(proc.readAllStandardError() != ""){
        LOG << "ERROR: " << proc.readAllStandardError();
        return false;
    }else {
        return true;
    }
}

bool ADBCommand::goHomeScreen()
{
    LOG;
    this->killSpecificApp(SETTING_PKG);
    QProcess proc;
    proc.start(QString("adb shell input keyevent KEYCODE_HOME"));
    proc.waitForFinished(-1);
    delay(100);
    if(proc.readAllStandardError() != ""){
        LOG << "ERROR: " << proc.readAllStandardError();
        return false;
    }else {
        return true;
    }
}

bool ADBCommand::requestShowAppDirectly(QString activity)
{
    LOG << "acivity: " << activity;
    QProcess proc;
    proc.start(QString("adb shell am start -a %1").arg(activity));
    proc.waitForFinished(-1);
    if(proc.readAllStandardError() != ""){
        LOG << "ERROR: " << proc.readAllStandardError();
        return false;
    }else {
        return true;
    }
}

bool ADBCommand::enterText(QString text)
{
    LOG << "Entering text: " << text;
    QProcess proc;
    proc.start(QString("adb shell input text %1").arg(text));
    proc.waitForFinished(-1);
    if(proc.readAllStandardError() != ""){
        LOG << "ERROR: " << proc.readAllStandardError();
        return false;
    }else {
        return true;
    }
}

bool ADBCommand::pressTap()
{
    LOG << "Pressing Tap Key ...";
    QProcess proc;
    proc.start(QString("adb shell input keyevent KEYCODE_TAB"));
    proc.waitForFinished(-1);
    if(proc.readAllStandardError() != ""){
        LOG << "ERROR: " << proc.readAllStandardError();
        return false;
    }else {
        return true;
    }
}

bool ADBCommand::rebootDevice()
{
    LOG;
    QProcess proc;
    proc.start(QString("adb shell reboot"));
    proc.waitForFinished(-1);
    if(proc.readAllStandardError() != ""){
        LOG << "ERROR: " << proc.readAllStandardError();
        return false;
    }else {
        return true;
    }
}

bool ADBCommand::checkConnection()
{
    QProcess proc;
    proc.start(QString("adb devices"));
    proc.waitForFinished(-1);
    if(proc.readAllStandardError() != ""){
        LOG << "ERROR: " << proc.readAllStandardError();
        return false;
    }else {
        QString output = proc.readAllStandardOutput();
        output.remove("List of devices attached");
        output.remove("device");
        output.remove("\r");
        output.remove("\n");
        output.remove("\t");
        output.remove(" ");
        delay(200);
        if(output != ""){
            LOG << "Devices: " << output;
            return true;
        }else {
            LOG << "There is no device is connected!";
            return false;
        }
    }
}

bool ADBCommand::customCommand(QString cmd)
{
    LOG << "Cmd: " << cmd;
    bool retVal = true;
    return retVal;
}

QString ADBCommand::currentActivity()
{
    QString retVal = "";

    // check the screen is onScreen


    if(this->checkConnection()){
        QProcess proc;

        proc.start(" adb shell dumpsys input_method | grep mScreenOn");
        proc.waitForFinished(-1);

        if(QString(proc.readAllStandardOutput()).contains("mScreenOn=false")){
            this->wakeUpScreen();
        }

        proc.start("adb shell dumpsys window windows | grep -E 'mFocusedApp'");
        proc.waitForFinished(-1);
        QStringList output = QString(proc.readAllStandardOutput()).split(' ');
        if(output.length() > 6){
            retVal = output.at(6);
        }
    }
    LOG << retVal;
    delay(200);
    return retVal;
}

void ADBCommand::killSpecificApp(QString packageName)
{
    LOG << "Killing " << packageName;
    QProcess proc;
    proc.start(QString("adb shell am force-stop %1").arg(packageName));
    proc.waitForFinished(-1);
    delay(100);
    return;
}

void ADBCommand::wakeUpScreen()
{
    LOG;
    QProcess proc;
    proc.start("adb shell input keyevent KEYCODE_POWER");
    proc.waitForFinished(-1);
    delay(200);
    return;
}

void ADBCommand::tapScreen(QPoint point)
{
    LOG << "Tapping at [" << point.x() << "," << point.y() << "]";
    QProcess proc;
    proc.start(QString("adb shell input tap %1 %2").arg(point.x()).arg(point.y()));
    proc.waitForFinished(-1);
    delay(100);
    return;
}
