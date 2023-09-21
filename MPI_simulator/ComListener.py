import serial

# Replace 'COM1' with the appropriate COM port
port_name = 'COM4'

# Create a serial connection
ser = serial.Serial(port=port_name, baudrate=230400, timeout=1)

if ser.is_open:
    print(f"Connected to {port_name}")
else:
    print(f"Failed to connect to {port_name}")
    exit(1)

# Send a command
command = 'HV_INNER_DOME_SCAN_MODE\n'
ser.write(command)

# Read and print the response
response = ser.read(1024)
print("Received:", response.decode('utf-8'))

# Close the serial connection
ser.close()
