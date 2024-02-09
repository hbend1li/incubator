![incubator](incubator.png)
# Incubator

are_you_ok - to know status of module
status - Request current Temperature, Humidity, Relay Status  
relay1_on - Relay1 ON  
relay1_off - Relay1 OFF  
relay2_on - Relay2 ON  
relay2_off - Relay2 OFF  
relay3_on - Relay3 ON  
relay3_off - Relay3 OFF  
relay4_on - Relay4 ON  
relay4_off - Relay4 OFF  
preferences - Get request current Temperature, Humidity, ...  
set - Set preferences to t_max, t_min, h_max, h_min, ...  


#### old partition.csv
```
# Name,   Type, SubType, Offset,  Size, Flags
nvs,      data, nvs,     0x9000,  0x5000,
otadata,  data, ota,     0xe000,  0x2000,
app0,     app,  ota_0,   0x10000, 0x300000,
spiffs,   data, spiffs,  0x310000,0xE0000,
```
