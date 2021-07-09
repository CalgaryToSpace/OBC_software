"""
This script will open a serial port at 230400 baud, and wait for message starting with [0, 0, 0] bytes. It will
then send one sample MPI frame to be stored into the memory. Once it does this it will wait for the user to send the
data back, and verify that it has not changed.

@author: James Chen
"""

import serial
import time


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
        sample_telemetry_data_ls.append(all_bytes_ls[frame_number * 160:(frame_number + 1) * 160])

    return sample_telemetry_data_ls[0]


def send_frames(data, ser,  n_frames):
    for i in range(0, n_frames):
        time.sleep(1 / 32)
        ser.write(bytes(data[i]))
        print(i)
        print(data[i])


def start_mpi_simulator(ser):
    print('Loading test data')
    test_data = load_sample_data('CalgaryToSpace_Satellite1_MPI_Telemery_Example_ICD_V1.1.bin')
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

            # send data code
            if rx[0:2] == [3, 1, 4]:
                print('Starting to send test data...')
                send_frames(test_data)
                print('Frame sent!')

            # verify  bytes
            elif rx[0:3] == [12, 255, 255, 12]:
                print('Verifying data!')
                print("Received, Actual")
                failed = 0
                for index, byte in enumerate(rx):
                    print(f"{byte},{test_data[index]}")
                    if byte != test_data[index]:
                        failed = 1
                if failed:
                    print("Results do NOT match!")
                else:
                    print('Excellent Work!!! Results Match! :)')


if __name__ == '__main__':
    try:
        port = 'COM3'
        ser = serial.Serial(port, 230400, timeout=1)
        ser.flush()
        print('Serial port opened')

    except serial.serialutil.SerialException:
        print("Serial open failed")
        exit()

    start_mpi_simulator(ser)
