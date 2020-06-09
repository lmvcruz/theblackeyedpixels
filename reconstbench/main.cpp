#include <QCoreApplication>

#include "createmrcsetup.h"
#include "mrcreconstruction.h"

#include "benchlib/benchmarkevaluation.h"
#include "benchlib/benchmarkprogram.h"
#include "benchlib/benchmarkengine.h"

void ReconstructGcRegularSamplingFromJson()
{
    QString filename = "../../theblackeyedpixels/setup/10.txt";
    //
    BenchmarkEngine engine;
    engine.Read(filename);
    //
    BenchmarkProgram *progQty = new StringEqualsCompProg(new GcCpRs);
    engine.add_program(progQty);
    engine.ValidateAll();
}

void test()
{
    BenchmarkEngine engine;
//    engine.Read(filename);
    engine.add_instance("../../theblackeyedpixels/data/10/abcde/sf/IMG_2603_qr.png", "");
    //
    BenchmarkProgram *progQty = new StringEqualsCompProg(new GcCpRs);
    engine.add_program(progQty);
    engine.ValidateAll();
}

int main(int argc, char *argv[])
{
//    createSetupFiles();
//    ReconstructGcRegularSamplingFromJson();
    test();
    //
    return 0;
}
