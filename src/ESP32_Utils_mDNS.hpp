void InitMDNS()
{
    if (!MDNS.begin(WIFI_HOSTNAME))
    {
        Serial.println("Error iniciando mDNS");
    }
    Serial.println("mDNS iniciado");
}