"""
test.py

Author: James Chen

Description:
Uses DDL to communicate and control the MCP2221 chip that acts as a USB to I2C, UART and GPIO converter
USB is a COM port, able to use pyserial or putty
"""

from ctypes import *
import os


class MCP2221:
    MCP_Library = windll.LoadLibrary(os.path.dirname(__file__) + '/mcp2221_dll_um_x64.dll')

    # vendor and product id
    MCP_VID = 0x04D8
    MCP_PID = 0x00DD

    # mcp2221 constants
    MCP_PINS = 4

    # error codes dictionary
    errors_dict = {0: 'E_SUCCESS', -1: 'E_ERR_UNKOWN_ERROR',
                   -2: 'E_ERR_CMD_FAILED', -3: 'E_ERR_INVALID_HANDLE',
                   -4: 'E_ERR_INVALID_PARAMETER', -5: 'E_ERR_INVALID_PASS',
                   -6: 'E_ERR_PASSWORD_LIMIT_REACHED', -7: 'E_ERR_FLASH_WRITE_PROTECTED',
                   -10: 'E_ERR_NULL', -11: 'E_ERR_DESTINATION_TOO_SMALL',
                   -12: 'E_ERR_INPUT_TOO_LARGE', -13: 'E_ERR_FLASH_WRITE_FAILED',
                   -14: 'E_ERR_MALLOC', -101: 'E_ERR_NO_SUCH_INDEX',
                   -103: 'E_ERR_DEVICE_NOT_FOUND', -104: 'E_ERR_INTERNAL_BUFFER_TOO_SMALL',
                   -105: 'E_ERR_OPEN_DEVICE_ERROR', -106: 'E_ERR_CONNECTION_ALREADY_OPENED',
                   -107: 'E_ERR_CLOSE_FAILED', -301: 'E_ERR_EEPROM_WRITE_FAIL',
                   -302: 'E_ERR_RAW_TX_COPYFAILED', -303: 'E_ERR_RAW_RX_COPYFAILED',
                   -401: 'E_ERR_STRING_TOO_LARGE', -402: 'E_ERR_SPEED_NOT_SET',
                   -403: 'E_ERR_INVALID_BYTE_NUMBER', -404: 'E_ERR_INVALID_ADDRESS',
                   -405: 'E_ERR_I2C_BUSY', -406: 'E_ERR_I2C_READ_ERROR',
                   -407: 'E_ERR_ADDRESS_NACK', -408: 'E_ERR_TIMEOUT',
                   -409: 'E_ERR_TOO_MANY_RX_BYTES', -410: 'E_ERR_COPY_RX_DATA_FAILED',
                   -411: 'E_ERR_NO_EFFECT', -412: 'E_ERR_COPY_TX_DATA_FAILED',
                   -413: 'E_ERR_INVALID_PEC', -414: 'E_ERR_BLOCK_SIZE_MISMATCH'}

    def __init__(self, pin_mask):
        self.err_status = 0
        self.handle = None
        self.gpio_dir_mask = []
        self.gpio_out_mask = []
        # self.ResetPins()

        if len(pin_mask) != self.MCP_PINS:
            self.pin_mask = []
            self.err_status = -2
            self.getErrorStatus()
        else:
            self.pin_mask = pin_mask

    def getErrorStatus(self):
        print('MCP2221: ', self.errors_dict.get(self.err_status, self.err_status))
        if self.err_status != 0:
            raise Exception(
                f'ERROR {self.err_status}: MCP2221 {self.errors_dict.get(self.err_status, self.err_status)}')

    def connect(self):
        dev = (c_uint * 1)()
        self.MCP_Library.Mcp2221_GetConnectedDevices(c_ushort(self.MCP_VID), c_ushort(self.MCP_PID), dev)
        num_devices = dev[0]
        if num_devices == 0:
            self.err_status = -103
            self.getErrorStatus()
        else:
            handle = c_void_p(
                self.MCP_Library.Mcp2221_OpenByIndex(c_ushort(self.MCP_VID), c_ushort(self.MCP_PID), c_uint(0)))
            self.err_status = self.MCP_Library.Mcp2221_GetLastError()
            if self.err_status != 0:  # E_SUCCESS
                self.getErrorStatus()
            else:
                self.handle = handle
                print('MCP2221 connected successfully')
        self.setGpioConfig([0, 0, 0, 0], [0, 0, 0, 0])

    def close(self):
        self.err_status = self.MCP_Library.Mcp2221_Close(self.handle)
        if self.err_status != 0:
            self.getErrorStatus()
        else:
            print('MCP2221 closed successfully')

    def setGpioConfig(self, gpio_dir_mask, gpio_out_mask):
        b_pin_mask = bytearray(self.pin_mask)
        b_gpio_dir_mask = bytearray(gpio_dir_mask)
        b_gpio_out_mask = bytearray(gpio_out_mask)
        if (len(gpio_dir_mask) != self.MCP_PINS) or (len(gpio_out_mask) != self.MCP_PINS):
            self.err_status = -2
            self.getErrorStatus()
        else:
            pin_des = (c_ubyte * self.MCP_PINS)()
            gpio_dir = (c_char * self.MCP_PINS)()
            gpio_out = (c_char * self.MCP_PINS)()
            for N in range(self.MCP_PINS):
                pin_des[N] = b_pin_mask[N]
                gpio_dir[N] = b_gpio_dir_mask[N]
                gpio_out[N] = b_gpio_out_mask[N]
            cfgsel = c_ubyte(1)
            self.err_status = self.MCP_Library.Mcp2221_SetGpioSettings(self.handle, cfgsel, pin_des, gpio_dir, gpio_out)
            if self.err_status != 0:
                self.getErrorStatus()
            else:
                self.gpio_dir_mask = b_gpio_dir_mask
                self.gpio_out_mask = b_gpio_out_mask

    def setGpioPin(self, pin, state):
        if (pin > 4) or (pin < 0):
            self.err_status = -2
            self.getErrorStatus()
        elif (not self.gpio_dir_mask) or (not self.gpio_out_mask):  # checks if empty
            self.err_status = -500
            self.getErrorStatus()
        elif self.gpio_dir_mask[pin] != 0:
            self.err_status = -501
            self.getErrorStatus()
        else:
            self.gpio_out_mask[pin] = state
            self.setGpioConfig(gpio_dir_mask=self.gpio_dir_mask, gpio_out_mask=self.gpio_out_mask)

    def i2cRead(self, i2cAddress, bytesToRead):
        read_bytes = bytearray(bytesToRead)

        pbytesToRead = c_uint(bytesToRead)
        pslaveAddress = c_uint(i2cAddress)
        puse7bitAddress = c_uint(1)  # use 7 bit i2c address
        pdataRx = (c_ubyte * bytesToRead)()  # I2C Rx data buffer

        self.err_status = self.MCP_Library.Mcp2221_I2cRead(self.handle, pbytesToRead, pslaveAddress, puse7bitAddress,
                                                           pdataRx)
        if self.err_status != 0:
            self.getErrorStatus()
        else:
            for N in range(bytesToRead):
                read_bytes[N] = pdataRx[N]
        return list(read_bytes)

    def i2cWrite(self, i2cAddress, txData):
        b_write_bytes = bytearray(txData)
        txfer_size = len(txData)

        pslaveAddress = c_uint(i2cAddress)
        puse7bitAddress = c_uint(1)
        ptxfer_size = c_uint(txfer_size)

        pdataTx = (c_ubyte * txfer_size)()
        for N in range(txfer_size):
            pdataTx[N] = b_write_bytes[N]

        self.err_status = self.MCP_Library.Mcp2221_I2cWrite(self.handle, ptxfer_size, pslaveAddress, puse7bitAddress,
                                                            pdataTx)
        if self.err_status != 0:  # E_SUCCESS
            self.getErrorStatus()


if __name__ == '__main__':
    MCP = MCP2221([0] * 4)
    print("done")
