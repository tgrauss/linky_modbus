# 🔌 Linky Bridge – Composant ESPHome

Un composant ESPHome modulaire en YAML pour exposer les données téléinfo Linky via Modbus RTU, Modbus TCP, MQTT, REST ou ESP-NOW.  
Compatible avec les contrats BASE, HC/HP, EJP et TEMPO.

---

## 🚀 Installation

Ajoutez ceci à votre configuration ESPHome :

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/<votre-utilisateur>/linky_bridge
    refresh: 0s

packages:
  linky: !include linky_bridge/linky_bridge.yaml
```

---

## ⚙️ Substitutions disponibles

Ces substitutions permettent de personnaliser le composant `linky_bridge.yaml` selon votre matériel et vos besoins. Toutes les valeurs peuvent être surchargées dans votre configuration ESPHome.

### 🔧 Identité

| Substitution        | Description                            | Valeur par défaut |
|---------------------|----------------------------------------|-------------------|
| `name`              | Nom du composant ESPHome               | `linky_bridge`    |

### 🔌 Options activables

| Substitution           | Description                                 | Valeur par défaut |
|------------------------|---------------------------------------------|-------------------|
| `enable_uart2`         | Active le second bus RS485 (`true` / `false`) | `"false"`         |
| `enable_mqtt`          | Active la publication MQTT (`true` / `false`) | `"false"`         |
| `enable_rest`          | Active l’API REST (`true` / `false`)          | `"false"`         |
| `enable_espnow`        | Active la communication ESP-NOW (`true` / `false`) | `"false"`     |
| `enable_modbus_tcp`    | Active le serveur Modbus TCP (`true` / `false`) | `"false"`       |

### 📡 UART TIC

| Substitution        | Description                        | Valeur par défaut |
|---------------------|------------------------------------|-------------------|
| `uart_tic_tx_pin`   | Broche TX pour le bus TIC          | `GPIO17`          |
| `uart_tic_rx_pin`   | Broche RX pour le bus TIC          | `GPIO16`          |

### 🔌 UART RS485 principal

| Substitution              | Description                             | Valeur par défaut |
|---------------------------|-----------------------------------------|-------------------|
| `uart_rs485_tx_pin`       | Broche TX pour RS485 principal          | `GPIO13`          |
| `uart_rs485_rx_pin`       | Broche RX pour RS485 principal          | `GPIO21`          |
| `modbus_flow_control_pin` | Broche de contrôle de flux Modbus RTU   | `GPIO14`          |
| `uart_rs485_baud_rate`    | Baudrate RS485 principal                | `9600`            |
| `uart_rs485_stop_bits`    | Stop bits RS485 principal               | `1`               |
| `uart_rs485_parity`       | Parité RS485 principal (`NONE`, `EVEN`, `ODD`) | `NONE`     |

### 🧪 UART RS485 secondaire (optionnel)

| Substitution                  | Description                             | Valeur par défaut |
|-------------------------------|-----------------------------------------|-------------------|
| `uart_rs485_2_tx_pin`         | Broche TX pour RS485 secondaire         | `GPIO35`          |
| `uart_rs485_2_rx_pin`         | Broche RX pour RS485 secondaire         | `GPIO37`          |
| `modbus2_flow_control_pin`    | Broche de contrôle de flux secondaire   | `GPIO36`          |
| `uart_rs485_2_baud_rate`      | Baudrate RS485 secondaire               | `9600`            |
| `uart_rs485__2_stop_bits`     | Stop bits RS485 secondaire              | `1`               |
| `uart_rs485_2_parity`         | Parité RS485 secondaire                 | `NONE`            |

### 🧮 Adresses Modbus (surchargables)

| Substitution                  |  Description                                      | Adresse par défaut | 
|-------------------------------|--------------------|--------------- -----------------------------------|
| `modbus_address`              | Adresse modbus sur uart1                          | `1`                | 
| `modbus2_address`             | Adresse modbus sur uart2                          | `1`                |

## 🧮 Registres Modbus exposés

Les registres suivants sont exposés en lecture via Modbus RTU ou TCP. Les adresses sont fixes et correspondent aux données issues du compteur Linky via téléinfo.

### 🧮 Registres Modbus

| Adresse   | Type      | Unité | Source TIC     | Description                          |
|-----------|-----------|-------|----------------|--------------------------------------|
| `0`       | U_DWORD   | Wh    | `EAST`         | Énergie totale soutirée              |
| `4`       | U_DWORD   | Wh    | `EAIT`         | Énergie totale injectée              |
| `10`      | U_DWORD   | Wh    | `EASF01`       | Énergie période 1 (HC)               |
| `14`      | U_DWORD   | Wh    | `EASF02`       | Énergie période 2 (HP)               |
| `20`      | U_DWORD   | Wh    | `EASF01`       | Énergie période 1 (EJP Normal)       |
| `24`      | U_DWORD   | Wh    | `EASF02`       | Énergie période 2 (EJP Pointe)       |
| `30`      | U_DWORD   | Wh    | `EASF01`       | Énergie période 1 (BLEU HC)          |
| `34`      | U_DWORD   | Wh    | `EASF02`       | Énergie période 2 (BLEU HP)          |
| `38`      | U_DWORD   | Wh    | `EASF03`       | Énergie période 3 (BLANC HC)         |
| `42`      | U_DWORD   | Wh    | `EASF04`       | Énergie période 1 (BLANC HP)         |
| `46`      | U_DWORD   | Wh    | `EASF05`       | Énergie période 2 (ROUGE HC)         |
| `50`      | U_DWORD   | Wh    | `EASF06`       | Énergie période 3 (ROUGE HP)         |
| `100`     | U_DWORD   | A     | `IRMS1`        | Courant phase 1                      |
| `104`     | U_DWORD   | A     | `IRMS2`        | Courant phase 2                      |
| `108`     | U_DWORD   | A     | `IRMS3`        | Courant phase 3                      |
| `112`     | U_DWORD   | V     | `URMS1`        | Tension phase 1                      |
| `118`     | U_DWORD   | V     | `URMS2`        | Tension phase 2                      |
| `122`     | U_DWORD   | V     | `URMS3`        | Tension phase 3                      |
| `124`     | U_DWORD   | VA    | `SINSTS`       | Puissance apparente instantanée      |
| `128`     | U_DWORD   | VA    | `SMAXSN`       | Puissance max du jour (totale)       |
| `132`     | U_DWORD   | VA    | `PCOUP`        | Puissance de coupure                 |
| `136`     | U_DWORD   | kVA   | `PREF`         | Puissance de référence               |
| `140`     | U_DWORD   | -     | `CCASN`        | Compteur de dépassement              |
| `144`     | U_DWORD   | VA    | `SINST1`       | Puissance phase 1                    |
| `148`     | U_DWORD   | VA    | `SINST2`       | Puissance phase 2                    |
| `152`     | U_DWORD   | VA    | `SINST3`       | Puissance phase 3                    |
| `156`     | U_DWORD   | VA    | `SMAXSN1`      | Puissance max phase 1                |
| `160`     | U_DWORD   | VA    | `SMAXSN2`      | Puissance max phase 2                |
| `164`     | U_DWORD   | VA    | `SMAXSN3`      | Puissance max phase 3                |
| `170`     | STRING(8) | -     | `NGTF`         | Type de contrat                      |
| `174`     | STRING(8) | -     | `LTARF`        | Tarif en cours                       |
| `180`     | U_DWORD   | -     | `NTARF`        | Index tarifaire en cours             |
| `184`     | U_DWORD   | -     | `NJOURF`       | Jour tarifaire actuel                |
| `188`     | U_DWORD   | -     | `NJOURF+1`     | Jour tarifaire prévu demain          |
| `192`     | STRING(8) | -     | `PJOURF+1`     | Profil tarifaire prévu demain        |
| `196`     | STRING(8) | -     | `PPOINTE`      | Jour de pointe prévu demain          |

## ⚙️ Valeurs possibles
Valeurs possibles pour différents registres de type STRING

### ⚙️ NTARF : Index tarifaire en cours HC/HP

| Code | Description |
| 01   | HC          |
| 02   | HP          |

### ⚙️ NTARF : Index tarifaire en cours EJP

| Code | Description |
| 01   | NORMAL      |
| 02   | POINTE      |

### ⚙️ NTARF : Index tarifaire en cours Tempo

| Code | Description |
| 01   | BLEU HC     |
| 02   | BLEU HP     |
| 03   | BLANC HC    |
| 04   | BLANC HP    |
| 05   | ROUGE HC    |
| 06   | ROUGE HP    |

### ⚙️ NJOURF et NJOURF+1 : Jour tarifaire et Jour tarifaire prévu demain

| Code | Description |
| 01   | BLEU        |
| 02   | BLANC       |
| 03   | ROUGE       |

### ⚙️ Valeurs possible pour PJOURF+1

| Description |
| BLEU HC     |
| BLEU HP     |
| BLANC HC    |
| BLANC HP    |
| ROUGE HC    |
| ROUGE HP    |

### ⚙️ Valeurs possible pour PPOINTE

| Code | Description              |
| OUI  | Jour pointe prévu demain |
| NON  | Jour normal prévu demain |

### ⚙️ Valeurs possible pour NGTF (type de contrat)

| Description |
| BASE        |
| HC/HP       |
| EJP         |
| TEMPO       |

### ⚙️ LTARF : tarifaire en cours

| Description |
| BASE        |
| HC          |
| HP          |
| NORMAL      |
| POINTE      |
| BLEU HC     |
| BLEU HP     |
| BLANC HC    |
| BLANC HP    |
| ROUGE HC    |
| ROUGE HP    |

---

## 🧪 Exemple d’intégration avec substitutions

```yaml
substitutions:
  name: mon_linky
  uart_rs485_tx_pin: GPIO1
  uart_rs485_rx_pin: GPIO3
  modbus_flow_control_pin: GPIO4
  enable_mqtt: "true"
  enable_modbus_tcp: "true"
  modbus_easf01_addr: "20"
  modbus_sinsts_addr: "130"

