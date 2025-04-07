#pragma once

#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <can_msgs/msg/frame.hpp>
#include <diagnostic_updater/diagnostic_updater.hpp>

// pix_nev_driver msgs - include_msgsName_list
#include <pix_nev_driver_msgs/msg/instrument_command1.hpp>
#include <pix_nev_driver_msgs/msg/instrument_command2.hpp>
#include <pix_nev_driver_msgs/msg/dtc_command.hpp>


// pix_nev_driver parse  - include_ParseName_list
#include <libs/instrument_command1.hpp>
#include <libs/instrument_command2.hpp>
#include <libs/dtc_command.hpp>


#define ERROR_THRESHOLD 5   // 严重级别延迟阈值
#define WARNING_THRESHOLD 3  // 警告级别延迟阈值
// 延迟记录
struct DelayRecording
{
  uint32_t count_eorro;  // 严重级别延迟累计 - 丢失5个周期
  uint32_t count_waring; // 警告级别延迟累计 - 丢失3个周期
};

namespace pix_nev_driver
{
namespace control_command
{

/**
 * @param pix_interface_driver_eorro pix_interface 严重超时阀值
 * @param pix_interface_driver_warn pix_interface 警告超时阀值
 */
struct TimeoutThresholdMs
{
  uint8_t pix_interface_driver_eorro;  // ms
  uint8_t pix_interface_driver_warn;  // ms
};

/**
 * @brief param structure of control command node
 * @param base_frame_id frame id of vehicle
 * @param loop_rate loop rate of publishers in hz
 * @param timeout_threshold_ms 超时阀值
 */
struct Param
{
  std::string base_frame_id;
  double loop_rate;
  TimeoutThresholdMs timeout_threshold_ms;
};

class ControlCommand : public rclcpp::Node
{
private:
  // Diagnostics Updater
  diagnostic_updater::Updater updater_;
  void onDelayedAlarm(diagnostic_updater::DiagnosticStatusWrapper & stat);

  // 订阅 pix_interface 底盘控制帧的下发延迟记录 - delay_recording_definition_list
  DelayRecording instrument_command1_delay_;
  DelayRecording instrument_command2_delay_;
  DelayRecording dtc_command_delay_;


  // 订阅 pix_interface 是否已经下发 - is_pix_interface_definition_list
  bool instrument_command1_issub_;
  bool instrument_command2_issub_;
  bool dtc_command_issub_;


private:
  // parameters of node
  Param param_;

  // subscribers - subscriber_member_list
  rclcpp::Subscription<pix_nev_driver_msgs::msg::InstrumentCommand1>::SharedPtr instrument_command1_sub_;
  rclcpp::Subscription<pix_nev_driver_msgs::msg::InstrumentCommand2>::SharedPtr instrument_command2_sub_;
  rclcpp::Subscription<pix_nev_driver_msgs::msg::DtcCommand>::SharedPtr dtc_command_sub_;


  // pix_nev_driver msgs -  msg_member_list
  pix_nev_driver_msgs::msg::InstrumentCommand1::ConstSharedPtr instrument_command1_ptr_;
  pix_nev_driver_msgs::msg::InstrumentCommand2::ConstSharedPtr instrument_command2_ptr_;
  pix_nev_driver_msgs::msg::DtcCommand::ConstSharedPtr dtc_command_ptr_;


  // control command structures - control_command_structure_list
  InstrumentCommand1 instrument_command1_parse_;
  InstrumentCommand2 instrument_command2_parse_;
  DtcCommand dtc_command_parse_;


  // msg received timestamp - msg_received_timestamp_list
  rclcpp::Time instrument_command1_received_time_;
  rclcpp::Time instrument_command2_received_time_;
  rclcpp::Time dtc_command_received_time_;


  // publishers to can card driver
  rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr can_frame_pub_;

  // publishing can msgs - publishing_can_msg_list
    can_msgs::msg::Frame::ConstSharedPtr instrument_command1_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr instrument_command2_can_ptr_;
  can_msgs::msg::Frame::ConstSharedPtr dtc_command_can_ptr_;


  // timer
  rclcpp::TimerBase::SharedPtr timer_;

public:
  ControlCommand(const rclcpp::NodeOptions & node_option);

  // calback functions - callback_function_prototype_list
  void callbackInstrumentCommand1(const pix_nev_driver_msgs::msg::InstrumentCommand1::ConstSharedPtr & msg);
  void callbackInstrumentCommand2(const pix_nev_driver_msgs::msg::InstrumentCommand2::ConstSharedPtr & msg);
  void callbackDtcCommand(const pix_nev_driver_msgs::msg::DtcCommand::ConstSharedPtr & msg);

  void timerCallback();

};

} // control_command
} // pix_nev_driver