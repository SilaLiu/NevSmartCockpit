#include <libs/instrument_command1.hpp>

int32_t InstrumentCommand1::ID = 0x28A;

// public
InstrumentCommand1::InstrumentCommand1() { Reset(); }

void InstrumentCommand1::UpdateData(int gear_shift_ctrl, int eoc_mode_shift_ctrl, bool left_door_ctrl, bool right_door_ctrl, bool emergency_button_ctrl, bool dome_light_ctrl, bool atmospherelightsp_ctrl, int left_window_ctrl, int right_window_ctrl) {
  set_p_gear_shift_ctrl(gear_shift_ctrl);
  set_p_eoc_mode_shift_ctrl(eoc_mode_shift_ctrl);
  set_p_left_door_ctrl(left_door_ctrl);
  set_p_right_door_ctrl(right_door_ctrl);
  set_p_emergency_button_ctrl(emergency_button_ctrl);
  set_p_dome_light_ctrl(dome_light_ctrl);
  set_p_atmospherelightsp_ctrl(atmospherelightsp_ctrl);
  set_p_left_window_ctrl(left_window_ctrl);
  set_p_right_window_ctrl(right_window_ctrl);
}

void InstrumentCommand1::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * InstrumentCommand1::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'gear_shift_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|8]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void InstrumentCommand1::set_p_gear_shift_ctrl(int gear_shift_ctrl) {
  // gear_shift_ctrl = ProtocolData::BoundedValue(0, 8, gear_shift_ctrl);
  int x = gear_shift_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 3);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 3, 'is_signed_var': False, 'len': 2, 'name': 'eoc_mode_shift_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void InstrumentCommand1::set_p_eoc_mode_shift_ctrl(int eoc_mode_shift_ctrl) {
  // eoc_mode_shift_ctrl = ProtocolData::BoundedValue(0, 3, eoc_mode_shift_ctrl);
  int x = eoc_mode_shift_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 3, 2);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 1, 'name': 'left_door_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void InstrumentCommand1::set_p_left_door_ctrl(bool left_door_ctrl) {
  int x = left_door_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 1);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 9, 'is_signed_var': False, 'len': 1, 'name': 'right_door_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void InstrumentCommand1::set_p_right_door_ctrl(bool right_door_ctrl) {
  int x = right_door_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 1, 1);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 10, 'is_signed_var': False, 'len': 1, 'name': 'emergency_button_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void InstrumentCommand1::set_p_emergency_button_ctrl(bool emergency_button_ctrl) {
  int x = emergency_button_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 2, 1);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 11, 'is_signed_var': False, 'len': 1, 'name': 'dome_light_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void InstrumentCommand1::set_p_dome_light_ctrl(bool dome_light_ctrl) {
  int x = dome_light_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 3, 1);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 12, 'is_signed_var': False, 'len': 1, 'name': 'atmospherelightsp_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
void InstrumentCommand1::set_p_atmospherelightsp_ctrl(bool atmospherelightsp_ctrl) {
  int x = atmospherelightsp_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 4, 1);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 16, 'is_signed_var': True, 'len': 2, 'name': 'left_window_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void InstrumentCommand1::set_p_left_window_ctrl(int left_window_ctrl) {
  // left_window_ctrl = ProtocolData::BoundedValue(0, 3, left_window_ctrl);
  int x = left_window_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 2);
  data[2] += to_set.return_byte_t();
  
}

// config detail: {'bit': 18, 'is_signed_var': True, 'len': 2, 'name': 'right_window_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void InstrumentCommand1::set_p_right_window_ctrl(int right_window_ctrl) {
  // right_window_ctrl = ProtocolData::BoundedValue(0, 3, right_window_ctrl);
  int x = right_window_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 2, 2);
  data[2] += to_set.return_byte_t();
  
}


