#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
import matplotlib.pyplot as plt
import pymysql
import matplotlib.animation as animation
from matplotlib.text import OffsetFrom
import datetime


# MariaDB database settings
MARIADB_HOST = '10.0.10.1'
MARIADB_USER = 'root'
MARIADB_PASSWORD = '#Zline159'
MARIADB_DATABASE = 'iot'

def fetch_data():
    db_conn = pymysql.connect(host=MARIADB_HOST, 
                              user=MARIADB_USER, 
                              password=MARIADB_PASSWORD, 
                              database=MARIADB_DATABASE)
    cursor = db_conn.cursor()

    # get 1H

    if (len(sys.argv)>1):
        cursor.execute("SELECT created_at, payload, topic, id FROM mqtt WHERE created_at > DATE_SUB(NOW(), INTERVAL "+sys.argv[1]+" HOUR)")
    else:
        cursor.execute("SELECT created_at, payload, topic, id FROM mqtt WHERE created_at > DATE_SUB(NOW(), INTERVAL 1 HOUR)")
        #cursor.execute("SELECT created_at, payload, topic, id FROM mqtt")

    #cursor.execute("SELECT created_at, payload, topic, id FROM (SELECT * FROM mqtt ORDER BY id DESC LIMIT 10000) sub ORDER BY id ASC")
    results = cursor.fetchall()
    db_conn.close()
    return results

def main():

    plt.style.use('bmh')
        #     'Solarize_Light2', 
        #     '_classic_test_patch', 
        #     '_mpl-gallery', 
        #     '_mpl-gallery-nogrid', 
        #     'bmh', 
        #     'classic', 
        #     'dark_background', 
        #     'fast', 
        #     'fivethirtyeight', 
        #     'ggplot', 
        #     'grayscale', 
        #     'seaborn', 
        #     'seaborn-bright', 
        #     'seaborn-colorblind', 
        #     'seaborn-dark', 
        #     'seaborn-dark-palette', 
        #     'seaborn-darkgrid', 
        #     'seaborn-deep', 
        #     'seaborn-muted', 
        #     'seaborn-notebook', 
        #     'seaborn-paper', 
        #     'seaborn-pastel', 
        #     'seaborn-poster', 
        #     'seaborn-talk', 
        #     'seaborn-ticks', 
        #     'seaborn-white', 
        #     'seaborn-whitegrid', 
        #     'tableau-colorblind10'

    fig, axes = plt.subplots(nrows=2, figsize=(30, 30))

    timeT = []
    temperature = []
    timeH = []
    humidity = []
    minH = 100
    minT = 100
    results = fetch_data()

    for row in results:
        #print(row)
        if ("Temperature" in row[2]):
            x = row[0]
            t = float(row[1])
            timeT.append(x)
            temperature.append(t)
            if (minT > t):
                minT = t

        elif ("Humidity" in row[2]):
            x = row[0]
            h = float(row[1])
            timeH.append(x)
            humidity.append(h)
            if (minH > h):
                minH = h

        # elif ("r1" in row[2]):
        #     if (row[1]=="0"):
        #         plt.axvline(timeT[-1], linestyle=':', color='red', lw=1, alpha=0.3)

        #     if (row[1]=="1"):
        #         plt.axvline(timeT[-1], linestyle=':', color='red', lw=1, alpha=0.7)

        elif ("r2" in row[2]):
            if (row[1]=="0"):
                axes[1].axvline(timeT[-1], linestyle=':', color='red', lw=1, alpha=0.3)

            if (row[1]=="1"):
                axes[1].axvline(timeT[-1], linestyle=':', color='red', lw=1, alpha=0.7)

        elif ("r3" in row[2]):
            if (row[1]=="0"):
                axes[1].axvline(timeT[-1], linestyle=':', color='green', lw=1, alpha=0.3)

            if (row[1]=="1"):
                axes[1].axvline(timeT[-1], linestyle=':', color='green', lw=1, alpha=0.7)

        elif ("r4" in row[2]):
            # if (row[1]=="0"):
            #     axes[0].axvline(timeT[-1], linestyle=':', color='blue', lw=1, alpha=0.2)
            #     axes[0].annotate(
            #         f'R4',
            #         xy=(timeH[-1],humidity[-1]), xycoords='data',
            #         xytext=(timeH[-1],humidity[-1]),
            #         textcoords='data',
            #         color="w",
            #         va="center",
            #         ha="center",
            #         bbox=dict(boxstyle="round4", fc="blue", alpha=0.2, pad=0.5 )
            #     )

            # if (row[1]=="1"):
            #     axes[0].axvline(timeT[-1], linestyle=':', color='blue', lw=1, alpha=1)
            #     axes[0].annotate(
            #         f'R4',
            #         xy=(timeH[-1],humidity[-1]), xycoords='data',
            #         xytext=(timeH[-1],humidity[-1]),
            #         textcoords='data',
            #         color="w",
            #         va="center",
            #         ha="center",
            #         bbox=dict(boxstyle="round4", fc="blue", alpha=0.8, pad=0.5 )
            #     )
            pass
        
        elif ("start" in row[2]):
            axes[0].axvline(timeT[-1], linestyle='-', color='red', lw=1, alpha=1)
            axes[1].axvline(timeT[-1], linestyle='-', color='red', lw=1, alpha=1)

            #offset_from = OffsetFrom(an1, (0.5, 0))
            #xp = timeT[-1] +  datetime.timedelta(minutes=15)
            axes[1].annotate(
                f'system boot',
                xy=(timeT[-1],minT), xycoords='data',
                xytext=(timeT[-1],minT),
                textcoords='data',
                color="w",
                va="center",
                ha="center",
                rotation=90,
                bbox=dict(boxstyle="round4", fc="r", pad=0.8 ),
                arrowprops=dict(
                    #arrowstyle="]->",
                    #connectionstyle="arc3,rad=-0.2",
                    facecolor='black', 
                    shrink=0.05
                )
            )


    sc = axes[0].fill_between(timeH, minH, humidity, alpha=0.05, color="blue",linewidth=2)
    sc = axes[0].scatter(timeH, humidity, c=humidity, cmap='winter', s=2,label="Humidity % ["+str(len(timeH))+"]")
    cbar = fig.colorbar(sc, ax=axes[0], pad=0.01)
    cbar.set_label(label=f'Humidity %', fontsize=15, labelpad=10)
    axes[0].set_xlim(timeT[0], timeT[-1])
    axes[0].legend()

    sc = axes[1].fill_between(timeT, minT, temperature, alpha=0.1, color="orange", linewidth=2)
    sc = axes[1].scatter(timeT, temperature, c=temperature, cmap='plasma', s=2,label="Température °c ["+str(len(timeT))+"]")
    cbar = fig.colorbar(sc, ax=axes[1], pad=0.01)
    cbar.set_label(label=f'Température °c', fontsize=15, labelpad=10)
    axes[1].set_xlim(timeT[0], timeT[-1])
    axes[1].legend()


    
    # plt.xlim(timeT[0], timeT[-1])
    #plt.xlabel("Temps (datetime)")

    #plt.legend()
    #plt.legend(['First line', 'Second line', 'First line', 'Second line'])
    plt.tight_layout(pad=5)
    plt.show()

if __name__ == "__main__":
    main()