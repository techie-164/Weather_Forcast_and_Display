# Weather Monitoring and Forecasting System

[![Python](https://img.shields.io/badge/Python-3.10-blue?logo=python)](https://www.python.org/)
[![Status](https://img.shields.io/badge/Project-Active-brightgreen)]()
[![License](https://img.shields.io/badge/License-MIT-lightgrey)](LICENSE)
[![ML](https://img.shields.io/badge/ML-Linear%20Regression-orange?logo=scikit-learn)]()

📡 A compact and reliable system that monitors real-time weather conditions and forecasts short-term environmental changes using machine learning, designed for microcontroller deployment.

---

## 🔧 Features

* 🌡️ **Live Weather Monitoring**
  Displays real-time **Temperature**, **Humidity**, and **Pressure** using onboard sensors.

* 🔮 **Short-Term Forecasting**
  Uses a **Linear Regression** model to predict the next 5 values based on past sensor readings.

* 🔌 **Microcontroller Integration**
  Forecasted values are sent via **Serial Communication** to an **ESP microcontroller**, which handles data display.

---

## 🛠️ Technologies Used

* **Python** – Data processing and forecasting logic
* **Pandas** – CSV handling and data cleaning
* **Scikit-learn** – Linear regression for prediction
* **NumPy** – Numerical computations
* **PySerial** – Serial communication interface
* **ESP (e.g., ESP32)** – Receives data and displays output
* **DHT11 & BMP280 Sensors** – To measure temperature, humidity, and pressure

---

## ⚙️ How It Works

1. 📥 Sensors collect live environmental data and send it to the ESP.
2. 🗃️ Data is periodically saved to a CSV file.
3. 🧠 A Python script trains a model on historical data and forecasts future values.
4. 🔁 Forecasted values are transmitted to the ESP via serial.
5. 📺 The ESP displays predicted values in real time.
