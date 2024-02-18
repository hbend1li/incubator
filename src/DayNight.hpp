#define PIN_SG90 33 // Output pin used
    Servo myservo;  // create servo object to control a servo

#define DAY 0
#define NOON 1
#define NIGHT 2

// bool DayNight = Day;
// int DayPos = 0;
// int NoonPos = 0;
// int NightPos = 0;

void setDayNightPos(int day_night, int value)
{
  DayNight = day_night;
  if (DayNight == DAY)
  {
    DayPos = value;
    preferences.putInt("DayPos", DayPos);
  }
  else if (DayNight == NOON)
  {
    NoonPos = value;
    preferences.putInt("NoonPos", NoonPos);
  }
  else if (DayNight == NIGHT)
  {
    NightPos = value;
    preferences.putInt("NightPos", NightPos);
  }
}

void setDayNight(int8_t day_night)
{
  DayNight = day_night;
  preferences.putInt("DayNight", DayNight);

  int NewPos = 0;

  if (DayNight == DAY)
    NewPos = DayPos;
  else if (DayNight == NOON)
    NewPos = NoonPos;
  else if (DayNight == NIGHT)
    NewPos = NightPos;

  if (NewPos > LastPos)
  {
    for (int i = LastPos; i < NewPos; i++)
    {
      myservo.write(i);
      delay(10);
    }
  }
  else if (NewPos < LastPos)
  {
    for (int i = LastPos; i > NewPos; i--)
    {
      myservo.write(i);
      delay(10);
    }
  }
  LastPos = NewPos;
  CloudSend("[Event]", "DayNight, Egg set to " + String(DayNight == DAY ? "DAY" : (DayNight == NOON ? "NOON" : (DayNight == NIGHT ? "NIGHT" : "?"))));
}

void InitDayNight()
{
  myservo.attach(PIN_SG90);
  setDayNight(DayNight);
  CloudSend("[Info]", "SG90 Init");
}