var assert = require('assert');
var aml = require('../');

var representation = new aml.Representation('sample_data_model.aml');
var deviceId = 'SAMPLE001';
var timeStamp = '123456789';

describe('#getRepresentationId()', function() {
    it('should return representation ID', function() {
        var id = representation.getRepresentationId();
        assert.notEqual(id, '');
    });
});

describe('#getConfigInfo()', function() {
    it('should return AMLObject', function() {
        var amlObj = representation.getConfigInfo();
        assert.notEqual(amlObj, null);
    });
});

describe('#dataToAml()', function() {
    it('should return AML String', function() {
        var amlObj = new aml.AMLObject(deviceId, timeStamp);
        var model = new aml.AMLData();
        model.setValue('a', 'Model_107.113.97.248');
        model.setValue('b', 'SR-P7-970');
        amlObj.addData('Model', model);
        var amlString = representation.dataToAml(amlObj);
        assert.notEqual(amlString, '');
    });
});

describe('#amlToData()', function() {
    it('should return AML Object', function() {
        var amlObj = new aml.AMLObject(deviceId, timeStamp);
        var model = new aml.AMLData();
        model.setValue('a', 'Model_107.113.97.248');
        model.setValue('b', 'SR-P7-970');
        amlObj.addData('Model', model);
        var amlString = representation.dataToAml(amlObj);
        var convertedObj = representation.amlToData(amlString);
        assert.notEqual(convertedObj, null);
    });
});

describe('#dataToByte()', function() {
    it('should return AML String', function() {
        var amlObj = new aml.AMLObject(deviceId, timeStamp);
        var model = new aml.AMLData();
        model.setValue('a', 'Model_107.113.97.248');
        model.setValue('b', 'SR-P7-970');
        amlObj.addData('Model', model);
        var byte_string = representation.dataToByte(amlObj);
        assert.notEqual(byte_string, '');
    });
});

describe('#byteToData()', function() {
    it('should return AML Object', function() {
        var amlObj = new aml.AMLObject(deviceId, timeStamp);
        var model = new aml.AMLData();
        model.setValue('a', 'Model_107.113.97.248');
        model.setValue('b', 'SR-P7-970');
        amlObj.addData('Model', model);
        var byte_string = representation.dataToByte(amlObj);
        var data_from_byte = representation.byteToData(
            byte_string,
            byte_string.length
        );
        assert.notEqual(data_from_byte, null);
    });
});
