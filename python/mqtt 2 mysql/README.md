# mqtt to mariadb

## Create `mqtt_mariadb.py` as service
```sh
sudo su
pip3 install paho-mqtt
pip3 install pymysql
cp mqtt_mariadb.service /etc/systemd/system/mqtt_mariadb.service
cp mqtt_mariadb.py /usr/bin/mqtt_mariadb.py
chmod +x /usr/bin/mqtt_mariadb.py
systemctl enable mqtt_mariadb.service
systemctl start mqtt_mariadb.service
```