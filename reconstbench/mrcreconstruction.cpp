#include "mrcreconstruction.h"

#include <iostream>
#include <string>

GcRegularSampling::GcRegularSampling()
    : BenchmarkEvaluation()
{

}

void GcRegularSampling::eval(QStringList args)
{
    std::string filename = args[0].toStdString();
    std::string msg; // decoded message
    // TODO: reconstruction method
    //
    // ... .. ...
    //
    std::cout << msg;
}
