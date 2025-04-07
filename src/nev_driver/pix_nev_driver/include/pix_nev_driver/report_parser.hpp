#pragma once

#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/header.hpp>

#include <can_msgs/msg/frame.hpp>


// pix_nev_driver_msgs - include_msg_list
#include <pix_nev_driver_msgs/msg/instrument_fb1.hpp>
#include <pix_nev_driver_msgs/msg/instrument_fb2.hpp>


// protocol libs - include_hpp_list
#include <libs/instrument_fb1.hpp>
#include <libs/instrument_fb2.hpp>


namespace pix_nev_driver
{
namespace report_parser
{

/**
 * @brief param structure of report parser node
 * @param base_frame_id frame id of vehicle
 * @param loop_rate loop rate of publishers in hz
 */
struct Param
{
  std::string base_frame_id;
  double loop_rate;
};

class ReportParser : public rclcpp::Node
{
private:
  // parameters of node
  Param param_;

  // subscribers from socketcan interface
  rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr can_frame_sub_;

  // publishers - publisher_list
  rclcpp::Publisher<pix_nev_driver_msgs::msg::InstrumentFb1>::SharedPtr instrument_fb1_pub_;
  rclcpp::Publisher<pix_nev_driver_msgs::msg::InstrumentFb2>::SharedPtr instrument_fb2_pub_;


  // can frame entities - publisher_msg_list
  InstrumentFb1 instrument_fb1_parser_;
  InstrumentFb2 instrument_fb2_parser_;

  
public:
  ReportParser(const rclcpp::NodeOptions & node_option);

  // callback
  /// @brief callback function of can Frame msgs, to store the data to member variable
  void callbackCan(const can_msgs::msg::Frame::ConstSharedPtr & msg);
};
} // report_parser
} // pix_nev_driver