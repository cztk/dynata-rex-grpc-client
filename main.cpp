#include <iostream>
#include <getopt.h>
#include <google/protobuf/stubs/common.h>
#include "src/config/config.h"
#include "src/daemonize/daemonize.h"
#include "src/queue/locked_queue.h"
#include "src/appio/InputHandler.h"
#include "src/appio/OutputHandler.h"

static bool rundaemonized = false;
static FILE *log_stream;
std::string PID_FILE;
std::string APP_NAME = "DYNATA_REX_GRPC_CLIENT";

int APP_RUNNING = 1;
Config config{};



int load_config(const std::string &config_file_name) {
    // TODO check file exists and file exists in $rundir and /etc/ path
    std::ifstream fin(config_file_name);
    std::string line;

    while (getline(fin, line)) {

        std::istringstream sin(line.substr(line.find('=') + 1));

        if (line.find("app_name") != std::string::npos)
        {
            std::string old_name = config.app_name;
            sin >> config.app_name;
            syslog(LOG_INFO, "%s: is now called %s", old_name.c_str(), config.app_name.c_str());
            APP_NAME = config.app_name;
        } else if (line.find("pid_file") != std::string::npos)
        {
            sin >> config.pid_file;
            PID_FILE = config.pid_file;
        }

        else if (line.find("app_socket") != std::string::npos)
            sin >> config.app_socket;
        else if (line.find("rundaemonized") != std::string::npos)
            sin >> config.rundaemonized;
        else if (line.find("error_log") != std::string::npos)
            sin >> config.error_log;
        else if (line.find("server_enable") != std::string::npos)
            sin >> config.server_enable;
        else if (line.find("syslogOutput") != std::string::npos)
            sin >> config.syslogOutput;

        else if( line.find("dynataAccessKey") != std::string::npos )
            sin >> config.dynataAccessKey;
        else if( line.find("dynataSecretKey") != std::string::npos )
            sin >> config.dynataSecretKey;

        else if( line.find("grpc_host") != std::string::npos )
            sin >> config.grpc_host;

    }
#ifdef DEBUG

#endif

    return true;
}

void stopApp() {
    {
        APP_RUNNING = 0;
        m_timer.interrupt();
    }
}

int main(int argc, char *argv[]) {

#ifdef DEBUG
    std::cout << "Hello, World!" << std::endl;
#endif

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int opt;
    bool config_loaded = false;

    while ((opt = getopt(argc, argv, ":c:d")) != -1) {
        switch (opt) {
            case 'c':
                //configuration file
                conf_file_name = optarg;
                config_loaded = load_config(conf_file_name);
                break;
            case 'd':
                if (config_loaded) {
                    syslog(LOG_INFO, "%s: run daemonized", APP_NAME.c_str());
                    config.rundaemonized = true;
                    rundaemonized = true;
                } else {
                    std::cout << "please specify -c option first\n";
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                break;
        }
    }

    if (config.rundaemonized) {
        rundaemonized = true;
        daemonize();
    } else {
        APP_RUNNING = 1;
    }



/* Open system log and write message to it */
//    openlog(app_name.c_str(), LOG_PID|LOG_CONS, LOG_DAEMON);
//    syslog(LOG_INFO, "Started %s", app_name.c_str());
    openlog(APP_NAME.c_str(), LOG_PID | LOG_CONS, LOG_DAEMON);
    syslog(LOG_INFO, "Started %s", APP_NAME.c_str());

    if (rundaemonized) {
        /* Daemon will handle two signals */
        signal(SIGINT, handle_signal);
        signal(SIGHUP, handle_signal);
    }

    /*
     * Application logic
     */


    utils::LockedQueue<std::string> messages;

    OutputHandler outputHandler(&config, &messages);
    outputHandler.initialize();


    InputHandler inputHandler(&config, &messages);
    inputHandler.initialize();

    //
//    auto outputHandler = OutputHandler(&config, &messages, &databaseHandler, &databaseTasksThreadpool);
//    std::thread outputHandlerThread = outputHandler.run();




    while (m_timer.wait_for(std::chrono::seconds(10))) {
        if(0 == inputHandler.status) {
            inputHandler.deinitialize();
            inputHandler.initialize();
        }
        if (!APP_RUNNING) break;

    }

    inputHandler.deinitialize();
    outputHandler.deinitialize();
//
//    outputHandler.stop();
//    if(outputHandlerThread.joinable()) {
//        outputHandlerThread.join();
//    }

    syslog(LOG_CRIT, "could not queue messages:");
    while(!messages.empty()) {
        auto msg = messages.pop();
        syslog(LOG_CRIT, "%s", msg.c_str());
    }

    /* Close log file, when it is used. */
    if (log_stream != stdout && log_stream != nullptr) {
        fclose(log_stream);
    }
    /* Write system log and close it. */
    //syslog(LOG_INFO, "Stopped %s", app_name.c_str());
    syslog(LOG_INFO, "Stopped %s", APP_NAME.c_str());
    closelog();
    if (rundaemonized) {
        unlink(PID_FILE.c_str());
    }
    return EXIT_SUCCESS;

    return 0;
}
