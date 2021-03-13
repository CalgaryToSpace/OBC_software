import serial

class Frame:
    def __init__(self):
        """
        initialize sample telemetry frame
        """
        self.sync_bytes = [0x0c, 0xff, 0xff, 0x0c]
        self.frame_counter = [0x00, 0x01]
        self.temperature = [0xaa, 0xaa]
        self.firmware_version = [0x01]
        self.mpi_unit_id = [0x01]
        self.detector_status = [0x00, 0x50]
        self.dome_voltage_set = [0xf0, 0x6a]
        self.spib = [0x01]
        self.dome_index = [0xdd]
        self.face_plate_voltage_set = [0xd5, 0x65]
        self.face_plate_voltage = [0xd5, 0x65]
        self.dome_voltage = [0xf0, 0x6a]

        self.image = []
        for i in range(0, 68*2):
            self.image.append(i)

        self.crc = [0x02, 0x02]

        self.full_frame = self.sync_bytes + self.frame_counter + self.temperature + self.firmware_version + \
                          self.mpi_unit_id + self.detector_status + self.dome_voltage_set + self.spib + \
                          self.dome_index + self.face_plate_voltage_set + self.face_plate_voltage + \
                          self.dome_voltage + self.image + self.crc
        self.frame_bytes = bytes(self.full_frame)


if __name__ == '__main__':
    Frame1 = Frame()

    print("Frame is: ")
    print(Frame1.frame_bytes)

    print("Frame Length is: ", end='')
    print(len(Frame1.frame_bytes))

    try:
        port = 'COM3'
        ser = serial.Serial(port, 230400, timeout=1)
        ser.flush()
        ser.write(Frame1.frame_bytes)
    except:
        print("Serial print failed")
