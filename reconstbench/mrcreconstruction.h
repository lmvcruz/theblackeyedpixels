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
    ctk::BinaryImage Rectify(ctk::RgbImage &photo, ctk::Contours &contours);
    ctk::BinaryImage RectifyGc(ctk::BinaryImage &rect, ctk::Contours &contours);
    ctk::BinaryImage Reconstruct(ctk::BinaryImage &bin);
    std::string Decode(ctk::BinaryImage &reconst);

    bool debug_mode;
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

private:
    ctk::BinaryImage Rectify(ctk::RgbImage &photo, ctk::Contours &contours);
    ctk::BinaryImage Reconstruct(ctk::BinaryImage &bin);
    std::string Decode(ctk::BinaryImage &reconst);

    bool debug_mode;
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
