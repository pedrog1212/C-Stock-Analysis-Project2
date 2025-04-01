#pragma once

#include "Candlestick.h"

//peaks and valleys class inherits from candlestick
public ref class PeaksAndValleys : public Candlestick
{
public:
    //indicates if this candlestick is a peak
    property bool isPeak;
    //indicates if this candlestick is a valley
    property bool isValley;
    //the difference between the value of the closest high and the peak
    property int leftMargin;
    //the difference between the value of the closest low and the Valley
    property int rightMargin;

    //default constructor
    PeaksAndValleys() {}

    //constructor that accepts an existing candlestick and pattern attributes
    PeaksAndValleys(Candlestick^ currentCandlestick, bool peak, bool valley, int leftM, int rightM)
    {
        //copy base candlestick data
        this->Date = currentCandlestick->Date;
        this->Open = currentCandlestick->Open;
        this->High = currentCandlestick->High;
        this->Low = currentCandlestick->Low;
        this->Close = currentCandlestick->Close;
        this->Volume = currentCandlestick->Volume;

        //assign pattern data
        isPeak = peak;
        isValley = valley;
        leftMargin = leftM;
        rightMargin = rightM;
    }
};