import smbus
import time
import struct

bus = smbus.SMBus(1)
address = 0x04

def writeBytes(cmd, bytes):
    bus.write_i2c_block_data(address, cmd, bytes)
    return -1

def setDatetimeArduino():
    actualTime = int(time.time())
    bytesTuple = struct.unpack("4B", struct.pack("I", actualTime))
    bytes = []
    for item in bytesTuple:
    	bytes.append(item)
    cmd = 0x01 # nuestro comando para indicarle al Arduino que queremos sincronizarlo temporalmente
    writeBytes(cmd,bytes)

setDatetimeArduino()
