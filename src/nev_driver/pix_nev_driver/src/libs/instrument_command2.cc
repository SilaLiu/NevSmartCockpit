#include <libs/instrument_command2.hpp>

int32_t InstrumentCommand2::ID = 0x28B;

// public
InstrumentCommand2::InstrumentCommand2() { Reset(); }

void InstrumentCommand2::UpdateData(int defrost_ctrl, int air_cod_ctrl, int air_cod_gear_ctrl, int air_cod_mod_ctrl, int air_cod_temp_ctrl, int ventilation_mod_ctrl, int in_loop_mod_ctrl, int reserve) {
  set_p_defrost_ctrl(defrost_ctrl);
  set_p_air_cod_ctrl(air_cod_ctrl);
  set_p_air_cod_gear_ctrl(air_cod_gear_ctrl);
  set_p_air_cod_mod_ctrl(air_cod_mod_ctrl);
  set_p_air_cod_temp_ctrl(air_cod_temp_ctrl);
  set_p_ventilation_mod_ctrl(ventilation_mod_ctrl);
  set_p_in_loop_mod_ctrl(in_loop_mod_ctrl);
  set_p_reserve(reserve);
}

void InstrumentCommand2::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * InstrumentCommand2::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'defrost_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void InstrumentCommand2::set_p_defrost_ctrl(int defrost_ctrl) {
  // defrost_ctrl = ProtocolData::BoundedValue(0, 7, defrost_ctrl);
  int x = defrost_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void InstrumentCommand2::set_p_air_cod_ctrl(int air_cod_ctrl) {
  // air_cod_ctrl = ProtocolData::BoundedValue(0, 7, air_cod_ctrl);
  int x = air_cod_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 16, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_gear_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void InstrumentCommand2::set_p_air_cod_gear_ctrl(int air_cod_gear_ctrl) {
  // air_cod_gear_ctrl = ProtocolData::BoundedValue(0, 7, air_cod_gear_ctrl);
  int x = air_cod_gear_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[2] += to_set.return_byte_t();
  
}

// config detail: {'bit': 24, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_mod_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void InstrumentCommand2::set_p_air_cod_mod_ctrl(int air_cod_mod_ctrl) {
  // air_cod_mod_ctrl = ProtocolData::BoundedValue(0, 7, air_cod_mod_ctrl);
  int x = air_cod_mod_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[3] += to_set.return_byte_t();
  
}

// config detail: {'bit': 32, 'is_signed_var': False, 'len': 8, 'name': 'air_cod_temp_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[16|32]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
void InstrumentCommand2::set_p_air_cod_temp_ctrl(int air_cod_temp_ctrl) {
  // air_cod_temp_ctrl = ProtocolData::BoundedValue(16, 32, air_cod_temp_ctrl);
  int x = air_cod_temp_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[4] += to_set.return_byte_t();
  
}

// config detail: {'bit': 40, 'is_signed_var': False, 'len': 4, 'name': 'ventilation_mod_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void InstrumentCommand2::set_p_ventilation_mod_ctrl(int ventilation_mod_ctrl) {
  // ventilation_mod_ctrl = ProtocolData::BoundedValue(0, 15, ventilation_mod_ctrl);
  int x = ventilation_mod_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 4);
  data[5] += to_set.return_byte_t();
  
}

// config detail: {'bit': 48, 'is_signed_var': False, 'len': 8, 'name': 'in_loop_mod_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void InstrumentCommand2::set_p_in_loop_mod_ctrl(int in_loop_mod_ctrl) {
  // in_loop_mod_ctrl = ProtocolData::BoundedValue(0, 7, in_loop_mod_ctrl);
  int x = in_loop_mod_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[6] += to_set.return_byte_t();
  
}

// config detail: {'bit': 56, 'is_signed_var': False, 'len': 8, 'name': 'reserve', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void InstrumentCommand2::set_p_reserve(int reserve) {
  // reserve = ProtocolData::BoundedValue(0, 7, reserve);
  int x = reserve;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[7] += to_set.return_byte_t();
  
}


