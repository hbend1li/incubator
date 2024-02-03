#include <Preferences.h>
Preferences preferences;

#define Relay_1 17
#define Relay_2 5
#define Relay_3 18
#define Relay_4 19

String WIFI_SSID;
String WIFI_PASSWORD;
String WIFI_HOSTNAME;
bool WIFI_AP_MODE;
IPAddress WIFI_IP(10, 0, 10, 99);
IPAddress WIFI_GATEWAY(10, 0, 10, 1);
IPAddress WIFI_SUBNET(255, 255, 255, 0);

String NTP_SERVER;

String MQTT_HOST;
uint16_t MQTT_PORT;
String MQTT_USERNAME;
String MQTT_PASSWORD;
String MQTT_SUB;

float Temperature;
float Humidity;
float temperature_min;
float temperature_max;
float humidity_min;
float humidity_max;

bool relay_1;
bool relay_2;
bool relay_3;
bool relay_4;

void InitPreferences()
{
    preferences.begin("credentials", false);

    WIFI_SSID = preferences.getString("wifi_ssid", "NO SIGNAL");
    WIFI_PASSWORD = preferences.getString("wifi_password", "#Zline159");
    WIFI_HOSTNAME = preferences.getString("wifi_hostname", "esp32");
    WIFI_AP_MODE = preferences.getBool("wifi_ap_mode", false);

    // WIFI_IP = IPAddress::fromString(preferences.getString("wifi_ip", "10.0.10.99"));
    // WIFI_GATEWAY = IPAddress::fromString(preferences.getString("wifi_gateway", "10.0.10.1"));
    // WIFI_SUBNET = IPAddress::fromString(preferences.getString("wifi_subnet", "255.255.255.0"));

    // my Mosquitto Broker
    MQTT_HOST = preferences.getString("mqtt_host", "10.0.10.1");
    MQTT_PORT = preferences.getShort("mqtt_port", 1883);
    MQTT_USERNAME = preferences.getString("mqtt_username", "incubator");
    MQTT_PASSWORD = preferences.getString("mqtt_password", "102403");
    MQTT_SUB = preferences.getString("mqtt_sub", "incub");

    // broker.emqx.io
    // MQTT_HOST = "broker.emqx.io";
    // MQTT_PORT = 1883;
    // MQTT_USERNAME = "";
    // MQTT_PASSWORD = "";
    // MQTT_SUB = "Ng3cKKI95qx3QI5pFTo2fCHK";

    // hivemq.cloud
    // MQTT_HOST = "b19b2fd9e16d4c8982ac0169cbc9a741.s2.eu.hivemq.cloud";
    // MQTT_PORT = 8883;
    // MQTT_USERNAME = "hbend1li";
    // MQTT_PASSWORD = "Genesis.07";
    // MQTT_SUB = "Ng3cKKI95qx3QI5pFTo2fCHK";

    temperature_max = 38.5; // preferences.getFloat("temperature_max", 38.5);
    temperature_min = 37.5; // preferences.getFloat("temperature_min", 37.5);
    humidity_max = 50.0;    // preferences.getFloat("humidity_max", 55.0);
    humidity_min = 49.5;    // preferences.getFloat("humidity_min", 45.0);

    // relay_1 = preferences.getBool("relay_1", false);
    // relay_2 = preferences.getBool("relay_2", false);
    relay_3 = preferences.getBool("relay_3", false);
    relay_4 = preferences.getBool("relay_4", false);
}