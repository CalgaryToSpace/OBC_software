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

    print("Listening for incoming serial messages...")
    while 1:
        line = ser.readline()
        rx = list(line)

        # display incoming data
        if rx:
            print_data(rx)

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
