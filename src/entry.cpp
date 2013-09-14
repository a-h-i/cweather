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
#include "weather_service.hpp"

static const char * version = "0.1.0 Alpha";

static void print_help()
{
    std::cout << "cweather weather utility version : " << version
              << "\nusage cweather [COUNTRY] [CITY]"
              << "\nor cweather [OPTION]"
              << "\nValid options : "
              << "\n--help or -h :\n\tprints this help message."
              << "\n--about or --version or -v :\n\tprints version and copyright notice.\n";
}

static void print_info()
{
    std::cout << "cweather weather utility version : " << version
              << ".\nCopytight (C) 2013 Ahmed H. Ismail."
              << "\nReleased under MIT License."
              << "\nSource code and License can be found at http://github.com/ah450/cweather .\n";
}

int main( int argc, const char * argv[] )
{
    if( argc >= 3 )
        {
            cweather::service::WebServiceXWeatherService to_test;
            try
                {
                    auto data = to_test.get_weather_data( argv[1], argv[2] );
                    std::cout << "Temperature : " << data.temperature << " C."
                              << "\nWind Speed : " << data.wind_speed << " KPH."
                              << "\nWind Direction : " << data.wind_direction << " Degrees."
                              << "\nPressure : " << data.pressure << " Pascal."
                              << "\nVisibility : " << data.visibility << " Kilometers."
                              << "\nHumidity : " << data.humidity * 100 << "%." ;
                    return 0;
                }
            catch( cweather::exceptions::IncorrectLocationException& )
                {
                    std::cerr <<
                              "Incorrect paramaters.\nrun cweather --help for usage information.\n";
                }
        }
    else if ( argc == 2 )
        {
            auto argument = std::string( argv[1] );
            if( argument == "--about" || argument == "--version" || argument == "-v" )
                {
                    print_info();
                    return 0;
                }
            else
                {
                    print_help();
                }
        }
    else
        {
            print_help();
            return -1;
        }
}