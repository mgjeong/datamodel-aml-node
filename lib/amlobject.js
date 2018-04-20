/*******************************************************************************
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *******************************************************************************/

//Module dependencies.
var amlObject = require('../build/Release/aml.node'),
    amlData = require('./amldata.js');

//Expose bindings as the module.
exports = module.exports = amlObject;

var namlObject;

/**
 * @class This class represents AMLObject.
 *
 * Application can pass deviceId and timestamp or
 * deviceId, timestamp and id.
 *
 * @param {string} deviceId -Device id of AMLObject.
 * @param {string} timestamp -Timestamp value of AMLObject delivered by device.
 * @param {string} id -id of AMLObject.
 *
 * @throws {AMLErrorCode} AML exception.
 * @constructor
 */
var AMLObject = (exports.AMLObject = function(deviceId, timestamp, id) {
    if (typeof id === 'undefined') {
        this.namlObject = new amlObject.NAMLObject(deviceId, timestamp);
    } else {
        this.namlObject = new amlObject.NAMLObject(deviceId, timestamp, id);
    }
});

/**
 * Add AMLData to AMLObject using AMLData key.
 *
 * @param {string} name -AMLData key.
 * @param {AMLData} data -AMLData value.
 *
 * @throws {AMLErrorCode} AML exception.
 */
AMLObject.prototype.addData = function(name, data) {
    this.namlObject.addData(name, data.getAddonObj());
};

/**
 * Get AMLData for the given key.
 *
 * @param {string} name -AMLData key.
 *
 * @return {AMLData} AMLData corresponding to given key.
 * @throws {AMLErrorCode} AML exception.
 */
AMLObject.prototype.getData = function(name) {
    var amlDataObj = new amlData.AMLData();
    amlDataObj.setAddonObj(this.namlObject.getData(name));
    return amlDataObj;
};

/**
 * Get string list of AMLObject's amlData keys.
 *
 * @return {Array} Array of string data's keys value list.
 * @throws {AMLErrorCode} AML exception.
 */
AMLObject.prototype.getDataNames = function() {
    return this.namlObject.getDataNames();
};

/**
 * Get device ID saved on AMLObject.
 *
 * @return {string} String value of device Id.
 * @throws {AMLErrorCode} AML exception.
 */
AMLObject.prototype.getDeviceId = function() {
    return this.namlObject.getDeviceId();
};

/**
 * Get timestamp that is delivered by device.
 *
 * @return {string} String value of timestamp.
 * @throws {AMLErrorCode} AML exception.
 */
AMLObject.prototype.getTimeStamp = function() {
    return this.namlObject.getTimeStamp();
};

/**
 * Get ID of AMLObject.
 *
 * @return {string} AML object id.
 * @throws {AMLErrorCode} AML exception.
 */
AMLObject.prototype.getId = function() {
    return this.namlObject.getId();
};

//This methods are being used internally by aml-js layer
AMLObject.prototype.getAddonObj = function() {
    return this.namlObject;
};

AMLObject.prototype.setAddonObj = function(amlObject) {
    this.namlObject = amlObject;
};
