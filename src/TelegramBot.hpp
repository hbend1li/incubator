#include <FastBot.h>

#define BOT_TOKEN "6890372375:AAGXAl_3nYDXUgAfaPFoHN6ZF6QDbl_i7bM"
#define CHAT_ID "-4191421330"

FastBot bot(BOT_TOKEN);

String precessMsg(String &msg)
{
  String res = "Error 404: param not found";

  // ex: /set tmax 38.20
  // Découper la commande en segments
  int paramIndex = msg.indexOf(' ');
  int valueIndex = msg.indexOf(' ', paramIndex + 1);

  String paramName = msg.substring(paramIndex + 1, valueIndex);
  String paramValue = msg.substring(valueIndex + 1);

  // Convertir la valeur en float

  // Affecter la valeur à la variable correspondante
  if (paramName == "tmax")
  {
    float value = paramValue.toFloat();
    temperature_max = value;
    preferences.putFloat("temperature_max", temperature_max);
    res = "Temperature MAX is set to: " + String(temperature_max);
  }
  else if (paramName == "tmin")
  {
    float value = paramValue.toFloat();
    temperature_min = value;
    preferences.putFloat("temperature_min", temperature_min);
    res = "Temperature MIN is set to: " + String(temperature_min);
  }
  else if (paramName == "hmax")
  {
    float value = paramValue.toFloat();
    humidity_max = value;
    preferences.putFloat("humidity_max", humidity_max);
    res = "Humidity MAX is set to: " + String(humidity_max);
  }
  else if (paramName == "hmin")
  {
    float value = paramValue.toFloat();
    humidity_min = value;
    preferences.putFloat("humidity_min", humidity_min);
    res = "Humidity MIN is set to: " + String(humidity_min);
  }
  else if (paramName == "day_pos")
  {
    int value = paramValue.toInt();
    setDayNightPos(DAY, value);
    res = "Day position set to: " + String(DayPos) + " °";
  }
  else if (paramName == "noon_pos")
  {
    int value = paramValue.toInt();
    setDayNightPos(NOON, value);
    res = "Noon position set to: " + String(NoonPos) + " °";
  }
  else if (paramName == "night_pos")
  {
    int value = paramValue.toInt();
    setDayNightPos(NIGHT, value);
    res = "Night position set to: " + String(NightPos) + " °";
  }
  else
  {
    // Paramètre inconnu

    res = "Paramatre unknown,\n";
    res += "Only ther params are reconized:\n";
    res += "*Temperature*, *Humidity*\n";
    res += "`tmax`, `tmin`, `hmax`, `hmin`\n";
    res += "*Wifi*\n";
    res += "`wifi_ssid`, `wifi_password`, `wifi_hostname`, `wifi_ap_mode`, `wifi_dhcp`, `wifi_ip`, `wifi_subnet`, `wifi_gateway`, `wifi_dns0`, `wifi_dns1`\n";
    res += "*MQTT*\n";
    res += "`mqtt_host`, `mqtt_port`, `mqtt_username`, `mqtt_password`, `mqtt_sub`\n";
    res += "*Day Night*\n";
    res += "`day_pos`, `noon_pos`, `night_pos`\n";
  }

  return res;
}

// обработчик сообщений
void newMsg(FB_msg &msg)
{
  if (msg.text.indexOf("are_you_ok") != -1)
  {
    bot.sendMessage("🥰 Yes iam fine");
  }
  else if (msg.text.indexOf("unpin") != -1)
  {
    warning = false;
    bot.unpinAll();
    bot.sendMessage("All message and warnig are unpined");
  }
  else if (msg.text.indexOf("relay1_on") != -1)
  {
    relay_1 = true;
    bot.sendMessage("Relay 1 set to ON");
  }
  else if (msg.text.indexOf("relay1_off") != -1)
  {
    relay_1 = false;
    bot.sendMessage("Relay 1 set to OFF");
  }
  else if (msg.text.indexOf("relay2_on") != -1)
  {
    relay_2 = true;
    bot.sendMessage("Relay 2 set to ON");
  }
  else if (msg.text.indexOf("relay2_off") != -1)
  {
    relay_2 = false;
    bot.sendMessage("Relay 2 set to OFF");
  }
  else if (msg.text.indexOf("relay3_on") != -1)
  {
    relay_3 = true;
    bot.sendMessage("Relay 3 set to ON");
  }
  else if (msg.text.indexOf("relay3_off") != -1)
  {
    relay_3 = false;
    bot.sendMessage("Relay 3 set to OFF");
  }
  else if (msg.text.indexOf("relay4_on") != -1)
  {
    relay_4 = true;
    bot.sendMessage("Relay 4 set to ON");
  }
  else if (msg.text.indexOf("relay4_off") != -1)
  {
    relay_4 = false;
    bot.sendMessage("Relay 4 set to OFF");
  }
  else if (msg.text.indexOf("/day") != -1)
  {
    setDayNight(DAY);
    bot.sendMessage("Set egg to DAY position");
  }
  else if (msg.text.indexOf("/noon") != -1)
  {
    setDayNight(NOON);
    bot.sendMessage("Set egg to NOON position");
  }
  else if (msg.text.indexOf("/night") != -1)
  {
    setDayNight(NIGHT);
    bot.sendMessage("Set egg to NIGHT position");
  }
  else if (msg.text.indexOf("status") != -1)
  {
    String m = "";
    m += "🌡 *Temperature:* `" + String(Temperature) + "` °C\n";
    m += "🌧 *Humidity:* `" + String(Humidity) + "` %\n";
    m += "*R1:* `" + String(relay_1 ? "ON" : "OFF") + "`\n";
    m += "*R2:* `" + String(relay_2 ? "ON" : "OFF") + "`\n";
    m += "*R3:* `" + String(relay_3 ? "ON" : "OFF") + "`\n";
    m += "*R4:* `" + String(relay_4 ? "ON" : "OFF") + "`\n";
    m += "Egg set: `" + String(DayNight == DAY ? "DAY" : (DayNight == NOON ? "NOON" : (DayNight == NIGHT ? "NIGHT" : "?"))) + "`\n";
    bot.sendMessage(m);
  }
  else if (msg.text.indexOf("preferences") != -1)
  {
    String p = "";
    p += "*Temperature MAX:* `" + String(temperature_max) + "` °C\n";
    p += "*Temperature MIN:* `" + String(temperature_min) + "` °C\n";
    p += "*Humidity MAX:* `" + String(humidity_max) + "` %\n";
    p += "*Humidity MIN:* `" + String(humidity_min) + "` %\n";
    p += "*Day Position:* `" + String(DayPos) + "` °\n";
    p += "*Noon Position:* `" + String(NoonPos) + "` °\n";
    p += "*Night Position:* `" + String(NightPos) + "` °\n";

    bot.sendMessage(p);
  }
  else if (msg.text.indexOf("set") != -1)
  {
    bot.sendMessage(precessMsg(msg.text));
  }

  Serial.print(">> ");
  Serial.println(msg.text);
}

void InitTelegram()
{
  bot.setChatID(CHAT_ID);
  bot.attach(newMsg);
  bot.clearServiceMessages(true);
  bot.sendMessage("🫥 Hello! system restarted.");
  bot.pinMessage(bot.lastBotMsg());
  bot.setTextMode(FB_MARKDOWN); // вернуть по умолчанию - FB_TEXT

  // String sticker = F("CAACAgIAAxkBAAEEj8ZiZ9h67kyCKj6ZWNgc1Nn9jMxzvgACLA0AAvb9IUq2Q93aVm1qyCQE");
  // bot.sendSticker(sticker);
}
