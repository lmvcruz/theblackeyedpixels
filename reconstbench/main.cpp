#include <QCoreApplication>

#include "createmrcsetup.h"
#include "mrcreconstruction.h"

#include "benchlib/benchmarkevaluation.h"
#include "benchlib/benchmarkprogram.h"
#include "benchlib/benchmarkengine.h"

#include "ctk/utils/filesys/filesystem.h"

void testSf()
{
    BenchmarkEngine engine;
    engine.add_program(new StringEqualsCompProg(new GcSfRs));
    //
#if 1
    QVector<QString> suffixes = {"png"};
    QVector<QString> files = createFileListRecursively("../../theblackeyedpixels/data/10/abcde/sf/", suffixes);
    QStringList args = {files[3], "1"};
    engine.add_instance(args, "abcde12345");
#else
    engine.Read("../../theblackeyedpixels/setup/10-sf.txt");
#endif
    //
    engine.ValidateAll();
}


void testCp()
{
    BenchmarkEngine engine;
    engine.add_program(new StringEqualsCompProg(new GcCpRs));
    //
#if 0
    QVector<QString> suffixes = {"png"};
    QVector<QString> files = createFileListRecursively("../../theblackeyedpixels/data/10/abcde/cp/", suffixes);
    QStringList args = {files[3], "1"};
    engine.add_instance(args, "abcde12345");
#else
    engine.Read("../../theblackeyedpixels/setup/10-cp.txt");
#endif
    //
    engine.ValidateAll();
}

void FullEval()
{
    QString basename = "../../theblackeyedpixels/setup/10-";
    //
    BenchmarkEngine engSf;
    BenchmarkProgram *sfProg = new StringEqualsCompProg(new GcSfRs);
    engSf.add_program(sfProg);
    engSf.Read(basename+"sf.txt");
    qDebug() << engSf.ValidationRate(0);
    //
    BenchmarkEngine engCp;
    BenchmarkProgram *cpProg = new StringEqualsCompProg(new GcCpRs);
    engCp.add_program(cpProg);
    engCp.Read(basename+"cp.txt");
    qDebug() << engCp.ValidationRate(0);
    //
    BenchmarkEngine engQr;
    BenchmarkProgram *qrProg = new StringEqualsCompProg(new QrReading);
    engQr.add_program(qrProg);
    engQr.Read(basename+"qr.txt");
    qDebug() << engQr.ValidationRate(0);
    //
    BenchmarkEngine engDm;
    BenchmarkProgram *dmProg = new StringEqualsCompProg(new DmReading);
    engDm.add_program(dmProg);
    engDm.Read(basename+"dm.txt");
    qDebug() << engDm.ValidationRate(0);
}

int main(int argc, char *argv[])
{
//    createSetupFile("sf");
//    createSetupFile("cp");
//    createSetupFile("qr");
//    createSetupFile("dm");
    //
//    testSf();
//    testCp();
    FullEval();
    //
    return 0;
}
