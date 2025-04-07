#include <pix_nev_driver/report_parser.hpp>

namespace pix_nev_driver
{
namespace report_parser
{
ReportParser::ReportParser(const rclcpp::NodeOptions & node_option) 
: Node("report_parser", node_option)
{
  // ros params
  param_.base_frame_id = declare_parameter("base_frame_id", "base_link");
  param_.loop_rate = declare_parameter("loop_rate", 50.0);

  using std::placeholders::_1;

  /* subscriber */
  {
    // from pix driver autoware interface
    can_frame_sub_ = create_subscription<can_msgs::msg::Frame>(
      "input/can_rx", 500, std::bind(&ReportParser::callbackCan, this, _1));
  }

  /* publisher - publisher_instance_list*/
  {
    instrument_fb1_pub_ = create_publisher<pix_nev_driver_msgs::msg::InstrumentFb1>("/pix_nev/instrument_fb1", rclcpp::QoS{10});
    instrument_fb2_pub_ = create_publisher<pix_nev_driver_msgs::msg::InstrumentFb2>("/pix_nev/instrument_fb2", rclcpp::QoS{10});
 
  }
}

// callback can
void ReportParser::callbackCan(const can_msgs::msg::Frame::ConstSharedPtr & msg)
{
  std_msgs::msg::Header header;
  header.frame_id = param_.base_frame_id;
  header.stamp = msg->header.stamp;

  // pix_msg  - report_msg_list
  pix_nev_driver_msgs::msg::InstrumentFb1 instrument_fb1_msg;
  pix_nev_driver_msgs::msg::InstrumentFb2 instrument_fb2_msg;


  // can - parser_case_code_list
  uint8_t byte_temp[8];
  switch (msg->id)
  {

  case InstrumentFb1::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    instrument_fb1_parser_.update_bytes(byte_temp);
    instrument_fb1_parser_.Parse();

    instrument_fb1_msg.header = header;
    instrument_fb1_msg.gear_shift_sta = instrument_fb1_parser_.gear_shift_sta_;
    instrument_fb1_msg.eco_sta = instrument_fb1_parser_.eco_sta_;
    instrument_fb1_msg.left_door_sta = instrument_fb1_parser_.left_door_sta_;
    instrument_fb1_msg.right_door_sta = instrument_fb1_parser_.right_door_sta_;
    instrument_fb1_msg.reserve = instrument_fb1_parser_.reserve_;
    instrument_fb1_msg.dome_light_sta = instrument_fb1_parser_.dome_light_sta_;
    instrument_fb1_msg.atmospherelightsp_sta = instrument_fb1_parser_.atmospherelightsp_sta_;
    instrument_fb1_msg.left_window_sta = instrument_fb1_parser_.left_window_sta_;
    instrument_fb1_msg.right_window_sta = instrument_fb1_parser_.right_window_sta_;

    instrument_fb1_pub_->publish(instrument_fb1_msg);
    break;
    
  case InstrumentFb2::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    instrument_fb2_parser_.update_bytes(byte_temp);
    instrument_fb2_parser_.Parse();

    instrument_fb2_msg.header = header;
    instrument_fb2_msg.defrost_sta = instrument_fb2_parser_.defrost_sta_;
    instrument_fb2_msg.air_cod_sta = instrument_fb2_parser_.air_cod_sta_;
    instrument_fb2_msg.air_cod_gear_sta = instrument_fb2_parser_.air_cod_gear_sta_;
    instrument_fb2_msg.air_cod_mod_sta = instrument_fb2_parser_.air_cod_mod_sta_;
    instrument_fb2_msg.air_cod_temp_sta = instrument_fb2_parser_.air_cod_temp_sta_;
    instrument_fb2_msg.ventilation_mod_sta = instrument_fb2_parser_.ventilation_mod_sta_;
    instrument_fb2_msg.in_loop_mod_sta = instrument_fb2_parser_.in_loop_mod_sta_;
    instrument_fb2_msg.reserve = instrument_fb2_parser_.reserve_;

    instrument_fb2_pub_->publish(instrument_fb2_msg);
    break;
    
  default:
    break;
  }
}

} // namespace report_parser
} // namespace pix_nev_driver
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(pix_nev_driver::report_parser::ReportParser)