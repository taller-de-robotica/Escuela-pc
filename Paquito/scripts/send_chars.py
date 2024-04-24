import socket

# Wifi
UDP_IP = "000.000.0.000" # Indicar IP
UDP_PORT = 0000 # Indicar puerto
sock = socket.socket(socket.AF_INET, # Internet
                socket.SOCK_DGRAM) # UDP
meesage = '7'
mes = bytes(message, 'ascii')
sock.sendto(mes, (UDP_IP, UDP_PORT))

meesage = '5'
mes = bytes(message, 'ascii')
sock.sendto(mes, (UDP_IP, UDP_PORT))
