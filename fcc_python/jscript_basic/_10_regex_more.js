/*
    < 1 >  all or none ?
    < 2 >  positive and negative look ahead (?=...) (?!...)
    < 3 >  lookahead on password
    < 4 >  group with OR |
    < 5 >  repeated words
    < 6 >  repeated numbers
    < 7 >  replace with regex
    < 8 >  replace switching with regex
    < 9 > regex trimming
    < 10 > js trimming
*/
let testStr = null;
let testRgx = null; // all letters and numbers
let rresult = null;
console.clear();
console.log("\n");

// < 1 >  all or none ?, effective {0, 1}
testStr = "color colour";
testRgx = /colou?r/g; // if the 'u' is present or not, just count it
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult);
console.log(`matches:  ${rresult.length}`);
testRgx = /colou{0,1}r/g; // if the 'u' is present or not, just count it
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log(rresult);
console.log(`matches:  ${rresult.length}`);
console.log("\n");

// < 2 >  positive and negative look ahead (?=...) (?!...)
testStr = "bad bay bat barn bacon cat ba^ ba*";
testRgx = /ba(?=\w{1} )/g; // 'ba' is present AND [1] alpha_numeric characters follow + space
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult);
console.log(`matches:  ${rresult.length}`);
testRgx = /ba(?!\w )/g; // 'ba' is present AND [1:2] non-alpha_numeric characters follow + space
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log(rresult);
console.log(`matches:  ${rresult.length}`);
console.log("\n");

// < 3 >  lookahead on password
testStr = "password69";
testRgx = /p(?=\w{3,6})(?=\D*\d)/g; // password is at least 4 chars + contains a number
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult);
console.log(`matches:  ${rresult.length}`);
console.log("\n");

// < 4 >  group with OR |
testStr = "penguin pumpkin";
testRgx = /p(engu|umpk)in/g; // enforce begin and end, middile is either or
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult);
console.log(`matches:  ${rresult.length}`);
console.log("\n");

// < 5 >  repeated words
// capture index starts at 1
testStr = "row row row ur b, row row your b, row your b";
testRgx = /(\w+) \1 \1/; // words that are repeated 3 times and seperated by white space
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult);
console.log(`matches:  ${rresult.length}`);
console.log("\n");

// < 6 >  repeated numbers
// capture index starts at 1
testStr = "43 43 43";
testRgx = /^(\d+) \1 \1$/; // numbers that are repeated 3 times and seperated by white space [start, stop] enforced
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult);
console.log(`matches:  ${rresult.length}  ...1 is for the capture group, other for query`);
console.log("\n");

// < 7 >  replace with regex
testStr = "silver is the most valuable metal, silver is very valuable";
testRgx = /silver/ig; // get what you want to correct
rresult = testStr.replace(testRgx, "Rhodium");
console.log(testStr);
console.log(testRgx);
console.log(rresult);
console.log("\n");

// < 8 >  replace switching with regex
testStr = "javascript is bad";
testRgx = /^(\w+)\s(\w+)\s(\w+)$/; // parse to scramble
rresult = testStr.replace(testRgx, '$3 $1 $2');
console.log(testStr);
console.log(testRgx);
console.log(rresult);
console.log("\n");

// < 9 > regex trimming
testStr = "  ...trim me! ..\t";
testRgx = /^\s+|\s$/g; // find the beginning and ending white spaces
rresult = testStr.replace(testRgx, ""); // replace them with null
console.log(testStr);
console.log(testRgx);
console.log(rresult);
console.log("\n");

// < 10 > js trimming
testStr = "  ...trim me! ..\t";
rresult = testStr.trim()
console.log(testStr);
console.log(rresult);
console.log("\n");


////////~~~~~~~~~END>  _10_regex_more.js
