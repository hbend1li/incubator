#!/usr/bin/python3
# -*- coding: utf-8 -*-

import paho.mqtt.client as mqtt
import sqlite3
from time import time

MQTT_HOST = 'broker.emqx.io'
MQTT_PORT = 1883
MQTT_CLIENT_ID = 'Python MQTT client'
MQTT_USER = ''
MQTT_PASSWORD = ''
TOPIC = 'Ng3cKKI95qx3QI5pFTo2fCHK/#'

DATABASE_FILE = 'iot.db'

def on_connect(mqtt_client, user_data, flags, conn_result):
    mqtt_client.subscribe(TOPIC)

def on_message(mqtt_client, user_data, message):
    payload = message.payload.decode('utf-8')

    db_conn = user_data['db_conn']
    sql = 'INSERT INTO mqtt (topic, payload, created_at) VALUES (?, ?, ?)'
    cursor = db_conn.cursor()
    cursor.execute(sql, (message.topic, payload, int(time())))
    db_conn.commit()
    cursor.close()

def main():
    db_conn = sqlite3.connect(DATABASE_FILE)
    sql = """
    CREATE TABLE IF NOT EXISTS mqtt (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        topic TEXT NOT NULL,
        payload TEXT NOT NULL,
        created_at INTEGER NOT NULL
    )
    """
    cursor = db_conn.cursor()
    cursor.execute(sql)
    cursor.close()

    mqtt_client = mqtt.Client(MQTT_CLIENT_ID)
    mqtt_client.username_pw_set(MQTT_USER, MQTT_PASSWORD)
    mqtt_client.user_data_set({'db_conn': db_conn})

    mqtt_client.on_connect = on_connect
    mqtt_client.on_message = on_message

    mqtt_client.connect(MQTT_HOST, MQTT_PORT)
    mqtt_client.loop_forever()

main()