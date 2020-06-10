#ifndef MRCRECONSTRUCTION_H
#define MRCRECONSTRUCTION_H

#include <QStringList>
#include <QString>

#include "ctk/ctkcontours.h"

#include "benchlib/benchmarkevaluation.h"
#include "benchlib/benchmarkprogram.h"
#include "benchlib/benchmarkengine.h"

//
// Graphic Code - Cellphone - Regular Sampling
//
class GcCpRs : public BenchmarkEvaluation
{
private:

public:
    GcCpRs();

    QString name();

    void Eval(QStringList args);

private:
    ctk::BinaryMatrix Rectify(ctk::RgbImage &photo, ctk::Contours &contours);
    ctk::BinaryMatrix Reconstruct(ctk::BinaryMatrix &bin);
    std::string Decode(ctk::BinaryMatrix &reconst);
};


//
// Graphic Code - Square frame - Regular Sampling
//
class GcSfRs : public BenchmarkEvaluation
{
private:

public:
    GcSfRs();

    QString name();

    void Eval(QStringList args);
};


//
// QR Code - Reading
//
class QrReading : public BenchmarkEvaluation
{
private:

public:
    QrReading();

    QString name();

    void Eval(QStringList args);
};


//
// Data Matrix - Reading
//
class DmReading : public BenchmarkEvaluation
{
private:

public:
    DmReading();

    QString name();

    void Eval(QStringList args);
};


#endif // MRCRECONSTRUCTION_H
