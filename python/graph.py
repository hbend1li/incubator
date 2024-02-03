#!/usr/bin/python3
# -*- coding: utf-8 -*-

import requests
import csv
import matplotlib.pyplot as plt
import datetime

# # Téléchargement du fichier CSV
response = requests.get("http://esp32.local/data.csv")
with open("data.csv", "wb") as f:
    f.write(response.content)

# Lecture du fichier CSV
with open("data.csv", "r") as f:
    reader = csv.reader(f, delimiter=",")
    # Ignorer la première ligne (en-tête)
    next(reader, None)
 
    # Récupération des données
    time = []
    temperature = []
    humidity = []
    missing_time = []
    #missing_temperature = []
    #last = 0
    for row in reader:
        if row[0] != '0' and row[1] != '--' and row[2] != '--':
            time.append(int(row[0]))
            temperature.append(float(row[1]))
            humidity.append(float(row[2]))
            #last = row[1]

            t = float(row[1])
            if t > 39 or t < 36.5:
                plt.scatter(datetime.datetime.fromtimestamp(int(row[0])), t, color="r")
                pass
            h = float(row[2])
            if h > 50 or h < 30:
                plt.scatter(datetime.datetime.fromtimestamp(int(row[0])), h, color="b")
                pass

        else:
            if row[0] != '0':
                missing_time.append(int(row[0]))
                #missing_temperature.append(float(last))

    time = [datetime.datetime.fromtimestamp(t) for t in time]
    missing_time = [datetime.datetime.fromtimestamp(t) for t in missing_time]

plt.scatter(time[0], 0, color="r")
plt.plot(time, temperature, label="Température °C", color="orange")
plt.plot(time, humidity, label="Humidité %", color="blue")
for time_value in missing_time:
    plt.axvline(time_value, color="red", linewidth=1)
plt.xlabel("Temps (datetime)")
#plt.ylabel("Température °C / Humidité %")
plt.legend()
plt.show()