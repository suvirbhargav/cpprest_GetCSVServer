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

    string_t file_name = "sample.csv";

    concurrency::streams::fstream::open_istream(U("spectrum/sample.csv"), std::ios::in).then(
            [=](concurrency::streams::istream is) {
                web::http::http_response response(web::http::status_codes::OK);
                response.headers().set_content_type(U("application/text"));
                response.headers().add(U("Content-Disposition"),U("inline; filename = \"") + file_name + U("\""));
                response.headers().set_content_length(3495423);
                response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
                response.set_body(std::move(is), U("application/text"));

                message.reply(response)
                        .then([](pplx::task<void> t) {
                            try {
                                t.get();
                            }
                            catch (...) {
                                //
                                std::cout << "catch" << std::endl;
                            }
                        });
            }).then([=](pplx::task<void> t) {
        try {
            t.get();
        }
        catch (...) {
            message.reply(status_codes::InternalError, U("INTERNAL ERROR "));
            std::cout << "internal error" << std::endl;
        }
    });

    return;

};


