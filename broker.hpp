#ifndef __BROKER__
#define __BROKER__

#include <iostream>
#include "data_manager.hpp"
#include <Poco/String.h>
#include <Poco/Message.h>
#include <Poco/Logger.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerParams.h>
#include <Poco/Net/TCPServerConnectionFactory.h>
#include <vector>

using namespace std;
using namespace Poco;
using namespace Poco::Net;

//! BrokerApplication manage the Application structure and options
class BrokerApplication : public Util::ServerApplication
{
public:
    BrokerApplication();
    ~BrokerApplication();
protected:
    int getPath(char* pBuf);
    void initialize(Util::Application& self);
    void uninitialize();
    void defineOptions(Util::OptionSet& options);
    void handleOption(const string& name, const string& value);
    void handleMode(const string& name, const string& value);
    void handlePort(const string& name, const string& value);
    void handleServerParams(const std::string& name, const std::string& value);
    void displayHelp();

    //! The main function (used by libpoco)
    int main(const vector<string>& args);
private:
    string debugTag;
    bool m_helpRequested, m_version, _debug_mode;
    Logger& logger;
    unsigned short port;
    int num_threads;
    int queuelen;
    int idletime;
    bool _data_mode;
    bool _stdout_logging;
    bool _filename_spec;
    string _exe_path;
    string _log_file;
    string _filename;
    string _mongo_ip;
    string _mongo_port;
    string _mongo_db;
    string _mongo_collection;
    DataManager* _data_manager;
};

class TCPConnectionFactory : public Net::TCPServerConnectionFactory
{
public:
    //! TCPConnectionFactory create the TCP connections
    TCPConnectionFactory(DataManager* data_m);
    ~TCPConnectionFactory();

    //! Create a new broker connection
    Net::TCPServerConnection* createConnection(const StreamSocket& socket);
private:
    DataManager* _data_m;
};

#endif
