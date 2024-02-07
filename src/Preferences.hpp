#include <Preferences.h>
#include <SPIFFS.h>

Preferences preferences;

void InitPreferences()
{
    SPIFFS.begin();
    preferences.begin("credentials", false);

    NTP_SERVER = preferences.getString("ntp_server", "pool.ntp.org");

    WIFI_SSID = preferences.getString("wifi_ssid", "NO SIGNAL");
    WIFI_PASSWORD = preferences.getString("wifi_password", "#Zline159");
    WIFI_HOSTNAME = preferences.getString("wifi_hostname", "esp32");
    WIFI_AP_MODE = preferences.getBool("wifi_ap_mode", false);
    WIFI_DHCP = preferences.getBool("wifi_dhcp", true);
    WIFI_IP.fromString(preferences.getString("wifi_ip", "10.0.0.1"));
    WIFI_SUBNET.fromString(preferences.getString("wifi_subnet", "255.255.255.0"));
    WIFI_GATEWAY.fromString(preferences.getString("wifi_gateway", "10.0.0.1"));
    WIFI_DNS0.fromString(preferences.getString("wifi_dns0", "1.1.1.1"));
    WIFI_DNS1.fromString(preferences.getString("wifi_dns1", "8.8.8.8"));

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

    temperature_max = preferences.getFloat("temperature_max", 38.1);        // 38.5
    temperature_min = preferences.getFloat("temperature_min", 37.9);        // 37.5
    humidity_max = preferences.getFloat("humidity_max", 50.0);      // 50.0
    humidity_min = preferences.getFloat("humidity_min", 49.5);      // 49.5

    relay_1 = preferences.getBool("relay_1", false);
    relay_2 = preferences.getBool("relay_2", false);
    relay_3 = preferences.getBool("relay_3", false);
    relay_4 = preferences.getBool("relay_4", false);
}