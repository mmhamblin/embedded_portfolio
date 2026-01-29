/// @file hal/simulated/simulated_i2c.hpp
/// @brief Simulated I2C HAL implementation

#pragma once

#include "hal/i2c.hpp"
#include <cstdint>
#include <cstddef>
#include <unordered_map>
#include <vector>

namespace hal
{
class SimulatedI2C : public I2C
{
public:
  SimulatedI2C() = default;

  ~SimulatedI2C() override = default;

  // Allows tests to pre-load device registers
  I2CERROR set_register(uint8_t device_address, 
                        uint8_t register_address, 
                        const std::vector<uint8_t>& data);

  I2CERROR init() override;

  I2CERROR write(uint8_t device_address, 
                 const uint8_t* data,
                 size_t length) override;

  I2CERROR read(uint8_t device_address, 
                uint8_t* data, 
                size_t length) override;
private:
  // Simulated device memory: device address -> register address -> data
  std::unordered_map<uint8_t, std::unordered_map<uint8_t, std::vector<uint8_t>>> device_memory_;
  uint8_t current_register_ = 0;
  bool has_register_ = false;
  bool initialized_ = false;

};

} // namespace hal