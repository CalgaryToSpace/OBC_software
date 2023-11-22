import serial
import time
import threading

filename = 'xxxxx.bin' # FIXME

def load_sample_data(file):
    sample_telemetry_data_bin = open(file, 'rb')

    all_bytes_ls = []
    sample_telemetry_data_ls = []

    # go through and add all bytes into list
    byte = sample_telemetry_data_bin.read(1)
    while byte:
        all_bytes_ls.append(int.from_bytes(byte, 'big'))
        byte = sample_telemetry_data_bin.read(1)

    for frame_number in range(0, len(all_bytes_ls) // 160):
        sample_telemetry_data_ls.append(
            all_bytes_ls[frame_number * 160:(frame_number + 1) * 160])

    return sample_telemetry_data_ls


def send_frames(data, ser, n_frames):
    for i in range(0, n_frames):
        time.sleep(1 / 32)
        ser.write(bytes(data[i]))
        print(i)
        print(data[i])


def listen(ser):
    print('Listening for incoming serial messages...')
    while 1:
        line = ser.readline()
        rx = list(line)

        # print any incoming data
        if rx:
            print('Message bytes:')
            print(rx)

            msg = "".join(map(chr, rx))
            print('Message as text:')
            print(msg)


def start_adcs_simulator(ser, mode):
    print('Loading test data')
    test_data = load_sample_data(
        filename)
    print('Test data loaded')

    print('Listening for incoming serial messages...')
    while 1:
        line = ser.read(160)
        rx = list(line)

        # print any incoming data
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

            # if TC for start sending data
            if rx[0] == 84 and rx[1] == 67 and rx[2] == 9:
                if mode == 1:
                    print('Sending success echo')
                    echo = rx[:]
                    echo.append(1)
                    ser.write(bytes(echo))
                    print('Echo sent!')

                    print('Starting to send frames...')
                    print('Sending...')
                    send_frames(test_data)
                    print('Frames all sent!')

                if mode == 2:
                    time.sleep(1)
                    # print('Sending success echo')
                    # echo = rx[:]
                    # echo.append(1)
                    # ser.write(bytes(echo))
                    # print('Echo sent!')

                    print('Starting to send 50 frames')
                    send_frames(test_data, ser, 50)

                    print('Frames sent!')

            # Test TC HV_SET_FACEPLATE_VOLTAGE
            elif rx[0] == 84 and rx[1] == 67 and rx[2] == 4:
                print('Received HV_SET_FACEPLATE_VOLTAGE TC')
                echo = rx[:]
                echo.append(1)
                ser.write(bytes(echo))
                print('Setting Faceplate Voltage to: ' + str(rx[3]))
                print('Sending success echo: ' + str(echo))

            # unknown TC!!!
            elif rx[0] == 84 and rx[1] == 67:  # if its a TC
                print('Unknown TC... sending failed Echo')
                echo = rx[:]
                echo.append(0)
                ser.write(bytes(echo))
                print('Echo sent!')


if __name__ == '__main__':
    try:
        port = "COM5"
        ser = serial.Serial(port=port, baudrate=230400, timeout=1, bytesize=8, stopbits=1)
        ser.flush()
        print('Serial port opened')

    except serial.serialutil.SerialException:
        print("Serial open failed")
        exit()

    start_adcs_simulator(ser, 2)

    # Create new threads

    # thread1 = ListenThread(1, "Thread-1", ser)
    # thread2 = RunThread(2, "Thread-2", ser)
    #
    # # Start new Threads
    # thread1.start()
    # thread2.start()
