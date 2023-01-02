/*
    < 1 >   shorthand vs longhand, alpha_numeric \w
    < 2 >   shorthand vs longhand, non-alpha_numeric \W
    < 3 >   shorthand vs longhand, digits \d
    < 4 >   shorthand vs longhand, non-digits \D
    < 5 >   shorthand vs longhand, whitespace \s
    < 6 >   shorthand vs longhand, not whitespace \S
    < 7 >   match with ranges {}, repeated char
    < 8 >   match with ranges {}, repeated pattern
    < 9 >   match with ranges {}, lower limit only
    < 10 >  match with ranges {}, exact
*/
let testStr = null;
let testRgx = null; // all letters and numbers
let rresult = null;
console.clear();
console.log("\n");

// < 1 >  shorthand vs longhand, alpha_numeric
testStr = "_8_chars **!!??";
testRgx = /\w/ig; // all alpha_numerics
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult, " alpha-numerics: ", rresult.length);
testRgx = /[A-za-z0-9_]+/ig; // all alpha_numerics
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log(rresult, " alpha-numerics: ", rresult[0].length);
console.log("\n");

// < 2 >  shorthand vs longhand, non-alpha_numeric
testStr = "_8_chars **!!??";
testRgx = /\W/ig; // all whitespace + non-alpha_numeric
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult, " non-alpha_numeric: ", rresult.length);
testRgx = /[^A-za-z0-9_]+/ig; // not alpha_numerics 
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log(rresult, " non-alpha_numeric: ", rresult[0].length);
console.log("\n");

// < 3 >  shorthand vs longhand, digits \d
testStr = "call Jenny @ +1(702) 329-5432";
testRgx = /\d/g; // all digits
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult, " digits: ", rresult.length);
testRgx = /[0-9]/g; // all digits
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log(rresult, " digits: ", rresult.length);
console.log("\n");

// < 4 >  shorthand vs longhand, non-digits \D
testStr = "call Jenny @ +1(702) 329-5432";
testRgx = /\D/g; // all non-digits
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult, " non-digits: ", rresult.length);
testRgx = /[^0-9]/g; // all non-digits
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log(rresult, " non-digits: ", rresult.length);
console.log("\n");

// < 5 >  shorthand vs longhand, whitespace \s
testStr = "\r\t\f\n\v this string";
testRgx = /\s/g; // all whitespace
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log("\\r\\t\\f\\n\\v this string", " whitespace: ", rresult.length);
testRgx = /[\r\t\f\n\v ]/g; // all whitespace
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log("\\r\\t\\f\\n\\v this string", " whitespace: ", rresult.length);
console.log("\n");

// < 6 >  shorthand vs longhand, not whitespace \S
testStr = "\r\t\f\n\v string";
testRgx = /\s/g; // all non-whitespace
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log("\\r\\t\\f\\n\\v string", " non-whitespace: ", rresult.length);
testRgx = /[^\r\t\f\n\v ]/g; // all non-whitespace
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log("\\r\\t\\f\\n\\v string", " non-whitespace: ", rresult.length);
console.log("\n");

// < 7 >  match with ranges {}, repeated char
testStr = "ah aah aaah aaaah aaaaah";
testRgx = /[a]{2,4}h/g; // 'a' [2:4]times + 'h'
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log(testStr);
console.log(rresult);
console.log(`matches:  ${rresult.length}`);
console.log("\n");

// < 8 >  match with ranges {}, repeated pattern
testStr = "bs bes bees beees beeees";
testRgx = /be{1,3}s/g; // 'b' 'e'[2:4]times + 's'
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log(testStr);
console.log(rresult);
console.log(`matches:  ${rresult.length}`);
console.log("\n");

// < 9 >  match with ranges {}, lower limit only
testStr = "hh hah haah haaah haaaah haaaaah";
testRgx = /ha{1,}h/g; // 'h' 'a'[1:oo]times + 'h'
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log(testStr);
console.log(rresult);
console.log(`matches:  ${rresult.length}`);
console.log("\n");

// < 10 >  match with ranges {}, exact
testStr = "hh hah haah haaah haaaah haaaaah";
testRgx = /ha{2}h/g; // 'ha'[2]times + 'h'
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log(testStr);
console.log(rresult);
console.log(`matches:  ${rresult.length}`);
console.log("\n");

////////~~~~~~~~~END>  _9_regex_intmd.js
