# DataModel AML library (nodejs)

datamodel-aml-node is a nodejs binding written over [datamodel-aml-cpp](https://github.sec.samsung.net/RS7-EdgeComputing/datamodel-aml-cpp), that provides the way to present raw data(key/value based) to AutomationML(AML) standard format.
 - Transform raw data to AML data(XML).
 - Serialization / Deserialization AML data using protobuf.

## Prerequisites ##

- nodejs
  - Version : 8.9.4 [[Node js Download link](https://nodejs.org/en/download/)]

- npm
  - Version : 5.6.0

## How to build ##
1. Goto: ~/datamodel-aml-node/
2. Run the script:

   ```
   ./build.sh         : Native build for x86_64 with default flags.
   ./build_32.sh      : Native build for x86 with default flags.
   ./build_common.sh  : Generic build script.
   ```
**Note:** </br>
1. For getting help about script options: **$ ./build_common.sh --help** </br>
2. While building for first time use: **--js_dependencies=true** flag</br>

## How to run ##

### Prerequisites ###
 Built datamodel-aml-node.

 ### sample ###
1. Goto: ~/datamodel-aml-node/samples/
2. Run the sample:
    ```
    node sample.js
    ```

## Running unit test cases ##

### Prerequisites ###
 Built datamodel-aml-node.

### Unit test ###
1. Goto: ~/datamodel-aml-node/unittests
2. Run the test cases:
   ```
   $ ../node_modules/mocha/bin/mocha *js
   ```