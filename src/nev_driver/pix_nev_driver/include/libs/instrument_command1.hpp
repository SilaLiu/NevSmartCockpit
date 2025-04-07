#pragma once
#include <libs/Byte.hpp>

class InstrumentCommand1 {
public:
	static  int32_t ID;

	InstrumentCommand1();
	void UpdateData(int gear_shift_ctrl, int eoc_mode_shift_ctrl, bool left_door_ctrl, bool right_door_ctrl, bool emergency_button_ctrl, bool dome_light_ctrl, bool atmospherelightsp_ctrl, int left_window_ctrl, int right_window_ctrl);
	void Reset();
	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 3, 'name': 'gear_shift_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|8]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_gear_shift_ctrl(int gear_shift_ctrl);

  // config detail: {'bit': 3, 'is_signed_var': False, 'len': 2, 'name': 'eoc_mode_shift_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_eoc_mode_shift_ctrl(int eoc_mode_shift_ctrl);

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 1, 'name': 'left_door_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_left_door_ctrl(bool left_door_ctrl);

  // config detail: {'bit': 9, 'is_signed_var': False, 'len': 1, 'name': 'right_door_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_right_door_ctrl(bool right_door_ctrl);

  // config detail: {'bit': 10, 'is_signed_var': False, 'len': 1, 'name': 'emergency_button_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_emergency_button_ctrl(bool emergency_button_ctrl);

  // config detail: {'bit': 11, 'is_signed_var': False, 'len': 1, 'name': 'dome_light_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_dome_light_ctrl(bool dome_light_ctrl);

  // config detail: {'bit': 12, 'is_signed_var': False, 'len': 1, 'name': 'atmospherelightsp_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  void set_p_atmospherelightsp_ctrl(bool atmospherelightsp_ctrl);

  // config detail: {'bit': 16, 'is_signed_var': True, 'len': 2, 'name': 'left_window_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_left_window_ctrl(int left_window_ctrl);

  // config detail: {'bit': 18, 'is_signed_var': True, 'len': 2, 'name': 'right_window_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_right_window_ctrl(int right_window_ctrl);

private:
	uint8_t data[8];
};



