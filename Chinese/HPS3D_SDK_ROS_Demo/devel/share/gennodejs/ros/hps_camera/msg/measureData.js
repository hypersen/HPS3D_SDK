// Auto-generated. Do not edit!

// (in-package hps_camera.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let PointCloudData = require('./PointCloudData.js');

//-----------------------------------------------------------

class measureData {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.point_cloud_data = null;
    }
    else {
      if (initObj.hasOwnProperty('point_cloud_data')) {
        this.point_cloud_data = initObj.point_cloud_data
      }
      else {
        this.point_cloud_data = new PointCloudData();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type measureData
    // Serialize message field [point_cloud_data]
    bufferOffset = PointCloudData.serialize(obj.point_cloud_data, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type measureData
    let len;
    let data = new measureData(null);
    // Deserialize message field [point_cloud_data]
    data.point_cloud_data = PointCloudData.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += PointCloudData.getMessageSize(object.point_cloud_data);
    return length;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hps_camera/measureData';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd25e7f28a0c985f85d20386b940737b5';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    hps_camera/PointCloudData point_cloud_data
    
    ================================================================================
    MSG: hps_camera/PointCloudData
    float32[] x
    float32[] y
    float32[] z
    uint16 width
    uint16 height
    uint16 points
    
    uint16 distance_average
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new measureData(null);
    if (msg.point_cloud_data !== undefined) {
      resolved.point_cloud_data = PointCloudData.Resolve(msg.point_cloud_data)
    }
    else {
      resolved.point_cloud_data = new PointCloudData()
    }

    return resolved;
    }
};

module.exports = measureData;
