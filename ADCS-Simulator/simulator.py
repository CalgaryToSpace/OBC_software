import serial
import datetime
import os
import polars as pl
import time

########### SETTINGS ############
TEST_DATA_PATH: str = (
    "TLM_Nov18.csv"  # test data that we want to send to the ADCS
)
BAUDRATE: int = 209700
PORT: str = None
if os.name == "nt":
    PORT = "COM3"  # windows
elif os.name == "posix":
    PORT = "/dev/ttyACM0"  # unix
#################################


def load_data(file: str):
    # load data from the .csv file
    try:
        data_csv = pl.read_csv(file, truncate_ragged_lines=True)
        return data_csv
    except Exception:
        return None   


def send_frames(data, ser, n_frames):
    # send n_frames of data to the serial port
    for i in range(0, n_frames):
        time.sleep(1 / 32)
        ser.write(bytes(data[i]))
        print(i)
        print(data[i])


def print_data(rx: list):
    # print received data to the console
    now = datetime.datetime.now().strftime("%H:%M:%S")
    print(f"{now} Message (BYTES): {rx}")

    msg = bytes(rx).hex()
    print(f"{now} Message (ASCII): {msg}")


def listen(ser: serial.Serial):
    # read from the serial port
    print("Listening...")
    while True:
        line = ser.readline()
        rx = list(line)

        if rx:
            print_data(rx)


def sim_driver(ser: serial.Serial, mode: int = None):
    print("Loading test data...")
    data: pl.DataFrame = load_data(TEST_DATA_PATH)
    if data.is_empty():
        print("Error loading test data.")
        quit()
    else:
        print("Test data loaded.")

    tc_id = 0x00
    tc_data = []

    id_flag = 0
    data_flag = 0
    finished_flag = 0

    print("Listening for incoming serial messages...")
    while 1:
        line = ser.readline()
        rx = list(line)

        # display incoming data
        if rx:
            print_data(rx)
            
            # FORMAT: [0x1f, 0x7f, ID, {data}, 0x1f, 0xff]

            prev = 0x00
            for item in bytes(rx):

                if data_flag == 1:
                    tc_data.append(item)

                if id_flag == 1:
                    tc_id = item
                    id_flag = 0
                    data_flag = 1
                
                if prev == 0x1f and item == 0x7f:
                    id_flag = 1
                elif prev == 0x1f and item == 0xff:
                    id_flag = 0
                    data_flag = 0
                    finished_flag = 1
                    tc_data = tc_data[:-2]
                
                prev = item

            if finished_flag == 1:
                print(f'TC/TLM ID: {tc_id}')
                print(f'Data: {tc_data}')
                finished_flag = 0
                tc_id = 0x00
                data = []
                


            # cases where we send data to the ADCS


if __name__ == "__main__":
    try:
        if not PORT:
            print("Check your port name.")
            exit()

        ser = serial.Serial(port=PORT, baudrate=BAUDRATE, timeout=1)
        ser.flush()
        print("Serial Port Connection: Success")

        # begin tests
        sim_driver(ser)

    except serial.serialutil.SerialException:
        print("Serial Port Connection: Failed")
