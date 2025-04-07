#pragma once

#include <libs/Byte.hpp>

class InstrumentFb1 {
public:
  static const uint32_t ID = 0x28D;
  InstrumentFb1();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int gear_shift_sta_;
  int eco_sta_;
  bool left_door_sta_;
  bool right_door_sta_;
  bool reserve_;
  bool dome_light_sta_;
  bool atmospherelightsp_sta_;
  int left_window_sta_;
  int right_window_sta_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'gear_shift_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|8]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int gearshiftsta();

  // config detail: {'bit': 3, 'is_signed_var': False, 'len': 2, 'name': 'eco_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ecosta();

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 1, 'name': 'left_door_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool leftdoorsta();

  // config detail: {'bit': 9, 'is_signed_var': False, 'len': 1, 'name': 'right_door_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool rightdoorsta();

  // config detail: {'bit': 10, 'is_signed_var': False, 'len': 1, 'name': 'reserve', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool reserve();

  // config detail: {'bit': 11, 'is_signed_var': False, 'len': 1, 'name': 'dome_light_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool domelightsta();

  // config detail: {'bit': 12, 'is_signed_var': False, 'len': 1, 'name': 'atmospherelightsp_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool atmospherelightspsta();

  // config detail: {'bit': 16, 'is_signed_var': True, 'len': 2, 'name': 'left_window_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int leftwindowsta();

  // config detail: {'bit': 18, 'is_signed_var': True, 'len': 2, 'name': 'right_window_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int rightwindowsta();
};



