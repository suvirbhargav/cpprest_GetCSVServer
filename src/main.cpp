#include "handler.h"

const string LOCALHOST = "http://127.0.0.1:";
const string PORT = "34568";
const string APIVERSION = "/v1/";

std::unique_ptr<handler> g_httpHandler;


void on_initialize(const string_t &address) {

    uri_builder uri(address);

    auto addr = uri.to_uri().to_string();
    g_httpHandler = std::unique_ptr<handler>(new handler(addr));
    g_httpHandler->open().wait();

    ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

    return;
}

void on_shutdown() {
    g_httpHandler->close().wait();
    return;
}

#ifdef _WIN32
int wmain(int argc, wchar_t *argv[])
#else

int main(int argc, char *argv[])
#endif
{
    utility::string_t port = U(PORT);
    if (argc == 2) {
        port = argv[1];
    }

    utility::string_t address = U(LOCALHOST);
    address.append(port + APIVERSION);

    on_initialize(address);
    std::cout << "Press ENTER to exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);

    on_shutdown();
    return 0;
}
