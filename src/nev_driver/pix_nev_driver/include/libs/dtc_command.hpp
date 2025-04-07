#pragma once
#include <libs/Byte.hpp>

class DtcCommand {
public:
	static  int32_t ID;

	DtcCommand();
	void UpdateData(int csc_flt_code1);
	void Reset();
	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'csc_flt_code1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_csc_flt_code1(int csc_flt_code1);

private:
	uint8_t data[8];
};



