# 🔌 Linky Bridge – Composant ESPHome

Un composant ESPHome modulaire en YAML pour exposer les données téléinfo Linky via Modbus RTU.  
Compatible avec les contrats BASE, HC/HP, EJP et TEMPO.

---

## ⚙️ Substitutions disponibles

Ces substitutions permettent de personnaliser le composant `linky_bridge.yaml` selon votre matériel et vos besoins. Toutes les valeurs peuvent être surchargées dans votre configuration ESPHome.

### 🔧 Identité

| Substitution        | Description                            | Valeur par défaut |
|---------------------|----------------------------------------|-------------------|
| `name`              | Nom du composant ESPHome               | `linky-bridge`    |

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

### 🧪 UART RS485 secondaire

| Substitution                  | Description                             | Valeur par défaut |
|-------------------------------|-----------------------------------------|-------------------|
| `uart_rs485_2_tx_pin`         | Broche TX pour RS485 secondaire         | `GPIO38`          |
| `uart_rs485_2_rx_pin`         | Broche RX pour RS485 secondaire         | `GPIO40`          |
| `modbus2_flow_control_pin`    | Broche de contrôle de flux secondaire   | `GPIO39`          |
| `uart_rs485_2_baud_rate`      | Baudrate RS485 secondaire               | `9600`            |
| `uart_rs485__2_stop_bits`     | Stop bits RS485 secondaire              | `1`               |
| `uart_rs485_2_parity`         | Parité RS485 secondaire                 | `NONE`            |

### 🧮 Adresses Modbus (surchargables)

| Substitution                  |  Description                                      | Adresse par défaut | 
|-------------------------------|---------------------------------------------------|--------------------|
| `modbus_address`              | Adresse modbus sur uart1                          | `1`                | 
| `modbus2_address`             | Adresse modbus sur uart2                          | `1`                |

## 🧮 Registres Modbus exposés

Les registres suivants sont exposés en lecture via Modbus RTU. Les adresses sont fixes et correspondent aux données issues du compteur Linky via téléinfo.

### 🧮 Registres Modbus

| Adresse   | Type        | Unité   | Source TIC     | Description                            |
|-----------|-------------|---------|----------------|----------------------------------------|
| `0`       | `U_DWORD`   | `Wh`    | `EAST`         | Énergie totale soutirée                |
| `2`       | `U_DWORD`   | `Wh`    | `EAIT`         | Énergie totale injectée                |
| `4`       | `U_DWORD`   | `Wh`    | `EASF01`       | Énergie période 1 (`HC`)               |
| `6`       | `U_DWORD`   | `Wh`    | `EASF02`       | Énergie période 2 (`HP`)               |
| `8`       | `U_DWORD`   | `Wh`    | `EASF01`       | Énergie période 1 (`EJP Normal`)       |
| `10`      | `U_DWORD`   | `Wh`    | `EASF02`       | Énergie période 2 (`EJP Pointe`)       |
| `12`      | `U_DWORD`   | `Wh`    | `EASF01`       | Énergie période 1 (`BLEU HC`)          |
| `14`      | `U_DWORD`   | `Wh`    | `EASF02`       | Énergie période 2 (`BLEU HP`)          |
| `16`      | `U_DWORD`   | `Wh`    | `EASF03`       | Énergie période 3 (`BLANC HC`)         |
| `18`      | `U_DWORD`   | `Wh`    | `EASF04`       | Énergie période 1 (`BLANC HP`)         |
| `20`      | `U_DWORD`   | `Wh`    | `EASF05`       | Énergie période 2 (`ROUGE HC`)         |
| `22`      | `U_DWORD`   | `Wh`    | `EASF06`       | Énergie période 3 (`ROUGE HP`)         |
| `24`      | `U_WORD`    | `A`     | `IRMS1`        | Courant phase 1                        |
| `25`      | `U_WORD`    | `A`     | `IRMS2`        | Courant phase 2                        |
| `26`      | `U_WORD`    | `A`     | `IRMS3`        | Courant phase 3                        |
| `27`      | `U_WORD`    | `V`     | `URMS1`        | Tension phase 1                        |
| `28`      | `U_WORD`    | `V`     | `URMS2`        | Tension phase 2                        |
| `29`      | `U_WORD`    | `V`     | `URMS3`        | Tension phase 3                        |
| `30`      | `U_DWORD`   | `VA`    | `SINSTS`       | Puissance apparente instantanée        |
| `32`      | `U_DWORD`   | `VA`    | `SINST1`       | Puissance phase 1                      |
| `34`      | `U_DWORD`   | `VA`    | `SINST2`       | Puissance phase 2                      |
| `36`      | `U_DWORD`   | `VA`    | `SINST3`       | Puissance phase 3                      |
| `38`      | `U_DWORD`   | `VA`    | `SMAXSN`       | Puissance max du jour (totale)         |
| `40`      | `U_DWORD`   | `VA`    | `SMAXSN1`      | Puissance max phase 1                  |
| `42`      | `U_DWORD`   | `VA`    | `SMAXSN2`      | Puissance max phase 2                  |
| `44`      | `U_DWORD`   | `VA`    | `SMAXSN3`      | Puissance max phase 3                  |
| `46`      | `U_DWORD`   | `VA`    | `PCOUP`        | Puissance de coupure                   |
| `48`      | `U_WORD`    | `kVA`   | `PREF`         | Puissance de référence                 |
| `49`      | `U_DWORD`   | `-`     | `CCASN`        | Compteur de dépassement                |
| `50`      | `U_WORD`    | `-`     | `NTARF`        | Index tarifaire en cours               |
| `51`      | `U_WORD`    | `-`     | `NJOURF`       | Jour tarifaire actuel                  |
| `52`      | `U_WORD`    | `-`     | `NJOURF+1`     | Jour tarifaire prévu demain            |
| `53`      | `U_QWORD`   | `-`     | `NGTF`         | Type de contrat                        |
| `57`      | `U_QWORD`   | `-`     | `LTARF`        | Tarif en cours                         |
| `61`      | `U_QWORD`   | `-`     | `PJOURF+1`     | Profil tarifaire prévu demain          |
| `65`      | `U_QWORD`   | `-`     | `PPOINTE`      | Jour de pointe prévu demain            |

