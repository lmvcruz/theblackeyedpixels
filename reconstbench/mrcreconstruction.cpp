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
    std::string msg;
    try {
        std::string filename = args[0].toStdString();
        ctk::RgbImage sf;
        sf.Open(filename);
        ctk::BinaryImage result = sf.toGrayImage().ApplyOtsuThreshold();
        ctk::Contours contours;
        contours.CalculateApproximateContours(result);
        ctk::BinaryImage rect = Rectify(sf, contours);
        ctk::Contours seccontours;
        seccontours.CalculateApproximateContours(rect);
        ctk::BinaryImage secrect = RectifyGc(rect, seccontours);
        ctk::BinaryImage reconst = Reconstruct(secrect);
        msg = Decode(reconst);
    } catch (std::exception &e) {
        msg = "FAIL";
    }
    //
    m_out = QString::fromStdString(msg);
}

ctk::BinaryImage GcCpRs::Rectify(ctk::RgbImage &photo,
                                  ctk::Contours &contours)
{
    if(contours.size() > 0){
        ctk::Contours boxes = contours.OrientedBoundingBoxes();
        ctk::Polygon& cont = boxes.polygon(3);
        std::vector<ctk::PointD> &pts = cont.get_data();
        //TODO: replace constants by a parameter
        int h = 900;
        int w = 470;
        std::vector<ctk::PointD> refs = {
            ctk::PointD(0,h),
            ctk::PointD(0,0),
            ctk::PointD(w,0),
            ctk::PointD(w,h)
        };
        ctk::RgbImage rect = photo.Warp(pts, refs, w ,h);
        //TODO: evaluate rotation
        return rect.toGrayImage().ApplyOtsuThreshold();
    }
}

ctk::BinaryImage GcCpRs::RectifyGc(ctk::BinaryImage &rect, ctk::Contours &contours)
{
    if(contours.size() > 0){
        ctk::Contours boxes = contours.OrientedBoundingBoxes();
//        ctk::RgbImage colbin = rect.toRgbImage();
//        for (int i=0; i< contours.size(); i++) {
//            ctk::Polygon& cont = boxes.polygon(i);
//            std::string name = "cont_" + std::to_string(i) + ".png";
//            colbin.DrawPolygon(cont).Save(name);
//        }
        ctk::Polygon& cont = boxes.polygon(10); //TODO: improve choice
        std::vector<ctk::PointD> &pts = cont.get_data();
        if (pts.size()!=4) {
            std::exception e; //TODO: improve it
            throw e;
        }
        //TODO: replace constants by a parameter
        int h = 170;
        int w = 110;
        std::vector<ctk::PointD> refs = {
            ctk::PointD(0,h),
            ctk::PointD(0,0),
            ctk::PointD(w,0),
            ctk::PointD(w,h)
        };
        ctk::BinaryImage rect2 = rect.Warp(pts, refs, w ,h);
        //TODO: evaluate rotation
        return rect2;
    }
}

ctk::BinaryImage GcCpRs::Reconstruct(ctk::BinaryImage &bin)
{
    ctk::BinaryImage reconst;
    //TODO: replace constants by a parameter
    reconst.Create(9, 15);
    int ox = 1;
    int oy = 1;
    for (int x=0; x<9; x++) {
        int xx = 5 + (ox+x)*10;
        for (int y=0; y<15; y++) {
            int yy = 5 + (oy+y)*10;
            reconst.set(x, y, bin.get(xx,yy));
        }
    }
    return reconst;
}

std::string GcCpRs::Decode(ctk::BinaryImage &reconst)
{
    if(reconst.width()>0){
        const std::string kDictionary = "../../theblackeyedpixels/data/dict.json";
        Dictionary dict = readDictionary(1001,kDictionary);
        //
        ctk::RgbImage col = reconst.toRgbImage();
        HalftoneGC halftone;
        halftone.read(col.get_data(), SCAN_ORDER, 3, 3, SCAN_ORDER);
        std::vector< std::vector<std::string> > msgs;
        std::vector<GeGrid> &grids = halftone.grids();
        //
        for (unsigned int i=0; i<grids.size(); i++) {
            msgs.push_back(( decodify(grids[i].cells(), dict) ));
        }
        if ((msgs.size()>0) && (msgs[0].size()>3)) {
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
    std::string msg;
    try {
        std::string filename = args[0].toStdString();
        ctk::RgbImage sf;
        sf.Open(filename);
        ctk::BinaryImage result = sf.toGrayImage().ApplyOtsuThreshold();
        ctk::Contours contours;
        contours.CalculateApproximateContours(result);
        ctk::BinaryImage rect = Rectify(sf, contours);
        ctk::BinaryImage reconst = Reconstruct(rect);
        msg = Decode(reconst);
    } catch (std::exception &e) {
        msg = "FAIL";
    }
    //
    m_out = QString::fromStdString(msg);
}

ctk::BinaryImage GcSfRs::Rectify(ctk::RgbImage &photo, ctk::Contours &contours)
{
    if(contours.size()>0){
        ctk::Contours boxes = contours.OrientedBoundingBoxes();
        ctk::Polygon& cont = boxes.polygon(3);
        std::vector<ctk::PointD> &pts = cont.get_data();
        //TODO: replace constants by a parameter
        std::vector<ctk::PointD> refs = {
            ctk::PointD(0,0),
            ctk::PointD(360,0),
            ctk::PointD(360,360),
            ctk::PointD(0,360)
        };
        ctk::RgbImage rect = photo.Warp(pts, refs, 360, 360);
        ctk::BinaryImage rectBin = rect.toGrayImage().ApplyOtsuThreshold();
        //TODO: replace constants by a variable calculated from a parameter
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

ctk::BinaryImage GcSfRs::Reconstruct(ctk::BinaryImage &bin)
{
    ctk::BinaryImage reconst;
    //TODO: replace constants by a parameter
    reconst.Create(12, 12);
    int ox = 12;
    int oy = 12;
    for (int x=0; x<12; x++) {
        int xx = 5 + (ox+x)*10;
        for (int y=0; y<12; y++) {
            int yy = 5 + (oy+y)*10;
            reconst.set(x, y, bin.get(xx,yy));
        }
    }
    return reconst;
}

std::string GcSfRs::Decode(ctk::BinaryImage &reconst)
{
    if(reconst.width()>0){
        const std::string kDictionary = "../../theblackeyedpixels/data/dict.json";
        Dictionary dict = readDictionary(1001,kDictionary);
        //
        ctk::RgbImage col = reconst.toRgbImage();
        HalftoneGC halftone;
        halftone.read(col.get_data(), SCAN_ORDER, 3, 3, SCAN_ORDER);
        std::vector< std::vector<std::string> > msgs;
        std::vector<GeGrid> &grids = halftone.grids();
        //
        for (unsigned int i=0; i<grids.size(); i++) {
            msgs.push_back(( decodify(grids[i].cells(), dict) ));
        }
        if ((msgs.size()>0) && (msgs[0].size()>3)) {
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
