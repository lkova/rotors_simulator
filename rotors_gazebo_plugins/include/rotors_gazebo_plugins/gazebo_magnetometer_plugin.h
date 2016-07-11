/*
 * Copyright 2015 Fadri Furrer, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Michael Burri, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Mina Kamel, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Janosch Nikolic, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Markus Achtelik, ASL, ETH Zurich, Switzerland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ROTORS_GAZEBO_PLUGINS_MAGNETOMETER_PLUGIN_H
#define ROTORS_GAZEBO_PLUGINS_MAGNETOMETER_PLUGIN_H

#include <random>

#include <gazebo/common/common.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <mav_msgs/default_topics.h>
#include <ros/ros.h>
#include <sensor_msgs/MagneticField.h>

#include "rotors_gazebo_plugins/common.h"
#include "rotors_gazebo_plugins/sdf_api_wrapper.hpp"

namespace gazebo {
// Default magnetic field [Tesla] in NED frame, obtained from World Magnetic
// Model: (http://www.ngdc.noaa.gov/geomag-web/#igrfwmm) for Zurich:
// lat=+47.3667degN, lon=+8.5500degE, h=+500m, WGS84
static const SdfVector3 kDefaultRefMagField(0.000021493, 0.000000815, 0.000042795);

class GazeboMagnetometerPlugin : public ModelPlugin {
 public:
  typedef std::normal_distribution<> NormalDistribution;
  typedef std::uniform_real_distribution<> UniformDistribution;

  GazeboMagnetometerPlugin();
  virtual ~GazeboMagnetometerPlugin();

 protected:
  void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);
  void OnUpdate(const common::UpdateInfo&);

 private:
  std::string namespace_;
  std::string magnetometer_topic_;
  ros::NodeHandle* node_handle_;
  ros::Publisher magnetometer_pub_;
  std::string frame_id_;

  // Pointer to the world
  physics::WorldPtr world_;
  // Pointer to the model
  physics::ModelPtr model_;
  // Pointer to the link
  physics::LinkPtr link_;
  // Pointer to the update event connection
  event::ConnectionPtr updateConnection_;

  math::Vector3 mag_W_;

  sensor_msgs::MagneticField mag_message_;

  NormalDistribution noise_n_[3];

  std::random_device random_device_;
  std::mt19937 random_generator_;
};
}

#endif // ROTORS_GAZEBO_PLUGINS_MAGNETOMETER_PLUGIN_H
