//
// Created by suvir bhargav on 2020-05-23.
//
#include "handler.h"

const string FOLDERNAME = "spectrum";
const string FILENAME = "sample.csv";


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
    auto path = uri::split_path(uri::decode(message.relative_uri().path()));

    if (path.size() == 2 && path[0] == FOLDERNAME && path[1] == FILENAME) {

        concurrency::streams::fstream::open_istream(message.relative_uri().path(), std::ios::in).then(
                [=](concurrency::streams::istream is) {
                    http_response response(status_codes::OK);
                    response.headers().set_content_type(U("application/text"));
                    response.headers().add(U("Content-Disposition"), U("inline; filename = \"") + path[1] + U("\""));
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
    } else {
        http_response response(status_codes::NotFound);
        response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
        message.reply(response);

    }

    return;

};



