#include "createmrcsetup.h"

#include <QDebug>
#include <QString>
#include <QMap>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "ctk/utils/filesys/filesystem.h"

void createSfSetupFiles()
{
    QString dirdb = "../../theblackeyedpixels/data/10";
    QVector<QString> suffixes = {"png"};
    QVector<QString> files = createFileListRecursively(dirdb, suffixes);
    QVector<QPair<QString, QString>> sfdata;
    for (auto &f: files) {
        QString fn = f;
        f.remove(0, 63);
        QString msg = f.split("/")[0];
        f.remove(0, 6);
        if (f.split("/")[0]=="sf") {
            sfdata.append( qMakePair(fn,msg) );
        }
    }
    //
    QString filename = "../../theblackeyedpixels/setup/10-sf.txt";
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << "{\n";
        out << "\t\"comparison\": \"STRING_EQUALS\",\n";
        out << "\t\"inputs\": [\n";
        for (auto i=0; i<sfdata.size(); i++) {
            out << "\t\t\"" << sfdata[i].first;
            if (i<sfdata.size()-1) {
                out << "\",\n";
            }
            else out << "\"\n";
        }

        out << "\t],\n";
        out << "\t\"output\": [\n";
        for (auto i=0; i<sfdata.size(); i++) {
            out << "\t\t\"abcde12345\"";
            if (i<sfdata.size()-1) {
                out << ",\n";
            }
            else out << "\n";
        }
        out << "\t]\n";
        out << "}";
    }
    file.close();
}

void createCpSetupFiles()
{
    QString dirdb = "../../theblackeyedpixels/data/10";
    QVector<QString> suffixes = {"png"};
    QVector<QString> files = createFileListRecursively(dirdb, suffixes);
    QVector<QPair<QString, QString>> sfdata;
    for (auto &f: files) {
        QString fn = f;
        f.remove(0, 63);
        QString msg = f.split("/")[0];
        f.remove(0, 6);
        if (f.split("/")[0]=="cp") {
            sfdata.append( qMakePair(fn,msg) );
        }
    }
    //
    QString filename = "../../theblackeyedpixels/setup/10-cp.txt";
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << "{\n";
        out << "\t\"comparison\": \"STRING_EQUALS\",\n";
        out << "\t\"inputs\": [\n";
        for (auto i=0; i<sfdata.size(); i++) {
            out << "\t\t\"" << sfdata[i].first;
            if (i<sfdata.size()-1) {
                out << "\",\n";
            }
            else out << "\"\n";
        }

        out << "\t],\n";
        out << "\t\"output\": [\n";
        for (auto i=0; i<sfdata.size(); i++) {
            out << "\t\t\"abcde12345\"";
            if (i<sfdata.size()-1) {
                out << ",\n";
            }
            else out << "\n";
        }
        out << "\t]\n";
        out << "}";
    }
    file.close();
}

//void createSfSetupFiles()
//{
//    QString dirdb = "../../theblackeyedpixels/data/10";
//    QVector<QString> suffixes = {"png"};
//    QVector<QString> files = createFileListRecursively(dirdb, suffixes);
//    QMap<QString, QVector<QPair<QString, QString>>> datasets;
//    for (auto &f: files) {
//        QString fn = f;
//        f.remove(0, 63);
//        QString msg = f.split("/")[0];
//        f.remove(0, 6);
//        if (f.split("/")[0]=="sf") {
//            datasets[f.split("/")[0]].append( qMakePair(fn,msg) );
//        }
//    }
//    //
//    QString filename = "../../theblackeyedpixels/setup/10.txt";
//    QFile file(filename);
//    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
//    {
//        QTextStream out(&file);
//        out << "{\n";
//        out << "\t\"comparison\": \"STRING_EQUALS\",\n";
//        out << "\t\"inputs\": [\n";
//        for (auto it=datasets.begin(); it!=datasets.end(); ++it) {
//            QVector<QPair<QString, QString>> &set = it.value();
//            for (auto i=0; i<set.size(); i++) {
//                out << "\t\t\"" << set[i].first;
//                if ((it!=datasets.end()-1) || (i!=set.size()-1)) {
//                    out << "\",\n";
//                }
//                else out << "\"\n";
//            }
//        }
//        out << "\t],\n";
//        out << "\t\"output\": [\n";
//        for (auto it=datasets.begin(); it!=datasets.end(); ++it) {
//            QVector<QPair<QString, QString>> &set = it.value();
//            for (auto i=0; i<set.size(); i++) {
//                out << "\t\t\"abcde12345\"";
//                if ((it!=datasets.end()-1) || (i!=set.size()-1)) {
//                    out << ",\n";
//                }
//                else out << "\n";
//            }
//        }
//        out << "\t]\n";
//        out << "}";
//    }
//    file.close();
//}


void createSetupFiles()
{
    QString dirdb = "../../theblackeyedpixels/data/10";
    QVector<QString> suffixes = {"png"};
    QVector<QString> files = createFileListRecursively(dirdb, suffixes);
    QMap<QString, QVector<QPair<QString, QString>>> datasets;
    for (auto &f: files) {
        QString fn = f;
        f.remove(0, 63);
        QString msg = f.split("/")[0];
        qDebug() << f << msg;
        f.remove(0, 6);
        datasets[f.split("/")[0]].append( qMakePair(fn,msg) );
    }
    //
    for (auto it=datasets.begin(); it!=datasets.end(); ++it) {
        qDebug() << it.key() << it.value().size();
        QVector<QPair<QString, QString>> &set = it.value();
        for (auto &p: set) {
            qDebug() << it.key() << p.first << p.second;
        }
    }
    //
    QString filename = "../../theblackeyedpixels/setup/10.txt";
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << "{\n";
//        out << "\t\"programs\": [\n";
//        out << "\t\t\"../prog1/prog1\"\n";
//        out << "\t],\n";
        out << "\t\"comparison\": \"STRING_EQUALS\",\n";
        out << "\t\"inputs\": [\n";
        for (auto it=datasets.begin(); it!=datasets.end(); ++it) {
            qDebug() << it.key() << it.value().size();
            QVector<QPair<QString, QString>> &set = it.value();
            for (auto i=0; i<set.size(); i++) {
                qDebug() << it.key() << (it!=datasets.end()-1) << i << set.size();
                out << "\t\t\"" << set[i].first;
                if ((it!=datasets.end()-1) || (i!=set.size()-1)) {
                    out << "\",\n";
                }
                else out << "\"\n";
            }
        }
        out << "\t],\n";
        out << "\t\"output\": [\n";
        for (auto it=datasets.begin(); it!=datasets.end(); ++it) {
            qDebug() << it.key() << it.value().size();
            QVector<QPair<QString, QString>> &set = it.value();
            for (auto i=0; i<set.size(); i++) {
                out << "\t\t\"" << set[i].second;
                if ((it!=datasets.end()-1) || (i!=set.size()-1)) {
                    out << "\",\n";
                }
                else out << "\"\n";
            }
        }
        out << "\t]\n";
        out << "}";
    }
    file.close();
}
