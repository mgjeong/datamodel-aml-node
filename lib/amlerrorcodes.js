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
var amlErrorCodes = require('../build/Release/aml.node');

//Expose bindings as the module.
exports = module.exports = amlErrorCodes;

/**
 * Represents AMl stack codes will be received in exception.
 */
var AMLErrorCode = (exports.AMLErrorCode = {
    AML_OK: 0,
    AML_INVALID_PARAM: 1,
    AML_INVALID_FILE_PATH: 2,
    AML_INVALID_AML_SCHEMA: 3,
    AML_INVALID_XML_STR: 4,
    AML_NOT_MATCH_TO_AML_MODEL: 5,
    AML_INVALID_BYTE_STR: 6,
    AML_SERIALIZE_FAIL: 7,
    AML_NO_MEMORY: 8,
    AML_KEY_NOT_EXIST: 9,
    AML_KEY_ALREADY_EXIST: 10,
    AML_WRONG_GETTER_TYPE: 11,
    AML_API_NOT_ENABLED: 12,
});

var amlValueType = require('../build/Release/aml.node');
exports = module.exports = amlValueType;

/**
 * Represents AMLValueType.
 */
var AMLValueType = (exports.AMLValueType = {
    /**  String */
    String: 0,
    /**  StringArray */
    StringArray: 1,
    /**  AMLData TOPIC */
    AMLData: 2,
});
