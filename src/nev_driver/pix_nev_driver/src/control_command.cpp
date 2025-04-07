#include <pix_nev_driver/control_command.hpp>

namespace pix_nev_driver
{
namespace control_command
{
ControlCommand::ControlCommand(const rclcpp::NodeOptions & node_options) 
: Node("control_command", node_options),
updater_(this)
{
  // init delay_recording_init_list is_pix_interface_init_list
  instrument_command1_delay_.count_eorro = 0;
  instrument_command1_delay_.count_waring = 0;
  instrument_command2_delay_.count_eorro = 0;
  instrument_command2_delay_.count_waring = 0;
  dtc_command_delay_.count_eorro = 0;
  dtc_command_delay_.count_waring = 0;

  instrument_command1_issub_ = false;
  instrument_command2_issub_ = false;
  dtc_command_issub_ = false;


  float pix_interface_driver_period_ms =
    declare_parameter("pix_interface_driver_period_ms", 50.0);
  param_.timeout_threshold_ms.pix_interface_driver_eorro  = pix_interface_driver_period_ms*ERROR_THRESHOLD;
  param_.timeout_threshold_ms.pix_interface_driver_warn  = pix_interface_driver_period_ms*WARNING_THRESHOLD;

  // ros params
  param_.base_frame_id = declare_parameter("base_frame_id", "base_link");
  param_.loop_rate = declare_parameter("loop_rate", 50.0);

  // initialize msg received time, make reservation of data size - msg_reveived_timestamp_instance_list
  instrument_command1_received_time_ = this->now();
  instrument_command2_received_time_ = this->now();
  dtc_command_received_time_ = this->now();


  using std::placeholders::_1;

  // Diagnostics Updater
  updater_.setHardwareID("pix_nev_driver-ControlCommand");
  updater_.add("delayed_alarm", this, &ControlCommand::onDelayedAlarm);

  /* subscriber */
  {
    // from nev driver autoware interface - subscribe_instance_list
      instrument_command1_sub_ = create_subscription<pix_nev_driver_msgs::msg::InstrumentCommand1>("/pix_nev/instrument_command1", 10, std::bind(&ControlCommand::callbackInstrumentCommand1, this, _1));
    instrument_command2_sub_ = create_subscription<pix_nev_driver_msgs::msg::InstrumentCommand2>("/pix_nev/instrument_command2", 10, std::bind(&ControlCommand::callbackInstrumentCommand2, this, _1));
    dtc_command_sub_ = create_subscription<pix_nev_driver_msgs::msg::DtcCommand>("/pix_nev/dtc_command", 10, std::bind(&ControlCommand::callbackDtcCommand, this, _1));

  }

  /* publisher */
  {
    // to socketcan drivier
    can_frame_pub_ = create_publisher<can_msgs::msg::Frame>("output/can_tx", rclcpp::QoS{500});
  }

  {
    // timer
    timer_ = rclcpp::create_timer(
      this, get_clock(), rclcpp::Rate(param_.loop_rate).period(),
      std::bind(&ControlCommand::timerCallback, this));
  }
}

// calback functions -- callback_functions_list


void ControlCommand::callbackInstrumentCommand1(const pix_nev_driver_msgs::msg::InstrumentCommand1::ConstSharedPtr & msg)
{
  instrument_command1_issub_ = true;
  instrument_command1_received_time_ = this->now();
  instrument_command1_ptr_ = msg;
  instrument_command1_parse_.Reset();
  instrument_command1_parse_.UpdateData(msg->gear_shift_ctrl, msg->eoc_mode_shift_ctrl, msg->left_door_ctrl, msg->right_door_ctrl, msg->emergency_button_ctrl, msg->dome_light_ctrl, msg->atmospherelightsp_ctrl, msg->left_window_ctrl, msg->right_window_ctrl);
  can_msgs::msg::Frame instrument_command1_can_msg;
  instrument_command1_can_msg.header.stamp = msg->header.stamp;
  instrument_command1_can_msg.dlc = 8;
  instrument_command1_can_msg.id = instrument_command1_parse_.ID;
  instrument_command1_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = instrument_command1_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    instrument_command1_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(instrument_command1_can_msg);
}

    

void ControlCommand::callbackInstrumentCommand2(const pix_nev_driver_msgs::msg::InstrumentCommand2::ConstSharedPtr & msg)
{
  instrument_command2_issub_ = true;
  instrument_command2_received_time_ = this->now();
  instrument_command2_ptr_ = msg;
  instrument_command2_parse_.Reset();
  instrument_command2_parse_.UpdateData(msg->defrost_ctrl, msg->air_cod_ctrl, msg->air_cod_gear_ctrl, msg->air_cod_mod_ctrl, msg->air_cod_temp_ctrl, msg->ventilation_mod_ctrl, msg->in_loop_mod_ctrl, msg->reserve);
  can_msgs::msg::Frame instrument_command2_can_msg;
  instrument_command2_can_msg.header.stamp = msg->header.stamp;
  instrument_command2_can_msg.dlc = 8;
  instrument_command2_can_msg.id = instrument_command2_parse_.ID;
  instrument_command2_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = instrument_command2_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    instrument_command2_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(instrument_command2_can_msg);
}

    

void ControlCommand::callbackDtcCommand(const pix_nev_driver_msgs::msg::DtcCommand::ConstSharedPtr & msg)
{
  dtc_command_issub_ = true;
  dtc_command_received_time_ = this->now();
  dtc_command_ptr_ = msg;
  dtc_command_parse_.Reset();
  dtc_command_parse_.UpdateData(msg->csc_flt_code1);
  can_msgs::msg::Frame dtc_command_can_msg;
  dtc_command_can_msg.header.stamp = msg->header.stamp;
  dtc_command_can_msg.dlc = 8;
  dtc_command_can_msg.id = dtc_command_parse_.ID;
  dtc_command_can_msg.is_extended = false;
  uint8_t *signal_bits;
  signal_bits = dtc_command_parse_.get_data();
  for (int i = 0; i < 8; i++)
  {
    dtc_command_can_msg.data[i] = *signal_bits;
    signal_bits += 1;
  }
  can_frame_pub_->publish(dtc_command_can_msg);
}

    

void ControlCommand::onDelayedAlarm(diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  const std::string error_msg = "[ReportConverter]: Timeout";
  const auto diag_level = diagnostic_msgs::msg::DiagnosticStatus::OK;
  stat.summary(diag_level, error_msg);
  // on_delayed_alarm_list
  
  stat.addf("instrument_command1 count_eorro", "%%d", instrument_command1_delay_.count_eorro); 
  stat.addf("instrument_command1 count_warn", "%%d", instrument_command1_delay_.count_waring);
    
  stat.addf("instrument_command2 count_eorro", "%%d", instrument_command2_delay_.count_eorro); 
  stat.addf("instrument_command2 count_warn", "%%d", instrument_command2_delay_.count_waring);
    
  stat.addf("dtc_command count_eorro", "%%d", dtc_command_delay_.count_eorro); 
  stat.addf("dtc_command count_warn", "%%d", dtc_command_delay_.count_waring);
    
}

void ControlCommand::timerCallback()
{

  // 如果存在一个为flase，表示初始化没有下发 - if_pix_interface_definition_list
  if(!instrument_command1_issub_) return;
  if(!instrument_command2_issub_) return;
  if(!dtc_command_issub_) return;

  const rclcpp::Time current_time = this->now();
  // if_msg_received_timestamp_list


  const double instrument_command1_delta_time_ms =
    (current_time - instrument_command1_received_time_).seconds() * 1000.0;
  if(instrument_command1_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    instrument_command1_delay_.count_eorro++;
  }else if (instrument_command1_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    instrument_command1_delay_.count_waring++;
  }

  const double instrument_command2_delta_time_ms =
    (current_time - instrument_command2_received_time_).seconds() * 1000.0;
  if(instrument_command2_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    instrument_command2_delay_.count_eorro++;
  }else if (instrument_command2_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    instrument_command2_delay_.count_waring++;
  }

  const double dtc_command_delta_time_ms =
    (current_time - dtc_command_received_time_).seconds() * 1000.0;
  if(dtc_command_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_eorro){
    dtc_command_delay_.count_eorro++;
  }else if (dtc_command_delta_time_ms > param_.timeout_threshold_ms.pix_interface_driver_warn){
    dtc_command_delay_.count_waring++;
  }
}

} // namespace control_command
} // namespace pix_nev_driver
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(pix_nev_driver::control_command::ControlCommand)