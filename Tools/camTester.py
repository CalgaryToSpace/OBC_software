import serial
import time

data = bytes('000003DEFFD8FFDB0084000D09090B0A080D0B0A0B0E0E0D0F13201513121213'.encode())

if __name__ == '__main__':
    try:
        port = 'COM5'
        ser = serial.Serial(port, 230400, timeout=1)
        ser.flush()
        print('Serial port opened')

    except serial.serialutil.SerialException:
        print("Serial open failed")
        exit()

    while 1:
        line = ser.read(1)
        rx = list(line)


        if rx:
            print("**********************************")
            print('Raw bytes: ')
            print(line)
            print('Message bytes:')
            print(rx)

            msg = "".join(map(chr, rx))
            print('Message as text:')
            print(msg)
            print("**********************************")

            print(rx[0])
            if msg == 'M':
                time.sleep(1)
                ser.write(data)
                print(data)
                print("sent!")
                for i in range(989):
                    ser.write(data)
                    print(i)
