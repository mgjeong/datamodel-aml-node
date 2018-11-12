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

var aml = require('../');

function printAMLData(amlData, depth) {
    var indent = '';
    for (j = 0; j < depth; j++) {
        indent += '    ';
    }
    console.log(indent + '{');
    var keys = amlData.getKeys();
    for (var k = 0; k < keys.length; k++) {
        var log = indent + '    "' + keys[k] + '" : ';
        var valueTye = amlData.getValueType(keys[k]);
        if (aml.AMLValueType.String == valueTye) {
            var valStr = amlData.getValueToStr(keys[k]);
            console.log(log + valStr);
        } else if (aml.AMLValueType.StringArray == valueTye) {
            var valStrArr = amlData.getValueToStrArr(keys[k]);
            console.log(log + valStrArr);
        } else if (aml.AMLValueType.AMLData == valueTye) {
            var valAMLData = amlData.getValueToAMLData(keys[k]);
            console.log(log);
            printAMLData(valAMLData, depth + 1);
        }
    }
    console.log(indent + '}');
}

function printAMLObject(amlObj) {
    console.log('{');
    console.log('    "device" : ' + amlObj.getDeviceId() + ',');
    console.log('    "timestamp" : ' + amlObj.getTimeStamp() + ',');
    console.log('    "id" : ' + amlObj.getId() + ',');

    var dataNames = amlObj.getDataNames();
    for (i = 0; i < dataNames.length; i++) {
        var amlData = amlObj.getData(dataNames[i]);
        console.log('    "' + dataNames[i] + '" : ');
        printAMLData(amlData, 1);
    }
    console.log('}');
}

//Create representation for given aml file
var representation = new aml.Representation('sample_data_model.aml');
console.log('RepresentationId is: ' + representation.getRepresentationId());

var amlObject = representation.getConfigInfo();
printAMLObject(amlObject);
console.log(
    '\n-------------------------------------------------------------\n'
);

// create AMLObject
var deviceId = 'SAMPLE001';
var timeStamp = '123456789';

var amlObj = new aml.AMLObject(deviceId, timeStamp);

// create "Model" data
var model = new aml.AMLData();
model.setValue('a', 'Model_107.113.97.248');
model.setValue('b', 'SR-P7-970');

// create "Sample" data
var axis = new aml.AMLData();
axis.setValue('x', '20');
axis.setValue('y', '110');
axis.setValue('z', '80');

var info = new aml.AMLData();
info.setValue('id', 'f437da3b');
info.setValue('axis', axis);

var appendix = ['52303', '935', '1442'];

var sample = new aml.AMLData();
sample.setValue('info', info);
sample.setValue('appendix', appendix);

amlObj.addData('Model', model);
amlObj.addData('Sample', sample);

printAMLObject(amlObj);

// Convert AMLObject to AMLstring(XML)
var aml_string = representation.dataToAml(amlObj);
console.log(
    '\n-------------------------------------------------------------\n'
);
console.log(aml_string);
console.log(
    '\n-------------------------------------------------------------\n'
);

// Convert AMLstring(XML) to AMLObject
var data_from_aml = representation.amlToData(aml_string);
printAMLObject(data_from_aml);
console.log(
    '\n-------------------------------------------------------------\n'
);

// Convert AMLObject to Byte(string)
var byte_string = representation.dataToByte(amlObj);
console.log( byte_string);
console.log('Length is : '  +  byte_string.length);
console.log('-------------------------------------------------------------');


// Convert Byte(string) to AMLObject
var data_from_byte = representation.byteToData(byte_string, byte_string.length);
printAMLObject(data_from_byte);

console.log('-------------------------------------------------------------');
