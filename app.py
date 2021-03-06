import paho.mqtt.client as mqtt
from flask import Flask, render_template, request
import json
import sqlite3

app = Flask(__name__)

def dict_factory(cursor, row):
    d = {}
    for idx, col in enumerate(cursor.description):
        d[col[0]] = row[idx]
    return d

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("/esp32/sctLeitura")

# The callback for when a PUBLISH message is received from the ESP8266.
def on_message(client, userdata, message):
    if message.topic == "/esp32/sctLeitura":
        print("Leitura do estado da maquina")

        sctreadings_json = json.loads(message.payload)

        print(sctreadings_json)
        
        conn=sqlite3.connect('sensordata.db')
        c=conn.cursor()
		    
        try:
          c.execute("""INSERT INTO sctLeitura (id, estado, data, hora) VALUES (null, (?), date('now'), time('now', '-2 hour'))""", (sctreadings_json['estado'],) )
          conn.commit()
        except sqlite3.Error as e:
            print "Database error: ", e
        except Exception as e:
            print "Exception in _query: ", e
        finally:
            if conn:
                conn.close()

mqttc=mqtt.Client()
mqttc.on_connect = on_connect
mqttc.on_message = on_message
mqttc.connect("localhost",1883,60)
mqttc.loop_start()

@app.route("/")
def main():   
   conn=sqlite3.connect('sensordata.db')

   conn.row_factory = dict_factory
   c=conn.cursor()
   c.execute("SELECT * FROM sctLeitura ORDER BY id DESC LIMIT 1")
   readings = c.fetchall()
   print(readings)
   return render_template('main.html', readings=readings)

if __name__ == "__main__":
   app.run(host='0.0.0.0', port=8181, debug=True)
