 #include "stdafx.h" 
#include "PINIReadWriter.h"

using namespace std;

PINIReadWriter::PINIReadWriter(string strFileName)
{
	_error = ini_parse(strFileName.c_str(), ValueHandler, this);
}

PINIReadWriter::~PINIReadWriter()
{

}


int PINIReadWriter::ParseError()
{
    return _error;
}


string PINIReadWriter::getStringValue(string section, string name, string default_value)
{
    string key = MakeKey(section, name);
    return _values.count(key) ? _values[key] : default_value;
}

long PINIReadWriter::getIntValue(string section, string name, long default_value)
{
    string valstr = getStringValue(section, name, "");
    const char* value = valstr.c_str();
    char* end;
    long n = strtol(value, &end, 0);
    return end > value ? n : default_value;
}

double PINIReadWriter::getDoubleValue(string section, string name, double default_value)
{
	string valstr = getStringValue(section, name, "");

	istringstream stringToDouble(valstr);
	double dVal=0.;
	stringToDouble >> dVal;
	return dVal;	
}



bool PINIReadWriter::GetBoolean(string section, string name, bool default_value)
{
    string valstr = getStringValue(section, name, "");
    // Convert to lower case to make string comparisons case-insensitive
    std::transform(valstr.begin(), valstr.end(), valstr.begin(), ::tolower);
    if(valstr == "true" || valstr == "yes" || valstr == "on" || valstr == "1")
        return true;
    else if(valstr == "false" || valstr == "no" || valstr == "off" || valstr == "0")
        return false;
    else
        return default_value;
}

string PINIReadWriter::MakeKey(string section, string name)
{
    string key = section + "." + name;
    // Convert to lower case to make section/name lookups case-insensitive
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    return key;
}

int PINIReadWriter::ValueHandler(void* user, const char* section, const char* name,
                            const char* value)
{
	PINIReadWriter* reader = (PINIReadWriter*)user;
    string key = MakeKey(section, name);
    if(reader->_values[key].size() > 0)
        reader->_values[key] += "\n";
    reader->_values[key] += value;
    return 1;
}
