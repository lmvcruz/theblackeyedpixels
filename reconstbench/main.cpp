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
//    engine.Read("../../theblackeyedpixels/setup/10-sf.txt");
    QVector<QString> suffixes = {"png"};
    QVector<QString> files = createFileListRecursively("../../theblackeyedpixels/data/10/abcde/sf/", suffixes);
    QStringList args = {files[3], "1"};
    engine.add_instance(args, "abcde12345");
    //
    BenchmarkProgram *progQty = new StringEqualsCompProg(new GcSfRs);
    engine.add_program(progQty);
    engine.ValidateAll();
}


void testCp()
{
    BenchmarkEngine engine;
    engine.Read("../../theblackeyedpixels/setup/10-cp.txt");
//    engine.add_instance("../../theblackeyedpixels/data/10/abcde/cp/IMG_2596_cp.png 1", "abcde12345");
    //
    BenchmarkProgram *progQty = new StringEqualsCompProg(new GcCpRs);
    engine.add_program(progQty);
    engine.ValidateAll();
}

void FullEval()
{
    QString basename = "../../theblackeyedpixels/setup/10-";
    //
    BenchmarkEngine engSf;
    engSf.Read(basename+"sf.txt");
    BenchmarkProgram *sfProg = new StringEqualsCompProg(new GcSfRs);
    engSf.add_program(sfProg);
    qDebug() << engSf.ValidationRate(0);
    //
    BenchmarkEngine engCp;
    engCp.Read(basename+"cp.txt");
    BenchmarkProgram *cpProg = new StringEqualsCompProg(new GcCpRs);
    engCp.add_program(cpProg);
    qDebug() << engCp.ValidationRate(0);
    //
    BenchmarkEngine engQr;
    engQr.Read(basename+"qr.txt");
    BenchmarkProgram *qrProg = new StringEqualsCompProg(new QrReading);
    engQr.add_program(qrProg);
    qDebug() << engQr.ValidationRate(0);
    //
    BenchmarkEngine engDm;
    engDm.Read(basename+"dm.txt");
    BenchmarkProgram *dmProg = new StringEqualsCompProg(new DmReading);
    engDm.add_program(dmProg);
    qDebug() << engDm.ValidationRate(0);
}

int main(int argc, char *argv[])
{
//    createSetupFile("sf");
//    createSetupFile("cp");
//    createSetupFile("qr");
//    createSetupFile("dm");
    //
    testSf();
//    testCp();
//    FullEval();
    //
    return 0;
}
