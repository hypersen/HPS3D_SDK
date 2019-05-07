// Auto-generated. Do not edit!

// (in-package hps_camera.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class cameraRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.client_node_name = null;
    }
    else {
      if (initObj.hasOwnProperty('client_node_name')) {
        this.client_node_name = initObj.client_node_name
      }
      else {
        this.client_node_name = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type cameraRequest
    // Serialize message field [client_node_name]
    bufferOffset = _serializer.string(obj.client_node_name, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type cameraRequest
    let len;
    let data = new cameraRequest(null);
    // Deserialize message field [client_node_name]
    data.client_node_name = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.client_node_name.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'hps_camera/cameraRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5fdb91215c50cf236532756057951fad';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string client_node_name
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new cameraRequest(null);
    if (msg.client_node_name !== undefined) {
      resolved.client_node_name = msg.client_node_name;
    }
    else {
      resolved.client_node_name = ''
    }

    return resolved;
    }
};

class cameraResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.control_cmd = null;
    }
    else {
      if (initObj.hasOwnProperty('control_cmd')) {
        this.control_cmd = initObj.control_cmd
      }
      else {
        this.control_cmd = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type cameraResponse
    // Serialize message field [control_cmd]
    bufferOffset = _serializer.string(obj.control_cmd, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type cameraResponse
    let len;
    let data = new cameraResponse(null);
    // Deserialize message field [control_cmd]
    data.control_cmd = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.control_cmd.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'hps_camera/cameraResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '39d7f0ad14e9dfe7d61de4ee6470c2d8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string control_cmd
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new cameraResponse(null);
    if (msg.control_cmd !== undefined) {
      resolved.control_cmd = msg.control_cmd;
    }
    else {
      resolved.control_cmd = ''
    }

    return resolved;
    }
};

module.exports = {
  Request: cameraRequest,
  Response: cameraResponse,
  md5sum() { return '856731728679b0f365031a50c1aa4795'; },
  datatype() { return 'hps_camera/camera'; }
};