packages:
  linky: !include linky_bridge/linky_bridge.yaml
```

---

## 📎 À propos

Ce composant est conçu pour être simple à intégrer, modulaire et compatible avec les superviseurs industriels, Home Assistant, Domoticz, ou tout autre système Modbus/MQTT.  
Pour toute contribution ou suggestion, ouvrez une issue ou une pull request sur le dépôt GitHub.

## 🛠️ Utilisation du composant

### 📁 Structure du dépôt

Le composant est organisé dans un dossier `linky_bridge/` contenant :

- `linky_bridge.yaml` : le fichier principal à inclure dans votre configuration ESPHome

---

### 📦 Intégration dans ESPHome

1. **Copiez le dossier `linky_bridge/`** dans le dossier `config/` de votre projet ESPHome (là où se trouvent vos fichiers `.yaml`).

2. **Ajoutez les substitutions nécessaires** dans votre fichier principal `.yaml` :

```yaml
substitutions:
  name: linky_bridge
  enable_modbus_tcp: "true"
  enable_mqtt: "true"
  uart_tic_rx_pin: GPIO16
  uart_tic_tx_pin: GPIO17
  uart_rs485_tx_pin: GPIO13
  uart_rs485_rx_pin: GPIO21
  modbus_flow_control_pin: GPIO14
```

3. **Incluez le composant dans votre configuration** :

```yaml
packages:
  linky: !include linky_bridge/linky_bridge.yaml
```

4. **Compilez et flashez votre firmware** :

- Depuis l’interface web ESPHome : cliquez sur “INSTALL” ou “UPLOAD”.
- En ligne de commande :

```bash
esphome run mon_linky.yaml
```

---

### ⚠️ Prérequis matériels

- Un compteur Linky en mode standard
- Un adaptateur téléinfo (TTL ou opto-isolé)
- Un ESP32 ou ESP8266 compatible avec UART et Modbus
- Optionnel : convertisseur RS485 si Modbus RTU est activé


---
