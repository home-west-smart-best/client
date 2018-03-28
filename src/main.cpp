// cpMQTT: MQTT client, command processor

#include "AppInfo.h"
#include "_libMQTT/MQTTconfig.h"
#include "application.h"
#include <atomic>
#include <csignal>
#include <iostream>

using namespace std;

volatile sig_atomic_t receivedSIGINT{false};

void handleSIGINT(int /* s */)
{
    receivedSIGINT = true;
}

int main(int argc, char *argv[])
{
    try
    {
        signal(SIGINT, handleSIGINT);

        string mqttBroker{MQTT_LOCAL_BROKER};
        int mqttBrokerPort{MQTT_LOCAL_BROKER_PORT};

        switch (argc)
        {
            case 1:
                // Using MQTT_LOCAL_BROKER and MQTT_LOCAL_BROKER_PORT
                break;
            case 2:
                // Using MQTT_LOCAL_BROKER_PORT
                mqttBroker = string(argv[1]);
                break;
            case 3:
                mqttBroker = string(argv[1]);
                mqttBrokerPort = stoi(argv[2]);
                break;
            default:
                cerr << endl << "ERROR command line arguments: "
                        "cpMQTT <URL broker> <broker port>" << endl;
                exit(EXIT_FAILURE);
        }

        int major{0};
        int minor{0};
        int revision{0};

        cout << "-- MQTT application: " << APPNAME_VERSION << "  ";
        mosqpp::lib_init();
        mosqpp::lib_version(&major, &minor, &revision);
        cout << "uses Mosquitto lib version "
             << major << '.' << minor << '.' << revision << endl;

        // Second MQTT client
        AppController app("control", "app", mqttBroker, mqttBrokerPort);

        // Checking rc for reconnection, 'clients' is an initializer_list
        auto clients = {static_cast<mosqpp::mosquittopp *>(&app)};

        while (!receivedSIGINT)
        {
            for (auto client: clients)
            {
                int rc = client->loop();
                if (rc)
                {
                    cerr << "-- MQTT reconnect" << endl;
                    client->reconnect();
                }
            }
        }
    }
    catch (exception &e)
    {
        cerr << "Exception " << e.what() << endl;
    }
    catch (...)
    {
        cerr << "UNKNOWN EXCEPTION\n";
    }

    cout << "-- MQTT application: " << APPNAME_VERSION << " stopped"
         << endl << endl;
    mosqpp::lib_cleanup();

    return 0;
}
