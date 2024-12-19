/**
  ************************************* Copyright ******************************
  *                 (C) Copyright 2023,--,China, CUIT.
  *                            All Rights Reserved
  *                     By(JCML)
  * FileName   : INA219.c
  * Version    : v1.0
  * Author     : JCML
  * Date       : 2024/12/18
  * Description: INA219Çý¶¯
******************************************************************************
 */
#include "main.h"
#include "INA219.h"

float ina219_calibrationValue;
float ina219_currentDivider_mA;
float ina219_powerMultiplier_mW;

/**
 * @brief  The IIC reads 16bit data from the specified register address.
 * @param  ina219 Slave configuration structure of the IIC.
 * @param  registerAddress Internal memory address.
 * @return 16 bit register data.
 */
uint16_t Read16(INA219_t *ina219, uint8_t Register)
{
	uint8_t Value[2];

	HAL_I2C_Mem_Read(ina219->ina219_i2c, (INA219_ADDRESS<<1), Register, 1, Value, 2, 1000);

	return ((Value[0] << 8) | Value[1]);
}

/**
 * @brief  Writes 16 bits of data to the register.
 * @param  ina219 Slave configuration structure of the IIC.
 * @param  registerAddress Internal memory address.
 * @param  Value 16 bits of data to be written.
 */
void Write16(INA219_t *ina219, uint8_t Register, uint16_t Value)
{
	uint8_t addr[2];
	addr[0] = (Value >> 8) & 0xff;  // upper byte
	addr[1] = (Value >> 0) & 0xff; // lower byte
	HAL_I2C_Mem_Write(ina219->ina219_i2c, (INA219_ADDRESS<<1), Register, 1, (uint8_t*)addr, 2, 1000);
}

/**
 * @brief  Read bus voltage.
 * @param  ina219 Slave configuration structure of the IIC.
 * @return Read voltage value, unit mV.
 */
float INA219_ReadBusVoltage(INA219_t *ina219)
{
	uint16_t result = Read16(ina219, INA219_REG_BUSVOLTAGE);

	return ((result >> 3  ) * 4);

}

/**
 * @brief  Read current register value.
 * @param  ina219 Slave configuration structure of the IIC.
 * @return Current register value.
 */
float INA219_ReadCurrent_raw(INA219_t *ina219)
{
	int16_t result = Read16(ina219, INA219_REG_CURRENT);

	return (result );
}

/**
 * @brief  Read current register value, unit mA.
 * @param  ina219 Slave configuration structure of the IIC.
 * @return Current value.
 */
float INA219_ReadCurrent(INA219_t *ina219)
{
	int16_t result = INA219_ReadCurrent_raw(ina219);

	return (result / ina219_currentDivider_mA );
}

/**
 * @brief  Read current register value, unit mV.
 * @param  ina219 Slave configuration structure of the IIC.
 * @return Shunt Voltage value.
 */
float INA219_ReadShuntVolage(INA219_t *ina219)
{
	uint16_t result = Read16(ina219, INA219_REG_SHUNTVOLTAGE);

  /* When multiple sign bits are present, they will all be the same value.
   * Negative numbers are represented in 2's complement format.
   * Generate the 2's complement of a negative number by complementing the absolute value binary number and adding 1.
   * Extend the sign, denoting a negative number by setting the MSB = 1.
   * Extend the sign to any additional sign bits to form the 16-bit word. */
    if(result > MAX_SHUNT_RANGE)
    {
        result = 65536 - MAX_SHUNT_RANGE;
    }

  /* Shunt voltage, unit mV. */
  return (result / 100);
}
/**
 * @brief  INA219 system reset.
 * @param  ina219 Slave configuration structure of the IIC.
 */
void INA219_Reset(INA219_t *ina219)
{
	Write16(ina219, INA219_REG_CONFIG, INA219_CONFIG_RESET);
	HAL_Delay(1);
}
/**
 * @brief Set calibration register.
 * @param ina219 Slave configuration structure of the IIC.
 * @param calibrationData Calibrated data.
 */
void INA219_setCalibration(INA219_t *ina219, uint16_t CalibrationData)
{
	Write16(ina219, INA219_REG_CALIBRATION, CalibrationData);
}
/**
 * @brief  Gets the value of the configuration register.
 * @param  ina219 Slave configuration structure of the IIC.
 * @return Configuration Register value.
 */
uint16_t INA219_getConfig(INA219_t *ina219)
{
	uint16_t result = Read16(ina219, INA219_REG_CONFIG);
	return result;
}
/**
 * @brief Set configuration register.
 * @param ina219 Slave configuration structure of the IIC.
 * @param configData Configuration data.
 */
void INA219_setConfig(INA219_t *ina219, uint16_t Config)
{
	Write16(ina219, INA219_REG_CONFIG, Config);
}

/**
 * @brief The measurement results are calibrated. Voltage range is 16V, Current range is 8A.
 * @param ina219 Slave configuration structure of the IIC.
 */

void INA219_setCalibration_16V_8A(INA219_t *ina219)
{
	uint16_t config = INA219_CONFIG_BVOLTAGERANGE_16V |
	                    INA219_CONFIG_GAIN_1_40MV | INA219_CONFIG_BADCRES_12BIT |
	                    INA219_CONFIG_SADCRES_12BIT_1S_532US |
	                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;

  // Current_LSB = Maximum Expected Current / 2^15 = (80 / 10) / 2^15 = 0.0002
  // Cal = 0.04096 / (Current_LSB / R) = 0.04096 / (0.0002A * 0.01R) = 20480 = 0x5000
  // Calibration Register = 20480
  ina219_calibrationValue = 10240;

  // 1mA = Current_LSB * bits = 200uA * 5bit (5 bit/mA)
  ina219_currentDivider_mA = 5;
  // 1mW = Power_LSB * bits = 4mW * 0.25bit (0.25f bit/mW)
  ina219_powerMultiplier_mW = 0.25f;

	INA219_setCalibration(ina219, ina219_calibrationValue);
	INA219_setConfig(ina219, config);
}

/**
 * @brief  Ina219 driver initialization
 * @param  ina219 Slave configuration structure of the IIC.
 * @param  i2c Pointer to a I2C_HandleTypeDef structure that contains
 *             the configuration information for the specified I2C.
 * @param  Address  Configuration data.
 * @return status.
 */
uint8_t INA219_Init(INA219_t *ina219, I2C_HandleTypeDef *i2c, uint8_t Address)
{
	ina219->ina219_i2c = i2c;
	ina219->Address = Address;

	ina219_currentDivider_mA = 0;
	ina219_powerMultiplier_mW = 0;

	uint8_t ina219_isReady = HAL_I2C_IsDeviceReady(i2c, (Address << 1), 3, 2);

	if(ina219_isReady == HAL_OK)
	{

		INA219_Reset(ina219);
		INA219_setCalibration_16V_8A(ina219);

		return 1;
	}

	else
	{
		return 0;
	}
}
/**
 * @brief  Ina219 driver ReadAll
 * @param  ina219 Slave configuration structure of the IIC.
 * @return void.
 */
void INA219_ReadALL(INA219_t *ina219){
    ina219->Voltage = INA219_ReadBusVoltage(ina219)/1000.0f;
    ina219->Current = INA219_ReadCurrent(ina219)/1000.0f;
    ina219->Power = ina219->Current * ina219->Voltage;
}