## ⚙️ Valeurs possibles
Valeurs possibles pour différents registres de type STRING

### ⚙️ NTARF : Index tarifaire en cours HC/HP

| Code   | Description |
|--------|-------------|
| `01`   | HC          |
| `02`   | HP          |

### ⚙️ NTARF : Index tarifaire en cours EJP

| Code   | Description |
|--------|-------------|
| `01`   | NORMAL      |
| `02`   | POINTE      |

### ⚙️ NTARF : Index tarifaire en cours Tempo

| Code   | Description |
|--------|-------------|
| `01`   | BLEU HC     |
| `02`   | BLEU HP     |
| `03`   | BLANC HC    |
| `04`   | BLANC HP    |
| `05`   | ROUGE HC    |
| `06`   | ROUGE HP    |

### ⚙️ NJOURF et NJOURF+1 : Jour tarifaire et Jour tarifaire prévu demain

| Code   | Description |
|--------|-------------|
| `01`   | BLEU        |
| `02`   | BLANC       |
| `03`   | ROUGE       |

### ⚙️ Valeurs possible pour PJOURF+1

| Description   |
|---------------|
| `BLEU HC`     |
| `BLEU HP`     |
| `BLANC HC`    |
| `BLANC HP`    |
| `ROUGE HC`    |
| `ROUGE HP`    |

### ⚙️ Valeurs possible pour PPOINTE

| Code   | Description              |
|--------|--------------------------|
| `OUI`  | Jour pointe prévu demain |
| `NON`  | Jour normal prévu demain |

### ⚙️ Valeurs possible pour NGTF (type de contrat)

| Description   |
|---------------|
| `BASE`        |
| `HC/HP`       |
| `EJP`         |
| `TEMPO`       |

### ⚙️ LTARF : tarifaire en cours

| Description   |
|---------------|
| `BASE`        |
| `HC`          |
| `HP`          |
| `NORMAL`      |
| `POINTE`      |
| `BLEU HC`     |
| `BLEU HP`     |
| `BLANC HC`    |
| `BLANC HP`    |
| `ROUGE HC`    |
| `ROUGE HP`    |

---

## 🧪 Exemple d’intégration avec substitutions
Téléchargez le composant et notemment le dossier `linky_bridge`. Créez un fichier secrets.yaml pour stocker vos mots de passe. Voir l'exemple dans le dossier `test` pour un exemple pratique.

```yaml
substitutions:
  name: linky-bridge
  uart_tic_rx_pin: GPIO16
  uart_tic_tx_pin: GPIO17
  uart_rs485_tx_pin: GPIO13
  uart_rs485_rx_pin: GPIO21
  modbus_flow_control_pin: GPIO14

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
  name: linky-bridge
  uart_tic_rx_pin: GPIO16
  uart_tic_tx_pin: GPIO17
  uart_rs485_tx_pin: GPIO13
  uart_rs485_rx_pin: GPIO21
  modbus_flow_control_pin: GPIO14
```
3. **Créer un fichier `secrets.yaml` à la racine de votre projet (avec votre fichier yaml). Il va contenir vos mots de passe

```yaml
wifi_ssid: "MonSSID"
wifi_password: "MonMotDePasse"
ota_pass: "qwerty123456"

```

3. **Incluez le composant dans votre configuration** :

```yaml
packages:
  linky: !include linky_bridge/linky_bridge.yaml
```

4. **Compilez et flashez votre firmware** :
Si vous souhaitez compiler et flasher le firmware en ligne de commande, voici les étapes recommandées :

### 📦 Prérequis

- Python 3.10 ou plus
- `pip` installé
- Accès au port série USB (ex. `/dev/ttyUSB0` ou `COM3`)

---

### 🐍 Création d’un environnement virtuel

```bash
# Créer un dossier de projet
mkdir mon_esphome
cd mon_esphome

# Créer un environnement virtuel Python
python3 -m venv .venv

# Activer l’environnement
source .venv/bin/activate  # Linux/macOS
# .venv\Scripts\activate    # Windows

# Installer ESPHome
pip install esphome
```

---

### ⚙️ Compilation et flash

Placez votre fichier `mon_linky.yaml` dans le dossier, puis lancez :

```bash
esphome run mon_linky.yaml
```

ESPHome va :

- Compiler le firmware
- Flasher l’ESP32/ESP8266 via USB
- Ou proposer une mise à jour OTA si déjà installé

---

### 🔁 Mise à jour

Pour mettre à jour ESPHome :

```bash
pip install --upgrade esphome
```

---

### 🧹 Désactivation de l’environnement

Quand vous avez terminé :

```bash
deactivate
```


---

### ⚠️ Prérequis matériels

- Un compteur Linky en mode standard
- Un adaptateur téléinfo (TTL ou opto-isolé)
- Un ESP32 ou ESP8266 compatible avec UART et Modbus
- Optionnel : convertisseur RS485 si Modbus RTU est activé


###  ⚠️ Matériel de référence

Dans le dossier schematic, vous trouverez :
- Le schéma au format PDF du module électronique de référence. La carte est prévue de s'installer dans un boitier plastique 2 modules au format rail DIN
- La nomenclature des des composants
- Le fichier de fabrication Gerber

---
