#include <FastBot.h>

#define BOT_TOKEN "6890372375:AAGXAl_3nYDXUgAfaPFoHN6ZF6QDbl_i7bM"
#define CHAT_ID "-4144220204"

FastBot bot(BOT_TOKEN);

// обработчик сообщений
void newMsg(FB_msg &msg)
{
  if (msg.text == "/are_you_ok@incub_bot")
  {
    bot.sendMessage("🥰 Yes iam fine");
  }

  if (msg.text == "unpin@incub_bot" || msg.text == "/unpin@incub_bot")
  {
    warning = false;
    bot.unpinAll();
    bot.sendMessage("All message and warnig are unpined");
  }

  if (msg.text == "/relay1_on@incub_bot")
  {
    relay_1 = true;
    bot.sendMessage("Relay 1 set to ON");
  }

  if (msg.text == "/relay1_off@incub_bot")
  {
    relay_1 = false;
    bot.sendMessage("Relay 1 set to OFF");
  }

  if (msg.text == "/relay2_on@incub_bot")
  {
    relay_2 = true;
    bot.sendMessage("Relay 2 set to ON");
  }

  if (msg.text == "/relay2_off@incub_bot")
  {
    relay_2 = false;
    bot.sendMessage("Relay 2 set to OFF");
  }

  if (msg.text == "/relay3_on@incub_bot")
  {
    relay_3 = true;
    bot.sendMessage("Relay 3 set to ON");
  }

  if (msg.text == "/relay3_off@incub_bot")
  {
    relay_3 = false;
    bot.sendMessage("Relay 3 set to OFF");
  }

  if (msg.text == "/relay4_on@incub_bot")
  {
    relay_4 = true;
    bot.sendMessage("Relay 4 set to ON");
  }

  if (msg.text == "/relay4_off@incub_bot")
  {
    relay_4 = false;
    bot.sendMessage("Relay 4 set to OFF");
  }

  if (msg.text == "/status@incub_bot")
  {
    String m = "🌡 *Temperature:* `";
    m += String(Temperature);
    m += "` °C\n🌧 *Humidity:* `";
    m += String(Humidity);
    m += "` %\n*R1:* ";
    m += relay_1 ? "`ON`" : "`OFF`";
    m += "\n*R2:* ";
    m += relay_2 ? "`ON`" : "`OFF`";
    m += "\n*R3:* ";
    m += relay_3 ? "`ON`" : "`OFF`";
    m += "\n*R4:* ";
    m += relay_4 ? "`ON`" : "`OFF`";
    bot.sendMessage(m);
  }

  if (msg.text == "/preferences@incub_bot")
  {
    String p = "*Temperature MAX:* `";
    p += String(temperature_max);
    p += "` °C\n*Temperature MIN:* `";
    p += String(temperature_min);
    p += "` °C\n*Humidity MAX:* `";
    p += String(humidity_max);
    p += "` %\n*Humidity MIN:* `";
    p += String(humidity_min);
    p += "` %";
    bot.sendMessage(p);
  }

  if (msg.text == "/unpin@incub_bot")
  {
    bot.unpinAll();
  }

  // if (msg.text == "/restart" || msg.text == "/reboot")
  // {
  //   ESP.restart();
  // }

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
