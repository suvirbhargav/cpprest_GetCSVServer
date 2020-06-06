//
// Created by suvir bhargav on 2020-05-23.
//

#ifndef CPPREST_GETCSV_HANDLER_H
#define CPPREST_GETCSV_HANDLER_H

#include <iostream>

#include <cpprest/http_listener.h>
#include <cpprest/filestream.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::experimental::listener;

using namespace std;


class handler
{
public:
    handler();
    handler(utility::string_t url);
    virtual ~handler();

    pplx::task<void>open(){return m_listener.open();}
    pplx::task<void>close(){return m_listener.close();}

protected:

private:
    void handle_get(http_request message);

    void handle_error(pplx::task<void>& t);
    http_listener m_listener;

    bool exists_test(const string &name);
};

#endif //CPPREST_GETCSV_HANDLER_H
