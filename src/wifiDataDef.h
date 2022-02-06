#define wifiMaxSsidLen 32
#define wifiMaxPasswordLen 63
struct wifiData
{
    char ssid[wifiMaxSsidLen];
    char password[wifiMaxPasswordLen];
};