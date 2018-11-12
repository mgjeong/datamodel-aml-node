var assert = require('assert');
var aml = require('../');

var representation = new aml.Representation('sample_data_model.aml');
var deviceId = 'SAMPLE001';
var timeStamp = '123456789';
var id = 'ID';

describe('#constructAMLData()', function() {
    it('should construct AMLData', function() {
        var amlData = new aml.AMLData();
        assert.notEqual(amlData, null);
    });
});

describe('#set_getValue()', function() {
    it('should set/get string value from amldata', function() {
        var model = new aml.AMLData();
        model.setValue('a', 'Model_107.113.97.248');
        model.setValue('b', 'SR-P7-970');
        assert.equal('SR-P7-970', model.getValueToStr('b'));
    });
});

describe('#set_getStringArrValue()', function() {
    it('should set/get string array value from amldata', function() {
        var appendix = ['52303', '935', '1442'];
        var sample = new aml.AMLData();
        sample.setValue('info', 'info1');
        sample.setValue('appendix', appendix);
        assert.deepEqual(appendix, sample.getValueToStrArr('appendix'));
    });
});

describe('#set_getAMLDataValue()', function() {
    it('should set/get AML Data value from amldata', function() {
        var axis = new aml.AMLData();
        axis.setValue('x', '20');
        var info = new aml.AMLData();
        info.setValue('id', 'f437da3b');
        info.setValue('axis', axis);
        var amlData = info.getValueToAMLData('axis');
        assert.equal('20', amlData.getValueToStr('x'));
    });
});

describe('#getKeys()', function() {
    it('Get all the keys in amldata', function() {
        var model = new aml.AMLData();
        model.setValue('a', 'Model_107.113.97.248');
        model.setValue('id', 'f437da3b');
        assert.equal('a', model.getKeys()[0]);
        assert.equal('id', model.getKeys()[1]);
    });
});

describe('#getValueType()', function() {
    it('getValueType from amldata', function() {
        var model = new aml.AMLData();
        model.setValue('a', 'Model_107.113.97.248');
        assert.equal(aml.AMLValueType.String, model.getValueType('a'));
    });
});
