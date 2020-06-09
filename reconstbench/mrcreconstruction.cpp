#include "mrcreconstruction.h"

#include <iostream>
#include <string>

#include "uniqode/auxiliar/dictaux.h"

#include "ctk/ctkimage.h"
#include "ctk/ctkpoint.h"

#include "ctk/utils/filesys/filesystem.h"

//
// Graphic Code - Cellphone - Regular Sampling
//
GcCpRs::GcCpRs()
    : BenchmarkEvaluation()
{

}

QString GcCpRs::name()
{
    return "GcCphoneRegSmp";
}

void GcCpRs::Eval(QStringList args)
{
    std::string filename = args[0].toStdString();
    std::cout << filename << std::endl;
    //
    std::string msg = "Oi"; // decoded message
    // TODO: reconstruction method
    //
    // ... .. ...
    //
    ctk::RgbImage sf;
    sf.Open(filename);
    ctk::BinaryMatrix result = sf.toGrayImage().ApplyOtsuThreshold();
    ctk::Contours contours;
    contours.CalculateApproximateContours(result);
    contours.Draw(sf).Save("conts.png");
    ctk::BinaryMatrix rect = Rectify(sf, contours);
    rect.Save("rect.png");
    //
    m_out = QString::fromStdString(msg);
}

ctk::BinaryMatrix GcCpRs::Rectify(ctk::RgbImage &photo,
                                  ctk::Contours &contours)
{
    if(contours.size()>0){
        if(contours.size() > 0){
            ctk::Contours boxes = contours.OrientedBoundingBoxes();
            ctk::Polygon& cont = boxes.polygon(3);
            std::vector<ctk::PointD> &pts = cont.get_data();
            std::vector<ctk::PointD> refs;
            refs.resize(4);
            refs[0] = ctk::PointD(0,0);
            refs[1] = ctk::PointD(360,0);
            refs[2] = ctk::PointD(360,360);
            refs[3] = ctk::PointD(0,360);
            ctk::RgbImage rect = photo.Warp(pts, refs, 360, 360);
            ctk::BinaryMatrix rectBin = rect.toGrayImage().ApplyOtsuThreshold();
            if (rectBin.get(105,105)==0) {
                return rectBin;
            }
            if (rectBin.get(255,105)==0) {
                ctk::RgbImage rot =  rect.Rotate270();
                return rot.toGrayImage().ApplyOtsuThreshold();
            }
            if (rectBin.get(255,255)==0) {
                ctk::RgbImage rot =  rect.Rotate180();
                return rot.toGrayImage().ApplyOtsuThreshold();
            }
            ctk::RgbImage rot =  rect.Rotate90();
            return rot.toGrayImage().ApplyOtsuThreshold();
        }
    }else{
        std::exception e;
        throw  e;
    }
}


//
// Graphic Code - Square frame - Regular Sampling
//
GcSfRs::GcSfRs()
    : BenchmarkEvaluation()
{

}

QString GcSfRs::name()
{
    return "GcSqFrRegSmp";
}

void GcSfRs::Eval(QStringList args)
{
    std::string filename = args[0].toStdString();
    std::string msg = "Oi"; // decoded message
    //
    // TODO: reconstruction method
    //
    // ... .. ...
    //
    m_out = QString::fromStdString(msg);
}

//
// QR Code - Reading
//
QrReading::QrReading()
    : BenchmarkEvaluation()
{

}

QString QrReading::name()
{
    return "QrReading";
}

void QrReading::Eval(QStringList args)
{
    std::string filename = args[0].toStdString();
    std::string msg = "Oi"; // decoded message
    //
    // TODO: reconstruction method
    //
    // ... .. ...
    //
    m_out = QString::fromStdString(msg);
}

//
// Data Matrix - Reading
//
DmReading::DmReading()
    : BenchmarkEvaluation()
{

}

QString DmReading::name()
{
    return "DmReading";
}

void DmReading::Eval(QStringList args)
{
    std::string filename = args[0].toStdString();
    std::string msg = "Oi"; // decoded message
    //
    // TODO: reconstruction method
    //
    // ... .. ...
    //
    m_out = QString::fromStdString(msg);
}
