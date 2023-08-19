
# Projet WebServerESP32

## Table des matières

- [Éléments nécessaires](#1-éléments-nécessaires-au-projet)
- [Branchements](#2-branchements-sur-lesp32-nodemcu)
- [Structure des fichiers](#3-explication-de-la-structure-des-fichiers)
- [Build et Upload](#4-build-et-upload)
- [Documentation des APIs](#5-documentation-des-apis)
- [Explication du programme](#6-explication-détaillée-du-programme)

## 1. Éléments nécessaires au projet

- Carte ESP32 NodeMCU
- Capteur de température DS18B20
- Résistance de 4.7k ohms
- Carte SD pour stocker les données
- Bibliothèques Arduino :
  - ESPAsyncWebServer
  - ESPAsyncTCP (pour ESP8266) ou AsyncTCP (pour ESP32)
  - DallasTemperature
  - OneWire
  - SQLite ESP32
  - ArduinoJson

## 2. Branchements sur l'ESP32 NodeMCU

```
   +-------------------+
   |     NodeMCU       |
   |                   |
   | D8 -------------> | DS18B20 Data
   | 3.3V -----------> | DS18B20 VCC
   | GND ------------> | DS18B20 GND
   | GPIO5 ----------> | SD Card CS
   | GPIO18 ---------> | SD Card SCK
   | GPIO23 ---------> | SD Card MOSI
   | GPIO19 ---------> | SD Card MISO
   | 3.3V -----------> | SD Card VCC
   | GND ------------> | SD Card GND
   +-------------------+
```

**Note:** Une résistance de 4.7k ohms doit être connectée entre Data et VCC du DS18B20.

## 3. Explication de la structure des fichiers

Le projet est organisé de manière modulaire avec différents fichiers ayant des responsabilités spécifiques. Les fichiers `.h` déclarent la structure des classes et des fonctions, tandis que les fichiers `.cpp` contiennent l'implémentation.

Par exemple, `ApiManager.h` déclare la classe `ApiManager`. `ApiManager.cpp` contient la logique réelle.

## 4. Build et Upload

Pour uploader le code :
1. Connectez l'ESP32 via USB.
2. Sélectionnez le port COM et le type de carte dans l'IDE Arduino.
3. Cliquez sur "Upload".

## 5. Documentation des APIs

Lorsque l'ESP32 est connecté à un réseau, il peut être interrogé via les URLs suivantes :
- **POST** `http://[adresse_ip_esp32]/setTemperature`
- **GET** `http://[adresse_ip_esp32]/getTemperatures`

## 6. Explication détaillée du programme

Le programme crée un serveur web sur l'ESP32 pour interagir avec un capteur de température. Les températures peuvent être enregistrées et récupérées via des appels API, et sont stockées sur une carte SD avec SQLite.

- `WebServerESP32.ino`: Fichier principal.
- `ApiManager`: Gestion des appels API.
- `DatabaseManager`: Interactions avec la base de données SQLite.
- `TemperatureManager`: Lecture du capteur DS18B20.
- `WifiManager`: Gestion de la connexion WiFi.
- `SDManager`: Interactions avec la carte SD.