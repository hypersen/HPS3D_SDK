// Auto-generated. Do not edit!

// (in-package hps_camera.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class distance {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.distance_average = null;
    }
    else {
      if (initObj.hasOwnProperty('distance_average')) {
        this.distance_average = initObj.distance_average
      }
      else {
        this.distance_average = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type distance
    // Serialize message field [distance_average]
    bufferOffset = _serializer.uint16(obj.distance_average, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type distance
    let len;
    let data = new distance(null);
    // Deserialize message field [distance_average]
    data.distance_average = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 2;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hps_camera/distance';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7abbfa2a9d95604277f1b4a37d989bb6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint16 distance_average
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new distance(null);
    if (msg.distance_average !== undefined) {
      resolved.distance_average = msg.distance_average;
    }
    else {
      resolved.distance_average = 0
    }

    return resolved;
    }
};

module.exports = distance;
