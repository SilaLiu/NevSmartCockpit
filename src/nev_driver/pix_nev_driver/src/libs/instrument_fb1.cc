#include <libs/instrument_fb1.hpp>


InstrumentFb1::InstrumentFb1() {}

void InstrumentFb1::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void InstrumentFb1::Parse() {
  gear_shift_sta_ = gearshiftsta();
  eco_sta_ = ecosta();
  left_door_sta_ = leftdoorsta();
  right_door_sta_ = rightdoorsta();
  reserve_ = reserve();
  dome_light_sta_ = domelightsta();
  atmospherelightsp_sta_ = atmospherelightspsta();
  left_window_sta_ = leftwindowsta();
  right_window_sta_ = rightwindowsta();
}


// config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'gear_shift_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|8]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int InstrumentFb1::gearshiftsta() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 3);

  int ret = x;
  return ret;
}

// config detail: {'bit': 3, 'is_signed_var': False, 'len': 2, 'name': 'eco_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int InstrumentFb1::ecosta() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(3, 2);

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 1, 'name': 'left_door_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool InstrumentFb1::leftdoorsta() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 9, 'is_signed_var': False, 'len': 1, 'name': 'right_door_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool InstrumentFb1::rightdoorsta() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(1, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 10, 'is_signed_var': False, 'len': 1, 'name': 'reserve', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool InstrumentFb1::reserve() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(2, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 11, 'is_signed_var': False, 'len': 1, 'name': 'dome_light_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool InstrumentFb1::domelightsta() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(3, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 12, 'is_signed_var': False, 'len': 1, 'name': 'atmospherelightsp_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool InstrumentFb1::atmospherelightspsta() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(4, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 16, 'is_signed_var': True, 'len': 2, 'name': 'left_window_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int InstrumentFb1::leftwindowsta() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 2);

  x <<= 30;
  x >>= 30;

  int ret = x;
  return ret;
}

// config detail: {'bit': 18, 'is_signed_var': True, 'len': 2, 'name': 'right_window_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int InstrumentFb1::rightwindowsta() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(2, 2);

  x <<= 30;
  x >>= 30;

  int ret = x;
  return ret;
}

