
#include "spdlog/spdlog.h"
#include "test.pb.h"
#include <Eigen/Dense>
#include <argparse/argparse.hpp>
#include <asio.hpp>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "MQTTClient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace Eigen;
using namespace argparse;
using json = nlohmann::json;
using namespace std;
volatile MQTTClient_deliveryToken deliveredtoken;
#define ADDRESS "tcp://127.0.0.1:1883"
#define CLIENTID "ExampleClientSub"
#define TOPIC "mqtt"
#define PAYLOAD "Hello World!"
#define QOS 1
#define TIMEOUT 10L

void delivered(void *context, MQTTClient_deliveryToken dt)
{
  printf("Message with token value %d delivery confirmed\n", dt);
  deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen,
             MQTTClient_message *message)
{
  printf("Message arrived\n");
  printf("     topic: %s\n", topicName);
  printf("   message: %.*s\n", message->payloadlen, (char *)message->payload);
  MQTTClient_freeMessage(&message);
  MQTTClient_free(topicName);
  return 1;
}

void connlost(void *context, char *cause)
{
  printf("\nConnection lost\n");
  printf("     cause: %s\n", cause);
}

int f_proto(double i)
{
  MsgPerson person;
  person.set_id(i);
  std::cout << person.id() << std::endl;
  return person.id();
}

int f_socket()
{
  asio::io_context io_context;
  asio::ip::tcp::socket socket(io_context);
  socket.open(asio::ip::tcp::v4());
  asio::error_code ec;
  socket.bind(asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 12345), ec);
  asio::ip::tcp::endpoint endpoint(asio::ip::address::from_string("127.0.0.1"),
                                   12345);
  socket.connect(endpoint, ec);
  if (!ec)
  {
    std::cout << "socket connect" << std::endl;
  }
  return 1;
}

int f_argparse()
{
  argparse::ArgumentParser parser("example", "Argument parser example");
  parser.add_argument("test").default_value('test');
  std::cout << parser << std::endl;
  return 3;
}

int f_eigen()
{
  MatrixXd test = MatrixXd::Zero(1, 1);
  std::cout << test << std::endl;
  return 2;
}

int f_fmt()
{
  fmt::print("fmt-testing\n");
  return 1;
}
int f_spdlog()
{
  spdlog::info("spdlog");
  std::cout << "\n" << std::endl;
  return 1;
}

int f_json()
{
  json j = "{ \"nlohmann-json\": true, \"pi\": 3.141 }"_json;
  std::cout << j.dump(4) << std::endl;
  return 2;
}

int f_mqtt()
{
  MQTTClient client;
  MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
  int rc;

  if ((rc = MQTTClient_create(&client, ADDRESS, CLIENTID,
                              MQTTCLIENT_PERSISTENCE_NONE, NULL)) !=
      MQTTCLIENT_SUCCESS)
  {
    printf("Failed to create client, return code %d\n", rc);
    rc = EXIT_FAILURE;
    goto exit;
  }

  if ((rc = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd,
                                    delivered)) != MQTTCLIENT_SUCCESS)
  {
    printf("Failed to set callbacks, return code %d\n", rc);
    rc = EXIT_FAILURE;
    goto destroy_exit;
  }

  conn_opts.keepAliveInterval = 20;
  conn_opts.cleansession = 1;
  if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
  {
    printf("Failed to connect, return code %d\n", rc);
    rc = EXIT_FAILURE;
    goto destroy_exit;
  }

  printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
         "Press Q<Enter> to quit\n\n",
         TOPIC, CLIENTID, QOS);
  if ((rc = MQTTClient_subscribe(client, TOPIC, QOS)) != MQTTCLIENT_SUCCESS)
  {
    printf("Failed to subscribe, return code %d\n", rc);
    rc = EXIT_FAILURE;
  }
  else
  {
    int ch;
    do
    {
      ch = getchar();
    } while (ch != 'Q' && ch != 'q');

    if ((rc = MQTTClient_unsubscribe(client, TOPIC)) != MQTTCLIENT_SUCCESS)
    {
      printf("Failed to unsubscribe, return code %d\n", rc);
      rc = EXIT_FAILURE;
    }
  }

  if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS)
  {
    printf("Failed to disconnect, return code %d\n", rc);
    rc = EXIT_FAILURE;
  }
destroy_exit:
  MQTTClient_destroy(&client);
exit:
  return 0;
}

int main()
{
  int a = f_json();
  int b = f_socket();
  int c = f_argparse();
  int d = f_eigen();
  int e = f_fmt();
  int f = f_spdlog();
  int t = f_json();
  int g = f_proto(2);
  int h = f_mqtt();
}
