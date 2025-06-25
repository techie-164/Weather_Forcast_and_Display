import pandas as pd
from sklearn.linear_model import LinearRegression
import numpy as np
import serial
import time

# Load and clean CSV
df = pd.read_csv('sensor_data.csv')
df.columns = df.columns.str.strip()

X = df[['Time(s)']].values
features = ['Temp_DHT', 'Humidity', 'Pressure']
forecasts = {}

# Fit regression for each feature
for feature in features:
    y = df[feature].values
    model = LinearRegression()
    model.fit(X, y)

    future_times = np.array([[df['Time(s)'].max() + i] for i in range(1, 6)])
    prediction = model.predict(future_times)
    forecasts[feature] = prediction

# Send forecasted data over Serial
with serial.Serial('COM7', 115200, timeout=1) as ser:
    time.sleep(2)  # Reset time for ESP
    for i in range(5):
        line = f"{forecasts['Temp_DHT'][i]:.2f},{forecasts['Humidity'][i]:.2f},{forecasts['Pressure'][i]:.2f}\n"
        print("Sending:", line.strip())
        ser.write(line.encode())
        time.sleep(2)  # Creating delay for next message