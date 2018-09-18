var assert = require('assert');
var aml = require('../');

var representation = new aml.Representation('sample_data_model.aml');
var deviceId = 'SAMPLE001';
var timeStamp = '123456789';
var id = 'ID';

describe('#constructAMLObject()', function() {
    it('should construct AMLObject', function() {
        var amlObj = new aml.AMLObject(deviceId, timeStamp);
        assert.notEqual(amlObj, null);
    });
});

describe('#constructAMLObjectWithId()', function() {
    it('should construct AMLObject with ID', function() {
        var amlObj = new aml.AMLObject(deviceId, timeStamp, id);
        assert.notEqual(amlObj, null);
    });
});

describe('#add_getData()', function() {
    it('should add/get amlData from amlObject', function() {
        var amlObj = new aml.AMLObject(deviceId, timeStamp, id);
        var model = new aml.AMLData();
        model.setValue('a', 'Model_107.113.97.248');
        model.setValue('b', 'SR-P7-970');
        amlObj.addData('Model', model);
        var amlData = amlObj.getData('Model');
        assert.equal('Model_107.113.97.248', amlData.getValueToStr('a'));
    });
});

describe('#getDataNames()', function() {
    it('should get string list of AMLObjects amlData keys', function() {
        var amlObj = new aml.AMLObject(deviceId, timeStamp, id);
        var model = new aml.AMLData();
        model.setValue('a', 'Model_107.113.97.248');
        model.setValue('b', 'SR-P7-970');
        amlObj.addData('Model', model);
        assert.equal('Model', amlObj.getDataNames()[0]);
    });
});

describe('#getDeviceId()', function() {
    it('should return device ID', function() {
        var amlObj = new aml.AMLObject(deviceId, timeStamp, id);
        assert.equal(deviceId, amlObj.getDeviceId());
    });
});

describe('#getTimeStamp()', function() {
    it('should return timestamp', function() {
        var amlObj = new aml.AMLObject(deviceId, timeStamp, id);
        assert.equal(timeStamp, amlObj.getTimeStamp());
    });
});

describe('#getId()', function() {
    it('should return ID', function() {
        var amlObj = new aml.AMLObject(deviceId, timeStamp, id);
        assert.equal(id, amlObj.getId());
    });
});
