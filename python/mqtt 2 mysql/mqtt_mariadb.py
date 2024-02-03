#!/usr/bin/python3
# -*- coding: utf-8 -*-

import paho.mqtt.client as mqtt
import pymysql
from time import time

# -- iot.mqtt definition

# CREATE TABLE `mqtt` (
#   `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
#   `topic` text NOT NULL,
#   `payload` text NOT NULL,
#   `created_at` datetime DEFAULT current_timestamp(),
#   PRIMARY KEY (`id`)
# ) ENGINE=InnoDB AUTO_INCREMENT=63 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

# MariaDB database settings
MARIADB_HOST = '10.0.10.1'
MARIADB_USER = 'root'
MARIADB_PASSWORD = '#Zline159'
MARIADB_DATABASE = 'iot'

# MQTT settings
MQTT_HOST = 'broker.emqx.io'
MQTT_PORT = 1883
MQTT_CLIENT_ID = 'Python MQTT client'
MQTT_USER = ''
MQTT_PASSWORD = ''
TOPIC = 'Ng3cKKI95qx3QI5pFTo2fCHK/#'

def on_connect(mqtt_client, user_data, flags, conn_result):
    mqtt_client.subscribe(TOPIC)

def on_message(mqtt_client, user_data, message):
    payload = message.payload.decode('utf-8')

    db_conn = user_data['db_conn']
    sql = 'INSERT INTO mqtt (topic, payload) VALUES (%s, %s)'
    with db_conn.cursor() as cursor:
        cursor.execute(sql, (message.topic, payload))
        db_conn.commit()

def main():
    db_conn = pymysql.connect(host=MARIADB_HOST, user=MARIADB_USER, password=MARIADB_PASSWORD, database=MARIADB_DATABASE)

    mqtt_client = mqtt.Client(MQTT_CLIENT_ID)
    mqtt_client.username_pw_set(MQTT_USER, MQTT_PASSWORD)
    mqtt_client.user_data_set({'db_conn': db_conn})

    mqtt_client.on_connect = on_connect
    mqtt_client.on_message = on_message

    mqtt_client.connect(MQTT_HOST, MQTT_PORT)
    mqtt_client.loop_forever()

main()


