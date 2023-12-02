import serial
import datetime
import os
import polars as pl

########### SETTINGS ############
TEST_DATA_PATH: str = (
    "path/to/test_data_file.csv"  # test data that we want to send to the ADCS
)
BAUDRATE: int = 115200
PORT: str = None
if os.name == "nt":
    PORT = "COM3"  # windows
elif os.name == "posix":
    PORT = "/dev/ttyACM0"  # unix
#################################


def load_data(file: str):
    try:
        data_csv = pl.read_csv(file)
    except Exception:
        return None

    return data_csv


def print_data(rx: list):
    now = datetime.datetime.now().strftime("%H:%M:%S")
    print(f"{now} Message (BYTES): {rx}")

    msg = bytes(rx).decode("utf-8")
    print(f"{now} Message (ASCII): {msg}")


def listen(ser: serial.Serial):
    print("Listening...")
    while True:
        line = ser.readline()
        rx = list(line)

        if rx:
            print_data(rx)


def sim_driver(ser: serial.Serial, mode: int = None):
    print("Loading test data")
    data: pl.DataFrame = load_data(TEST_DATA_PATH)
    print("Test data loaded")

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
            print("Check your port name")
            exit()

        ser = serial.Serial(port=PORT, baudrate=BAUDRATE, timeout=1)
        ser.flush()
        print("Serial Port Connection: Success")

        # begin tests
        sim_driver(ser)
    except serial.serialutil.SerialException:
        print("Serial Port Connection: Failed")
