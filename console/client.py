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
    try:
        data = soc.recv(BUFFER_SIZE)
    except Exception as ex:
        print("Error connecting with server...")
        soc.close()
    if data=="":
        exit()
    print("Message received: "+data)
    if ("sleep" in data):
        print("Status sent to web: 1")
        send("1")
    elif ("awake" in data):
        print("Status sent to web: 0")
        send("0")

try:
    socketio.run(app)
except KeyboardInterrupt as ex: #Exit Program whenever the user presses Ctrl+C
    print("Keyboard Interupt: exit program")
    
soc.close()

