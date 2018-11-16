
"use strict";

let SetHardSync = require('./SetHardSync.js')
let MissionWpUpload = require('./MissionWpUpload.js')
let QueryDroneVersion = require('./QueryDroneVersion.js')
let SetupCameraStream = require('./SetupCameraStream.js')
let StereoVGASubscription = require('./StereoVGASubscription.js')
let MissionWpAction = require('./MissionWpAction.js')
let MissionHpAction = require('./MissionHpAction.js')
let SetLocalPosRef = require('./SetLocalPosRef.js')
let MissionHpUpload = require('./MissionHpUpload.js')
let MFIOConfig = require('./MFIOConfig.js')
let DroneTaskControl = require('./DroneTaskControl.js')
let SDKControlAuthority = require('./SDKControlAuthority.js')
let MissionWpGetSpeed = require('./MissionWpGetSpeed.js')
let SendMobileData = require('./SendMobileData.js')
let MissionStatus = require('./MissionStatus.js')
let MissionWpGetInfo = require('./MissionWpGetInfo.js')
let MissionHpResetYaw = require('./MissionHpResetYaw.js')
let MissionHpUpdateRadius = require('./MissionHpUpdateRadius.js')
let Activation = require('./Activation.js')
let DroneArmControl = require('./DroneArmControl.js')
let CameraAction = require('./CameraAction.js')
let MissionHpGetInfo = require('./MissionHpGetInfo.js')
let MFIOSetValue = require('./MFIOSetValue.js')
let MissionHpUpdateYawRate = require('./MissionHpUpdateYawRate.js')
let Stereo240pSubscription = require('./Stereo240pSubscription.js')
let StereoDepthSubscription = require('./StereoDepthSubscription.js')
let MissionWpSetSpeed = require('./MissionWpSetSpeed.js')

module.exports = {
  SetHardSync: SetHardSync,
  MissionWpUpload: MissionWpUpload,
  QueryDroneVersion: QueryDroneVersion,
  SetupCameraStream: SetupCameraStream,
  StereoVGASubscription: StereoVGASubscription,
  MissionWpAction: MissionWpAction,
  MissionHpAction: MissionHpAction,
  SetLocalPosRef: SetLocalPosRef,
  MissionHpUpload: MissionHpUpload,
  MFIOConfig: MFIOConfig,
  DroneTaskControl: DroneTaskControl,
  SDKControlAuthority: SDKControlAuthority,
  MissionWpGetSpeed: MissionWpGetSpeed,
  SendMobileData: SendMobileData,
  MissionStatus: MissionStatus,
  MissionWpGetInfo: MissionWpGetInfo,
  MissionHpResetYaw: MissionHpResetYaw,
  MissionHpUpdateRadius: MissionHpUpdateRadius,
  Activation: Activation,
  DroneArmControl: DroneArmControl,
  CameraAction: CameraAction,
  MissionHpGetInfo: MissionHpGetInfo,
  MFIOSetValue: MFIOSetValue,
  MissionHpUpdateYawRate: MissionHpUpdateYawRate,
  Stereo240pSubscription: Stereo240pSubscription,
  StereoDepthSubscription: StereoDepthSubscription,
  MissionWpSetSpeed: MissionWpSetSpeed,
};
