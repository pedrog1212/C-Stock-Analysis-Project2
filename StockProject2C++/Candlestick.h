#pragma once
using namespace System;
#include "string"

//class representing a single candlestick data point in stock trading.
public ref class Candlestick
{
public:

    //properties representing candlestick attributes.

    //trading volume of the stock for the given date.
    property unsigned long long Volume;
    //closing price of the stock for the given date.
    property double Close;
    //lowest price reached during the given date.
    property double Low;
    //highest price reached during the given date.
    property double High;
    //opening price of the stock for the given date.
    property double Open;
    //date of the candlestick.
    property DateTime Date;
    //default constructor.
    Candlestick() {}

    //parameterized constructor to initialize candlestick attributes.
    Candlestick(DateTime date, double open, double high, double low, double close, unsigned long long volume)
    {
        //initialize the candlestick properties with provided values.
        this->Date = date;
        this->Open = open;
        this->High = high;
        this->Low = low;
        this->Close = close;
        this->Volume = volume;
    }

    //constructor that takes a formatted string of the form "Date, open, high, low, close, volume"
    Candlestick(String^ candlestickString);
};
