import serial
import serial.tools.list_ports
import time
import sys


DELAY = 2


if __name__ == "__main__":
    hwid = sys.argv[1]
    baudrate = int(sys.argv[2])
    message = sys.argv[3] + "\n"

    device = ""
    ports = serial.tools.list_ports.comports()
    print(f"Finding serial ports with hwid <{hwid}>")
    for port in ports:
        print(f"  - device <{port.device}> hwid <{port.hwid}>")
        if port.hwid == hwid:
            device = port.device
            print(f"hwid <{hwid}> found in device <{device}>")
            break

    if device == "":
        print(f"hwid <{hwid}> not found")
        sys.exit(1)

    ser = serial.Serial(device, baudrate, timeout=2)
    print(f"Sleeping {DELAY} seconds")
    time.sleep(DELAY)
    print(f"Write: {message.strip()} ({ser.write(message.encode())} bytes)")
    print(f"Sleeping {DELAY} seconds")
    time.sleep(DELAY)

    if ser.in_waiting > 0:
        data = ser.readline().decode("UTF-8").rstrip()
        print(f"Received: {data}")
