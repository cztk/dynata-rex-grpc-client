//
// Created by ztk on 14.03.24.
//

#ifndef DYNATA_REX_GRPC_CLIENT_CONFIG_H
#define DYNATA_REX_GRPC_CLIENT_CONFIG_H


#include <string>
#include <fstream>
#include <sstream>
#include <sys/syslog.h>


struct Config {

    std::string app_name = "DYNATA_REX_GRPC_CLIENT";
    //! PID file when running daemonized
    std::string pid_file;

    std::string app_socket = "/tmp/dynatarexgrpcclient.sock";

    bool rundaemonized = false;


    //! output log file for stuff
    std::string error_log = "";

    bool server_enable = true;

    bool syslogOutput = false;


    std::string dynataAccessKey = "";
    std::string dynataSecretKey = "";

    std::string grpc_host = "events.rex.dynata.com";



};




#endif //DYNATA_REX_GRPC_CLIENT_CONFIG_H
