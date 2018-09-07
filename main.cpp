#include "ui/maindialog.h"
#include <QApplication>
#include "network/secureclient.h"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <network/dataflowextract.h>
#include <isc/utils.h>
#include <dataobject.h>
#include <objecttable.h>



int main(int argc, char *argv[])
{
    srand (time(NULL));
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();




    QApplication a(argc, argv);
    MainDialog w;
    w.show();

//    std::ifstream file;

//    file.open("stream.txt", std::ios::binary);
//    if(file.is_open()) {
//        std::string s;
//        std::cout << "start read file content\n";
//        if(getline(file, s)) {
//            std::cout <<"string: " << s;
//            std::vector<std::string> vect;
//            cppframework::str::Util::split(s, ",", vect);
//            for(auto &elem : vect)
//                std::cout << cppframework::str::Util::convert(elem, 0.0) << " ";

//        }
//    } else {
//        std::cout << "file not found\n";
//    }

//    fflush(stdout);

    return a.exec();
}
