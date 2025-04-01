#include "pch.h"
#include "Candlestick.h"

//constructor that takes a CSV string and initializes the Candlestick object.
Candlestick::Candlestick(String^ candlestickString)
{
    //remove all double quotes from the string to ensure clean parsing.
    candlestickString = candlestickString->Replace("\"", "");

    //define delimiters used to split the string into separate values.
    array<wchar_t>^ seperators = gcnew array<wchar_t>{ ',', '\"' };

    //split the cleaned string using commas and remove empty entries.
    array<String^>^ values = candlestickString->Split(seperators, StringSplitOptions::RemoveEmptyEntries);

    //ensure the array has at least 6 elements (Date, Open, High, Low, Close, Volume).
    if (values->Length < 6) 
    {
        throw gcnew ArgumentException("Invalid candlestick string format.");
    }

    try {
        //parse the date value from the first element of the array.
        this->Date = DateTime::Parse(values[0]);

        //parse numeric values for Open, High, Low, Close, and Volume.
        this->Open = Convert::ToDouble(values[1]);
        this->High = Convert::ToDouble(values[2]);
        this->Low = Convert::ToDouble(values[3]);
        this->Close = Convert::ToDouble(values[4]);
        this->Volume = Convert::ToUInt64(values[5]);
    }
    catch (Exception^ ex) {
        //throw an exception if there is an error while parsing the data.
        throw gcnew ArgumentException("Error parsing candlestick data: " + ex->Message);
    }
}