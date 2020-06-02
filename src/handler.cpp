//
// Created by suvir bhargav on 2020-05-23.
//
#include "handler.h"

handler::handler() {
    //ctor
}

handler::handler(utility::string_t url) : m_listener(url) {
    m_listener.support(methods::GET, std::bind(&handler::handle_get, this, std::placeholders::_1));

}

handler::~handler() {
    //dtor
}

void handler::handle_error(pplx::task<void> &t) {
    try {
        t.get();
    }
    catch (...) {
        // Ignore the error, Log it if a logger is available
    }
}


//
// Get Request
//
void handler::handle_get(http_request message) {
    ucout << message.to_string() << endl;

    auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

    message.relative_uri().path();

    //set response instance
    /*http_response response(status_codes::OK);
    response.headers().set_content_type(U("application/text"));
    response.headers().set_content_length(3495423);
    response.headers().set_cache_control(U("max-age=300"));
    response.headers().add(U("Content-Security-Policy"), U("default-src 'none'; style-src 'unsafe-inline'; sandbox"));
    response.headers().add(U("Strict-Transport-Security"), U("max-age=31536000"));
    response.headers().add(U("Accept-Ranges"), U("bytes"));
    response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
    response.headers().add(U("Source-Age"), U("13"));*/


    concurrency::streams::fstream::open_istream(U("GetFile/Pist 10s again 2_Z-Weighting.csv"), std::ios::in).then(
    //concurrency::streams::fstream::open_istream(U("GetFile/less.csv"), std::ios::in).then(
            [=](concurrency::streams::istream is) {
                message.reply(status_codes::OK, is,  U("Content-Type: application/text\n"
                                                       "Content-Length: 581\n"
                                                       "Cache-Control: max-age=300\n"
                                                       "Content-Security-Policy: default-src 'none'; style-src 'unsafe-inline'; sandbox\n"
                                                       "Strict-Transport-Security: max-age=31536000\n"
                                                       "X-Content-Type-Options: nosniff\n"
                                                       "X-Frame-Options: deny\n"
                                                       "X-XSS-Protection: 1; mode=block\n"
                                                       "Via: 1.1 varnish (Varnish/6.0)\n"
                                                       "Accept-Ranges: bytes\n"
                                                       "Via: 1.1 varnish\n"
                                                       "X-Served-By: cache-bma1643-BMA\n"
                                                       "X-Cache: MISS, HIT\n"
                                                       "X-Cache-Hits: 0, 1\n"
                                                       "Vary: Authorization,Accept-Encoding\n"
                                                       "Access-Control-Allow-Origin: *\n"
                                                       "Source-Age: 13"))
                        .then([](pplx::task<void> t) {
                            try {
                                t.get();
                            }
                            catch (...) {
                                //
                            }
                        });
            }).then([=](pplx::task<void> t) {
        try {
            t.get();
        }
        catch (...) {
            message.reply(status_codes::InternalError, U("INTERNAL ERROR "));
        }
    });

    return;

};


