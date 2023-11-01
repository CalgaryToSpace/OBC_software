#### ADCS Communication Module

The CubeSpace CubeADCS hardware module includes a set of software packages for its operation.

The Calgary2Space system built using FreeRTOS and FPrime will not run the ADCS software packages as-is. Therefore, the purpose of this ADCS Communication module is to have an interface for developers to query the ADCS' data according to the schema provided in the official CubeSpace CubeADCS documentation.

The CubeADCS documentation is available on the CTS Google Drive.

#### Tasks
1) Design and document the communication protocol between the STM32 chip and the ADCS module,
2) Ensure that messages can be accepted and sent from/to the ADCS module.


#### Contributors
- Saksham Puri (https://github.com/Saksham-P)
- Zach Uy (https://github.com/SCBee)
- Nadeem Moosa (https://github.com/DeemDeem52)