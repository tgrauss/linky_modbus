# 🔌 Linky Bridge – Composant ESPHome

Un composant ESPHome modulaire en YAML pour exposer les données téléinfo Linky via Modbus RTU.
Compatible avec les contrats BASE, HC/HP, EJP et TEMPO.

---

## ⚙️ Paramètres disponibles
Le fichier `config_linky_bridge.yaml` contient l'appel aux différents packages avec leurs paramètres.
Vous pouvez le modifier si nécessaire. Par défaut, on va exposer les étiquettes téléinfo sur 2 bus rs485 en Modbus RTU mais vous pouvez également en enlever un en fonction des capacités de votre ESP32.

### 📡 Paramètres Téléinfo : `packages_linky_bridge\teleinfo_map.yaml`

| Substitution        | Description                        | Valeur par défaut |
|---------------------|------------------------------------|-------------------|
| `teleinfo_id`       | Nom de votre composant téléinfo    | `linky`           |
| `rx_pin`            | Broche RX (GPIO)                   | `16`              |
| `tx_pin`            | Broche TX (GPIO), non utilisé      | `17`              |

### 🔌 Paramètres Modbus : `packages_linky_bridge\modbus_map.yaml`

| Substitution              | Description                             | Valeur par défaut |
|---------------------------|-----------------------------------------|-------------------|
| `bus_id`                  | Identifiant du bus Modbus               | `1`               |
| `bus_address`             | Adresse Modbus                          | `100`             |
| `baud_rate`               | Baudrate RS485                          | `9600`            |
| `tx_pin`                  | Broche TX pour RS485                    | `13`              |
| `rx_pin`                  | Broche RX pour RS485                    | `21`              |
| `flow_control_pin`        | Broche de contrôle de flux Modbus RTU   | `14`              |
| `stop_bit`                | Stop bit RS485                          | `1`               |
| `parity`                  | Parité RS485 (`NONE`, `EVEN`, `ODD`)    | `NONE`            |
| `teleinfo_id`             | Nom du composant téléinfo utilisé       | `linky`           |

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
Téléchargez le composant et notemment le dossier `linky_bridge`. Créez un fichier secrets.yaml pour stocker vos mots de passe. Voir l'exemple dans le dossier `test` pour un exemple pratique. Dans votre fichier, appelez votre fichier `config_linky_bridge.yaml` avec un `package`.
Ci-dessous, un exemple de contenu du fichier `config_linky_bridge.yaml`

```yaml
packages:
  teleinfo: !include
    file: packages_linky_bridge/teleinfo_map.yaml
    vars:
      teleinfo_id: linky
      tx_pin: 17
      rx_pin: 16

  modbus1: !include
    file: packages_linky_bridge/modbus_map.yaml
    vars:
      bus_id: 1
      bus_address: 100
      baud_rate: 9600
      tx_pin: 13
      rx_pin: 21
      flow_control_pin: 14
      stop_bits: 1
      parity: NONE
      teleinfo_id: linky

  modbus2: !include
    file: packages_linky_bridge/modbus_map.yaml
    vars:
      bus_id: 2
      bus_address: 100
      baud_rate: 9600
      tx_pin: 38
      rx_pin: 40
      flow_control_pin: 39
      stop_bits: 1
      parity: NONE
      teleinfo_id: linky

```

---

## 🛠️ Utilisation du composant

### 📁 Structure du dépôt

Le composant est organisé dans un dossier `linky_bridge/` contenant :
- `config_linky_bridge.yaml` : le fichier contenant votre configuration téléinfo
- `packages_linky_bridge` : le dossier contenant les fichiers du package linky_bridge
- `modbus_map.yaml` : le fichier contenant le paramétrage modbus
- `teleinfo_map.yaml` : le fichier exposant les étiquettes téléinfo

---

### 📦 Intégration dans ESPHome

1. **Copiez le dossier `linky_bridge/`** dans votre projet ESPHome.

2. **Modifiez le fichier `config_linky_bridge.yaml`** dans votre fichier principal `.yaml`.

3. **Créez un fichier `secrets.yaml`** à la racine de votre projet (avec votre fichier yaml). Il va contenir vos mots de passe. Vous trouverez un exemple dans le dossier `test`, dans le fichier `secrets.example.yaml`.

3. **Incluez le composant dans votre configuration** 

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
- Un adaptateur téléinfo (opto-isolé)
- Un ESP32 ou ESP8266 compatible avec UART et Modbus
- Un convertisseur RS485


###  ⚠️ Matériel de référence

Dans le dossier schematic, vous trouverez :
- Le schéma au format PDF du module électronique de référence. La carte est prévue de s'installer dans un boitier plastique 2 modules au format rail DIN
- La nomenclature des des composants
- Le fichier de fabrication Gerber

---
