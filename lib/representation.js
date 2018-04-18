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
var representation = require('../build/Release/aml.node'),
    amlObject = require('./amlobject.js');

//Expose bindings as the module.
exports = module.exports = representation;

var nrepresentation;

/**
 * @class  This class converts between AMLObject, AML(XML) string, AML(Protobuf) byte.
 *
 * @param {string} filePath -File path that contains data model information.
 * @throws {AMLErrorCode} AML exception.
 *
 * @constructor
 */
var Representation = (exports.Representation = function(filePath) {
    this.nrepresentation = new representation.NRepresentation(filePath);
});

/**
 * Converts AMLObject to AML(XML) string to match the AML model information
 * which is set by constructor.
 *
 * @param {AMLObject} amlObject -AMLObject to be converted.
 *
 * @return {string} Converted string from amlObject.
 * @throws {AMLErrorCode} AML exception.
 */
Representation.prototype.dataToAml = function(amlObject) {
    return this.nrepresentation.dataToAml(amlObject.getAddonObj());
};

/**
 * Converts AML(XML) string to AMLObject to match the AML model information
 * which is set by constructor.
 *
 * @param {string} amlString - AML(XML) string to be converted.
 *
 * @return {AMLObject} Instance converted from AML(XML) string.
 * @throws {AMLErrorCode} AML exception.
 */
Representation.prototype.amlToData = function(amlString) {
    //The values for creating AMLObject is required, as addon will throw exception
    var amlObj = new amlObject.AMLObject('device123', 'time123', '');
    amlObj.setAddonObj(this.nrepresentation.amlToData(amlString));
    return amlObj;
};

/**
 * Converts AMLObject to Protobuf byte data(string) to match the AML model information
 * which is set by constructor.
 *
 * @param {AMLObject} amlObject -AMLObject to be converted.
 *
 * @return {string} Protobuf byte data(string) converted from amlObject.
 * @throws {AMLErrorCode} AML exception.
 */
Representation.prototype.dataToByte = function(amlObject) {
    return this.nrepresentation.dataToByte(amlObject.getAddonObj());
};

/**
 * Converts Protobuf byte data to AMLObject to match the AML model information
 * which is set by constructor.
 *
 * @param {string} byteString -Protobuf byte data(string) to be converted.
 * @param {int} length -Length of Protobuf byte data(string).
 *
 * @return {AMLObject} Instance converted from byte string.
 * @throws {AMLErrorCode} AML exception.
 */
Representation.prototype.byteToData = function(byteString, length) {
    //The values for creating AMLObject is required, as addon will throw exception
    var amlObj = new amlObject.AMLObject('device123', 'time123', '');
    amlObj.setAddonObj(this.nrepresentation.byteToData(byteString, length));
    return amlObj;
};

/**
 * Get AutomationML SystemUnitClassLib's unique ID.
 *
 * @return {string} String value of AML SystemUnitClassLIb's ID.
 * @throws {AMLErrorCode} AML exception.
 */
Representation.prototype.getRepresentationId = function() {
    return this.nrepresentation.getRepresentationId();
};

/**
 * Get AMLObject that contains configuration data which is present in RoleClassLib.
 *
 * @return {AMLObject} AMLObject that has configuration data.
 * @throws {AMLErrorCode} AML exception.
 */
Representation.prototype.getConfigInfo = function() {
    var nAMLObject = this.nrepresentation.getConfigInfo();
    //The values for creating AMLObject is required, as addon will throw exception
    var jsAMLObject = new amlObject.AMLObject('device123', 'time123', '');
    var jsAMLObject = new amlObject.AMLObject();
    jsAMLObject.setAddonObj(nAMLObject);
    return jsAMLObject;
};
