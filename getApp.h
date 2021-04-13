#ifndef GETAPP_H
#define GETAPP_H

#endif // GETAPP_H
#include <QtCore>
#include <sys/types.h>
#include <unistd.h>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusReply>
#include <QDBusObjectPath>
#include <QSettings>


class UkuiMenuInterface
{
private:
    QStringList filePathList;
    QSettings* setting=nullptr;

protected:
    void recursiveSearchFile(const QString& _filePath);//遍历/usr/share/applications/文件夹
    QStringList getSpecifiedCategoryAppList(QString categorystr);//获取指定类型应用列表

public:
    UkuiMenuInterface();
    ~UkuiMenuInterface();
    QVector<QStringList> createAppInfoVector();//创建应用信息容器
    static QVector<QStringList> appInfoVector;
    static QVector<QString> desktopfpVector;
    static QVector<QStringList> alphabeticVector;
    static QVector<QStringList> functionalVector;
    static QVector<QString> allAppVector;
    static QStringList androidDesktopfnList;

    /**
     * 获取系统应用名称
     * @param desktopfp 为应用.desktop文件所在路径
     * @return 返回应用名称
     */
    QString getAppName(QString desktopfp);//获取应用名
    QString getAppEnglishName(QString desktopfp);//获取英语英文名
    QString getAppIcon(QString desktopfp);//获取应用图像
    QString getAppCategories(QString desktopfp);//获取应用分类
    QString getAppExec(QString desktopfp);//获取应用命令
    QString getAppType(QString desktopfp);//获取应用类型
    QString getAppComment(QString desktopfp);//获取应用注释
    QStringList getDesktopFilePath();//获取系统deskyop文件路径

    QVector<QStringList> getAlphabeticClassification();//字母分类模块
    QVector<QStringList> getFunctionalClassification();//功能分类模块
    QVector<QString> getCommonUseApp();//获取常用App
    QVector<QString> getAllClassification();//所有软件模块
    void getAndroidApp();//获取安卓应用
    static bool cmpApp(QStringList &arg_1,QStringList &arg_2);
    bool matchingAppCategories(QString desktopfp,QStringList categorylist);//匹配应用Categories
    QString getAppNameInitials(QString desktopfp);//获取应用名所有首字母
    QString getAppNameInitial(QString desktopfp);//获取应用名所有首字母
    QString getAppNamePinyin(QString appname);//获取应用名拼音

    //获取用户图像
    QString getUserIcon();
    //获取用户姓名
    QString getUserName();

};
