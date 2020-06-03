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

    ucout << "message looks like "  << message.to_string() << endl;
    ucout << "message path : "  << message.relative_uri().path() << endl;

    auto path = uri::split_path(uri::decode(message.relative_uri().path()));

    ucout << "path[0] : "  << path[0] << endl;
    ucout << "path[1] : "  << path[1] << endl;


    if (path.size() == 2 && path[0] == "spectrum" && path[1] == "sample.csv") {

        concurrency::streams::fstream::open_istream(message.relative_uri().path(), std::ios::in).then(
                [=](concurrency::streams::istream is) {
                    web::http::http_response response(web::http::status_codes::OK);
                    response.headers().set_content_type(U("application/text"));
                    response.headers().add(U("Content-Disposition"),U("inline; filename = \"") + path[1] + U("\""));
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
    } else {
        message.reply(status_codes::NotFound);
    }


    string_t file_name = message.relative_uri().path().substr(9,10);//"sample.csv";



    return;

};


