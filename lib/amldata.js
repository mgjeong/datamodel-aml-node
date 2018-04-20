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
var amlData = require('../build/Release/aml.node');

//Expose bindings as the module.
exports = (module.exports = amlData);

var namlData;

/**
 * @class  This class have RawData map which have key-value pair.
 * @constructor
 */
var AMLData = (exports.AMLData = function() {
    this.namlData = new amlData.NAMLData();
});

/**
 * Set key and string type value/string vector type/AMLData type value  pair on AMLData.
 *
 * @param {string} key - AMLData key.
 * @param {string}  {Array}  {AMLData} value - AMLData value
 *
 * @throws {AMLErrorCode} AML exception.
 */
AMLData.prototype.setValue = function(key, value) {
    if (typeof value === 'string') {
        return this.namlData.setValue(key, value);
    } else if (value instanceof AMLData) {
        return this.namlData.setAMLDataValue(key, value.getAddonObj());
    }
    return this.namlData.setVectorValue(key, value);
};

/**
 *  Get string which matched key in a AMLData's AMLMap.
 *
 * @param {string} key - AMLData key.
 *
 * @return {string}  String value which matched using key on AMLMap.
 * @throws {AMLErrorCode} AML exception.
 */
AMLData.prototype.getValueToStr = function(key) {
    return this.namlData.getValueToStr(key);
};

/**
 *  Get string array which matched key in a AMLData's AMLMap.
 *
 * @param {string} key - AMLData key.
 *
 * @return {Array} String array value which matched using key on AMLMap.
 * @throws {AMLErrorCode} AML exception.
 */
AMLData.prototype.getValueToStrArr = function(key) {
    return this.namlData.getValueToStrArr(key);
};

/**
 *  Get AMLData which matched key in a AMLData's AMLMap.
 *
 * @param {string} key - AMLData key.
 *
 * @return {AMLData} AMLData value which matched using key on AMLMap.
 * @throws {AMLErrorCode} AML exception.
 */
AMLData.prototype.getValueToAMLData = function(key) {
    var nAMLData = this.namlData.getValueToAMLData(key);
    var jsAMLData = new AMLData();
    jsAMLData.setAddonObj(nAMLData);
    return jsAMLData;
};

/**
 *  Get all the keys in AMLData.
 *
 * @return {Array} String array containing keys.
 * @throws {AMLErrorCode} AML exception.
 */
AMLData.prototype.getKeys = function() {
    return this.namlData.getKeys();
};

/**
 *  Get AML Value type for the given key.
 *
 * @param {string} key - AMLData key.
 *
 * @return {AMLValueType} AML value type.
 * @throws {AMLErrorCode} AML exception.
 */
AMLData.prototype.getValueType = function(key) {
    return this.namlData.getValueType(key);
};

//This methods are being used internally by aml-js layer
AMLData.prototype.getAddonObj = function() {
    return this.namlData;
};

AMLData.prototype.setAddonObj = function(amlDataObj) {
    this.namlData = amlDataObj;
};
