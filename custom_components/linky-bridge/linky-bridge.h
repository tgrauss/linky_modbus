#include "esphome.h"

class LinkyBridge : public Component {
public:
    void setup() override;
    void loop() override;

    void set_papp(Sensor *sensor) { papp_ = sensor; }
    void set_iinst(Sensor *sensor) { iinst_ = sensor; }
    void set_base(Sensor *sensor) { base_ = sensor; }

private:
    Sensor *papp_;
    Sensor *iinst_;
    Sensor *base_;
};
