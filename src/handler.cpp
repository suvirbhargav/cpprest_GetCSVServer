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

    concurrency::streams::fstream::open_istream(U("GetFile/Pist 10s again 2_Z-Weighting.csv"), std::ios::in).then(
            [=](concurrency::streams::istream is) {
                message.reply(status_codes::OK, is, U("text/csv"))
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


