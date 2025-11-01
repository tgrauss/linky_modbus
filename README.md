# linky-bridge for ESPHome
`linky_bridge` is an ESPHome component that reads Linky smart meter data via Téléinfo and exposes it through Modbus RTU, Modbus TCP (optional), ESP-NOW (optional), and API/MQTT/Home Assistant.

## Features

- Reads PAPP, IINST, BASE from Linky via UART
- Exposes data as Modbus registers
- Compatible with SmartEVSE, PLCs, and other Modbus masters
- Optional integration with MQTT, Home Assistant, ESP-NOW

## Example YAML

See `linky_bridge.yaml` for a full integration example.

