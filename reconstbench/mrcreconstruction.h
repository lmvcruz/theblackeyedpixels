#ifndef MRCRECONSTRUCTION_H
#define MRCRECONSTRUCTION_H

#include <QStringList>
#include <QString>

#include "benchlib/benchmarkevaluation.h"
#include "benchlib/benchmarkprogram.h"
#include "benchlib/benchmarkengine.h"

class GcRegularSampling : public BenchmarkEvaluation
{
private:

public:
    GcRegularSampling();

    void eval(QStringList args);
};


#endif // MRCRECONSTRUCTION_H
