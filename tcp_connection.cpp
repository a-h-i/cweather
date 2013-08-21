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
#include <iterator>
#include <istream>

cweather::service::TCPConnecter::TCPConnecter( const std::string& host ) : sock( service )
{
    boost::asio::ip::tcp::resolver res( service );
    boost::asio::ip::tcp::resolver::query query( host, "http" );
    boost::system::error_code ec;
    auto ep_iter  = res.resolve( query, ec );
    //TODO: throw exceptions instead of terminating
    if( !ec )
        {
            sock.connect( *ep_iter, ec );
            if( ec )
                {
                    // error while connecting
                    std::cerr << "Error while connecting to host.\nError code : " << ec.message();
                    std::exit( -1 );
                }
            // connected
            boost::asio::socket_base::keep_alive option( true );
            sock.set_option( option, ec );
        }
    else
        {
            // error while resolving
            std::cerr << "Error while resolving host.\nError code : " << ec.message();
            std::exit( -1 );
        }
}

cweather::service::TCPConnecter::~TCPConnecter()
{
    boost::system::error_code ec; // TODO: log error code
    sock.shutdown( boost::asio::ip::tcp::socket::shutdown_both, ec );
    sock.close( ec );
}


std::size_t cweather::service::TCPConnecter::send_data( const std::vector<char> &data, boost::system::error_code& ec )
{
    auto written = boost::asio::write( sock, boost::asio::buffer( data ), ec );
    return written;
}


std::size_t cweather::service::TCPConnecter::read_data( std::vector<char> &data, boost::system::error_code& ec )
{
    auto read = sock.read_some(boost::asio::buffer(data), ec);
    return read;
}