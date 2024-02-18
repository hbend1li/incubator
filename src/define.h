#define Relay_1 17
#define Relay_2 5
#define Relay_3 18
#define Relay_4 19

bool relay_1;
bool relay_2;
bool relay_3;
bool relay_4;

String NTP_SERVER;

String TELEGRAM_TOKEN;
String TELEGRAM_CHATID;

String WIFI_SSID;
String WIFI_KEY;
String WIFI_HOSTNAME;
bool WIFI_AP_MODE;
bool WIFI_DHCP;
IPAddress WIFI_IP;
IPAddress WIFI_GATEWAY;
IPAddress WIFI_SUBNET;
IPAddress WIFI_DNS0;
IPAddress WIFI_DNS1;

String MQTT_HOST;
uint16_t MQTT_PORT;
String MQTT_USERNAME;
String MQTT_PASSWORD;
String MQTT_SUB;

float Temperature, lastTemperature;
float temperature_max;
float temperature_min;

float Humidity, lastHumidity;
float humidity_max;
float humidity_min;

bool warning = false;

int DayNight;
int DayPos = 0;
int NoonPos = 0;
int NightPos = 0;
int LastPos = 0;

int CloudSend(String, String);