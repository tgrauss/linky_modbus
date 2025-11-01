#include "linky-bridge.h"

void LinkyBridge::setup() {
    ESP_LOGI("linky_bridge", "LinkyBridge setup complete");
}

void LinkyBridge::loop() {
    // Exemple : log des valeurs
    if (papp_ && iinst_ && base_) {
        ESP_LOGD("linky_bridge", "PAPP: %.1f VA, IINST: %.1f A, BASE: %.1f Wh",
                 papp_->state, iinst_->state, base_->state);
    }
}
