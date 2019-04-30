#include "httpserver.h"

#include <QtHttpServer/QHttpServer>

HttpServer::HttpServer()
{
    QHttpServer httpServer;
    httpServer.route("/", []() {
      return "Hello world";
    });
    httpServer.listen(QHostAddress::Any);
}
