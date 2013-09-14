/*
* The MIT License (MIT)
*
* Copyright (c) 2013 Ahmed H. Ismail
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
* the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef PARSERS_HPP
#define PARSERS_HPP
#include "exceptions.hpp"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#include "tinyxml2/tinyxml2.h"
#include <boost/regex.hpp>
#pragma GCC diagnostic pop
#include <sstream>

namespace cweather { namespace service { namespace parsers {


/**
* @brief retrives and parses an XML element.
* @detail return type must be convertable from string using std::stringstream.
* @throws cweather::exceptions::DataFormatException
* @sa cweather::exceptions::DataFormatException
*/
template<typename ReturnType>
    ReturnType xml_element_get(tinyxml2::XMLDocument * doc, const std::string &exception_header, const std::string &element_name, const std::string &root_element_name, const boost::regex &pattern)
    {
        using cweather::exceptions::DataFormatException;
        auto root_element = doc->RootElement();
        if(root_element == nullptr)
        {
           throw DataFormatException( exception_header + " : Could not get document root.");  
        }

        auto root_container_element = root_element->FirstChildElement( root_element_name.c_str() );

        if( root_container_element == nullptr)
        {
            throw DataFormatException( exception_header  + " : could not get " + root_element_name);
        }

        auto element =  root_container_element->FirstChildElement( element_name.c_str() );

        if(element == nullptr)
        {
            throw DataFormatException( exception_header + " : could not get " + element_name);
        }

        boost::match_results<const char *> m;
        bool found = boost::regex_search(element->GetText(), element->GetText() + strlen(element->GetText()), m, pattern, boost::match_default);
        if(found)
        {
            std::stringstream sstream;
            sstream << m[0];
            ReturnType to_return;
            sstream >> to_return;            
            return to_return;
        }else
        {
            throw DataFormatException( exception_header + " : could not parse value of element "  + element_name);
        }


    } 

/**
 * @brief Parses weather data from webserviceX xml format.
 * @detail uses tinyxml2 for parsing xml elements. XMLDocument is not owned by this Object.
 * 
 */
class WebServiceXParser
{
public:
    /**
     * @param doc should be properly initialized.
     */
    WebServiceXParser(tinyxml2::XMLDocument * doc) : doc(doc){}
    /**
     * @throws cweather::exceptions::DataFormatException
     * @sa cweather::exceptions::DataFormatException
     */
    double get_temp_celcius()
    {
        return xml_element_get<double>(doc, "Invalid XML format from WebServiceX", "Temperature", "CurrentWeather", temperature_regex);
    }
    /**
     * @throws cweather::exceptions::DataFormatException
     * @sa cweather::exceptions::DataFormatException
     */
    double get_pressure_pascal()
    {   // webserviceX uses hectopascals 1 hPa = 100 pascal
        return xml_element_get<double>(doc, "Invalid XML format from WebServiceX", "Pressure", "CurrentWeather", pressure_regex) * 100.0;
    }

    double get_visibility_kilometers()
    {   // webserviceX uses miles to represent visibility
        return xml_element_get<double>(doc, "Invalid XML format from WebServiceX", "Visibility", "CurrentWeather", visibility_regex) * 1.6;
    }
    double get_wind_speed_kph()
    {
        //websericeX uses miles per hour for wind speed
        return xml_element_get<double>(doc, "Invalid XML format from WebServiceX", "Wind", "CurrentWeather", wind_speed_regex) * 1.6;
    }
    unsigned short get_wind_direction_degrees()
    {
        return xml_element_get<unsigned short>(doc, "Invalid XML format from WebserviceX", "Wind", "CurrentWeather", wind_direction_regex);
    }

    double get_humidity()
    {
        return xml_element_get<double>(doc, "Invalid XML format from WebserviceX", "RelativeHumidity", "CurrentWeather", humidity_regex) / 100.0;
    }

private:
    tinyxml2::XMLDocument * doc;
    static const boost::regex temperature_regex;
    static const boost::regex pressure_regex;
    static const boost::regex visibility_regex;
    static const boost::regex wind_speed_regex;
    static const boost::regex wind_direction_regex;
    static const boost::regex humidity_regex;
};




}}} // cweather::service::parsers

#endif