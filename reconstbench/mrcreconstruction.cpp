#include "mrcreconstruction.h"

#include <iostream>
#include <string>

#include "ctk/ctkimage.h"
#include "ctk/ctkpoint.h"

#include "ctk/utils/filesys/filesystem.h"

#include "uniqode/auxiliar/dictaux.h"
#include "uniqode/gc/halftonegc.h"
#include "uniqode/auxiliar/auxiliar.h"
#include "uniqode/auxiliar/reconstaux.h"
#include "uniqode/gc/dictionary.h"
#include "uniqode/gc/decoding.h"
#include "utils/qtjsonfs/jsonspec.h"

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
    std::string msg;
    ctk::RgbImage sf;
    sf.Open(filename);
    ctk::BinaryMatrix result = sf.toGrayImage().ApplyOtsuThreshold();
    ctk::Contours contours;
    contours.CalculateApproximateContours(result);
    contours.Draw(sf).Save("conts.png");
    ctk::BinaryMatrix rect = Rectify(sf, contours);
    rect.Save("rect.png");
    ctk::BinaryMatrix reconst = Reconstruct(rect);
    reconst.Save("reconst.png");
    //
    msg = Decode(reconst);
    //
    m_out = QString::fromStdString(msg);
}

ctk::BinaryMatrix GcCpRs::Rectify(ctk::RgbImage &photo,
                                  ctk::Contours &contours)
{
    if(contours.size()>0){
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
    }else{
        std::exception e;
        throw  e;
    }
}

ctk::BinaryMatrix GcCpRs::Reconstruct(ctk::BinaryMatrix &bin)
{
    ctk::BinaryMatrix reconst;
    reconst.Create(36, 36);
    for (int x=0; x<36; x++) {
        int xx = 5 + x*10;
        for (int y=0; y<36; y++) {
            int yy = 5 + y*10;
            reconst.set(x, y, bin.get(xx,yy));
        }
    }
    return reconst;
}

std::string GcCpRs::Decode(ctk::BinaryMatrix &reconst)
{
    if(reconst.width()>0){
        const std::string kDictionary = "../../Data/dict.json";
        const int kDictID = 1001;
        Dictionary dict = readDictionary(kDictID,kDictionary);
        //
        HalftoneGC halftone;
        halftone.read(reconst.get_data(), SCAN_ORDER, 3, 3, SCAN_ORDER);
        std::vector< std::vector<std::string> > msgs;
        std::vector<GeGrid> &grids = halftone.grids();

        for (unsigned int i=0; i<grids.size(); i++) {
            msgs.push_back(( decodify(grids[i].cells(), dict) ));
        }

        if(msgs[0].size() > 0){
            std::string msg_final = vector2compactstring(msgs[0]);
            std::string msg;
            if(verifyCheckDigit(msgs[0],dict.alphabet(),3)){
                msg = removeCheckDigit(msg_final,3);
            }else{
                std::exception e; //TODO: improve it
                throw e;
            }
            return msg;
        }else{
            std::exception e; //TODO: improve it
            throw e;
        }
    }else{
        std::exception e; //TODO: improve it
        throw e;
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
