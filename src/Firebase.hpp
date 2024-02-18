#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

// Insert Firebase project API Key
#define API_KEY "AIzaSyCcvoVBhYM-eG_tcM7Vgq_MTWzkJZN46Xs"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://incubator-d50d5-default-rtdb.europe-west1.firebasedatabase.app"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "hbendali@ya.ru"
#define USER_PASSWORD "yJuIL0IbcU3AmmAz"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Database main path (to be updated in setup with the user UID)
String databasePath;
// Database child nodes
String tempPath = "/temperature";
String humPath = "/humidity";
String presPath = "/pressure";
String timePath = "/timestamp";

// Parent Node (to be updated in every loop)
String parentPath;

int timestamp;
FirebaseJson Fjson;

unsigned long sendDataPrevMillis = 0;
int intValue;
float floatValue;
bool signupOK = false;

void FireSend()
{
    if (Firebase.ready())
    {
        // Get current timestamp
        timestamp = getTime();
        parentPath = databasePath + "/" + String(timestamp);
        Fjson.set(tempPath.c_str(), String(Temperature));
        Fjson.set(humPath.c_str(), String(Humidity));
        Fjson.set(timePath, String(timestamp));
        Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &Fjson) ? "ok" : fbdo.errorReason().c_str());
    }
}

void InitFirebase()
{
    // Assign the api key (required)
    config.api_key = API_KEY;

    // Assign the user sign in credentials
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    // Assign the RTDB URL (required)
    config.database_url = DATABASE_URL;

    Firebase.reconnectWiFi(true);
    fbdo.setResponseSize(4096);

    // Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    // Assign the maximum retry of token generation
    config.max_token_generation_retry = 5;

    // Initialize the library with the Firebase authen and config
    Firebase.begin(&config, &auth);

    // /* Sign up */
    // if (Firebase.signUp(&config, &auth, "", ""))
    // {
    //     Serial.println("ok");
    //     signupOK = true;
    // }
    // else
    // {
    //     Serial.printf("%s\n", config.signer.signupError.message.c_str());
    // }

    // /* Assign the callback function for the long running token generation task */
    // config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    // Firebase.begin(&config, &auth);
    // Firebase.reconnectWiFi(true);

    // Getting the user UID might take a few seconds
    Serial.println("Getting User UID");
    while ((auth.token.uid) == "")
    {
        Serial.print('.');
        delay(1000);
    }
    // Print user UID
    uid = auth.token.uid.c_str();
    Serial.print("User UID: ");
    Serial.println(uid);

    // Update database path
    databasePath = "/UsersData/" + uid + "/readings";
}