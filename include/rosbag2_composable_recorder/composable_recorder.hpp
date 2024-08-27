// -*-c++-*---------------------------------------------------------------------------------------
// Copyright 2021 Bernd Pfrommer <bernd.pfrommer@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ROSBAG2_COMPOSABLE_RECORDER__COMPOSABLE_RECORDER_HPP_
#define ROSBAG2_COMPOSABLE_RECORDER__COMPOSABLE_RECORDER_HPP_

#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <rosbag2_transport/recorder.hpp>
#include <std_msgs/msg/int8.hpp>
#include <std_srvs/srv/trigger.hpp>

namespace rosbag2_composable_recorder
{
class ComposableRecorder : public rosbag2_transport::Recorder
{
public:
  explicit ComposableRecorder(const rclcpp::NodeOptions & options);
  ~ComposableRecorder();

private:
  // service callback function
  bool startStopRecording(
    const std::shared_ptr<std_srvs::srv::Trigger::Request> req,
    std::shared_ptr<std_srvs::srv::Trigger::Response> res);
  void timerCallback();

  // ---- variables
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr startStopRecordingService_;
  rclcpp::Publisher<std_msgs::msg::Int8>::SharedPtr statePublisher_;
  rclcpp::TimerBase::SharedPtr wallTimer_;
  bool isRecording_{false};
  std::string storageId_;
  int maxCacheSize_;
  std::string bagName_;
  std::string bagPrefix_;
};

}  // namespace rosbag2_composable_recorder
#endif  // ROSBAG2_COMPOSABLE_RECORDER__COMPOSABLE_RECORDER_HPP_
