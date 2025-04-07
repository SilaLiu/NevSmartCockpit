#include <libs/dtc_command.hpp>

int32_t DtcCommand::ID = 0x28C;

// public
DtcCommand::DtcCommand() { Reset(); }

void DtcCommand::UpdateData(int csc_flt_code1) {
  set_p_csc_flt_code1(csc_flt_code1);
}

void DtcCommand::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * DtcCommand::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'csc_flt_code1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void DtcCommand::set_p_csc_flt_code1(int csc_flt_code1) {
  // csc_flt_code1 = ProtocolData::BoundedValue(0, 255, csc_flt_code1);
  int x = csc_flt_code1;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[0] += to_set.return_byte_t();
  
}


