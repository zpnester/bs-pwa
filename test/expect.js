 function expectToEqual(a, b) {
    let expect = require("expect");
    expect(a).toEqual(b);
}



function isArray(arr) {
    return arr instanceof Array;
}

module.exports.expectToEqual = expectToEqual;
module.exports.isArray = isArray;