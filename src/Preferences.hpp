#include <Preferences.h>
#include <SPIFFS.h>

Preferences preferences;

void ResetPreferences()
{
    Serial.print("Reset all preferences ... ");
    NTP_SERVER = "pool.ntp.org";
    TELEGRAM_TOKEN = "6890372375:AAGXAl_3nYDXUgAfaPFoHN6ZF6QDbl_i7bM";
    TELEGRAM_CHATID = "-4191421330";
    WIFI_SSID = "NO SIGNAL";
    WIFI_KEY = "#Zline159";
    WIFI_HOSTNAME = "esp32";
    WIFI_AP_MODE = false;
    WIFI_DHCP = true;
    WIFI_IP.fromString("10.0.0.1");
    WIFI_SUBNET.fromString("255.255.255.0");
    WIFI_GATEWAY.fromString("10.0.0.1");
    WIFI_DNS0.fromString("1.1.1.1");
    WIFI_DNS1.fromString("8.8.8.8");
    MQTT_HOST = "10.0.10.1";
    MQTT_PORT = 1883;
    MQTT_USERNAME = "incubator";
    MQTT_PASSWORD = "102403";
    MQTT_SUB = "incub";
    temperature_max = 38.1;
    temperature_min = 37.9;
    humidity_max = 50.0;
    humidity_min = 49.5;
    relay_1 = false;
    relay_2 = false;
    relay_3 = false;
    relay_4 = false;
    DayNight = 0;
    DayPos = 0;
    NoonPos = 90;
    NightPos = 180;

    preferences.putString("telegram_token", TELEGRAM_TOKEN);
    preferences.putString("telegram_chatid", TELEGRAM_CHATID);
    preferences.putString("ntp_server", NTP_SERVER);
    preferences.putString("wifi_ssid", WIFI_SSID);
    preferences.putString("wifi_key", WIFI_KEY);
    preferences.putString("wifi_hostname", WIFI_HOSTNAME);
    preferences.putBool("wifi_ap_mode", WIFI_AP_MODE);
    preferences.putBool("wifi_dhcp", WIFI_DHCP);
    preferences.putString("wifi_ip", String(WIFI_IP));
    preferences.putString("wifi_subnet", String(WIFI_SUBNET));
    preferences.putString("wifi_gateway", String(WIFI_GATEWAY));
    preferences.putString("wifi_dns0", String(WIFI_DNS0));
    preferences.putString("wifi_dns1", String(WIFI_DNS1));
    preferences.putString("mqtt_host", MQTT_HOST);
    preferences.putShort("mqtt_port", MQTT_PORT);
    preferences.putString("mqtt_username", MQTT_USERNAME);
    preferences.putString("mqtt_password", MQTT_PASSWORD);
    preferences.putString("mqtt_sub", MQTT_SUB);
    preferences.putFloat("temperature_min", temperature_min);
    preferences.putFloat("temperature_max", temperature_max);
    preferences.putFloat("humidity_min", humidity_min);
    preferences.putFloat("humidity_max", humidity_max);
    preferences.putBool("relay_1", relay_1);
    preferences.putBool("relay_2", relay_2);
    preferences.putBool("relay_3", relay_3);
    preferences.putBool("relay_4", relay_4);
    preferences.putInt("DayNight", DayNight);
    preferences.putInt("DayPos", DayPos);
    preferences.putInt("NoonPos", NoonPos);
    preferences.putInt("NightPos", NightPos);
    Serial.println("[done]");
}

void InitPreferences()
{
    Serial.print("Load preferences ... ");
    SPIFFS.begin();
    preferences.begin("credentials", false);

    NTP_SERVER = preferences.getString("ntp_server", "pool.ntp.org");
    TELEGRAM_TOKEN = preferences.getString("telegram_token", "");
    TELEGRAM_CHATID = preferences.getString("telegram_chatid", "");

    WIFI_SSID = preferences.getString("wifi_ssid", "NO SIGNAL");
    WIFI_KEY = preferences.getString("wifi_key", "#Zline159");
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

    temperature_max = preferences.getFloat("temperature_max", 38.1); // 38.5
    temperature_min = preferences.getFloat("temperature_min", 37.9); // 37.5
    humidity_max = preferences.getFloat("humidity_max", 50.0);       // 50.0
    humidity_min = preferences.getFloat("humidity_min", 49.5);       // 49.5

    relay_1 = preferences.getBool("relay_1", false);
    relay_2 = preferences.getBool("relay_2", false);
    relay_3 = preferences.getBool("relay_3", false);
    relay_4 = preferences.getBool("relay_4", false);

    DayNight = preferences.getInt("DayNight", 0);
    DayPos = preferences.getInt("DayPos", 0);
    NoonPos = preferences.getInt("NoonPos", 90);
    NightPos = preferences.getInt("NightPos", 180);
    Serial.println("[done]");
}