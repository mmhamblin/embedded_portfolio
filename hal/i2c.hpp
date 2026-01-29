/// @file embedded_portfolio/hal/i2c.hpp
/// @brief I2C HAL interface

#pragma once

#include <cstddef>
#include <cstdint>

namespace hal
{

enum class I2CERROR
{
    NONE,
    NOT_INITIALIZED,
    NACK,
    BUS_ERROR,
    TIMEOUT,
    INVALID_ARGUMENT
};

class I2C
{
public:
    virtual ~I2C() = default;

    /// @brief  Initialize the I2C peripheral
    /// @return I2CERROR indicating success or type of failure
    virtual I2CERROR init() = 0;

    /// @brief Write data to an I2C device
    ///
    /// @param device_address The I2C address of the device
    /// @param data           Pointer to the data to write
    /// @param length         Length of the data to write
    ///
    /// @return I2CERROR indicating success or type of failure
    virtual I2CERROR write(uint8_t device_address, 
                           const uint8_t* data, 
                           size_t length) = 0;

    /// @brief Read data from an I2C device
    ///
    /// @param device_address The I2C address of the device 
    /// @param data           Pointer to the buffer to store read data
    /// @param length         Length of the data to read
    ///
    /// @return I2CERROR indicating success or type of failure
    virtual I2CERROR read(uint8_t device_address, 
                          uint8_t* data, 
                          size_t length) = 0;

};

} // namespace embedded_portfolio::hal
