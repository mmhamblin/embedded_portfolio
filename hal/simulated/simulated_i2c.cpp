/// @file hal/simulated/simulated_i2c.cpp
/// @brief Simulated I2C HAL implementation

#include "hal/simulated/simulated_i2c.hpp"

namespace hal
{

I2CERROR SimulatedI2C::init()
{
  initialized_ = true;
  return I2CERROR::NONE;
}

I2CERROR SimulatedI2C::set_register(uint8_t device_address, 
                                    uint8_t register_address, 
                                    const std::vector<uint8_t>& data)
{
  device_memory_[device_address][register_address] = data;
  return I2CERROR::NONE;
}

I2CERROR SimulatedI2C::write(uint8_t device_address, 
                             const uint8_t* data,
                             size_t length)
{
  if (!initialized_)
  {
    return I2CERROR::NOT_INITIALIZED;
  }
  if (length < 1)
  {
    return I2CERROR::INVALID_ARGUMENT;
  }

  // First byte is the register address
  current_register_ = data[0];
  has_register_ = true;

  for(size_t i = 1; i < length; ++i)
  {
    device_memory_[device_address][current_register_ + (i - 1)] = {data[i]};
  }

  return I2CERROR::NONE;
}

I2CERROR SimulatedI2C::read(uint8_t device_address, 
                            uint8_t* data, 
                            size_t length)
{
  if (!initialized_)
  {
    return I2CERROR::NOT_INITIALIZED;
  }
  if (length < 1)
  {
    return I2CERROR::INVALID_ARGUMENT;
  }

  if (device_memory_.find(device_address) == device_memory_.end())
  {
    return I2CERROR::NACK;
  }
  if (!has_register_)
  {
    return I2CERROR::INVALID_ARGUMENT;
  }
  

  for(size_t i = 0; i < length; ++i)
  {
    uint8_t reg_addr = current_register_ + i;
    if (device_memory_[device_address].find(reg_addr) == device_memory_[device_address].end())
    {
      return I2CERROR::NACK;
    }
    const auto& reg_data = device_memory_[device_address][reg_addr];
    if (reg_data.empty())
    {
      return I2CERROR::NACK;
    }
    data[i] = reg_data[0];
  }

  current_register_ += length;
  return I2CERROR::NONE;
} // namespace hal