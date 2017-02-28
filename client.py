import socket
from flask import Flask, render_template
from flask_socketio import SocketIO, emit, send

TCP_IP = '127.0.0.1'
TCP_PORT = 1500
BUFFER_SIZE = 1024

app = Flask("server")
app.config['SECRET_KEY']="secret!"
socketio=SocketIO(app)

soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
soc.connect((TCP_IP, TCP_PORT))

@socketio.on('message')
def handle_message(message):
    data = soc.recv(BUFFER_SIZE)
    if data=="":
        exit()
    print("Message received: "+data)
    if ("sleeping" in data):
        send("1")
    elif ("awake" in data):
        send("0")

socketio.run(app)
soc.close()

