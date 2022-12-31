/*
    < 1 >  hypen combination -
    < 2 >  negate chars you don't want ^
    < 3 >  at least once +
    < 4 >  occurs none or many *
    < 5 >  greedy match (default)
    < 6 >  lazy match ?
    < 7 >  html tag
    < 8 >  beginning of string ^ (outside of a set[])
    < 9 >  end of string $
    
    don't try to parse HTML, JSON, XML, etc with regex
    but, pattern matching is ok
*/
let testStr = null;
let testRgx = null; // all letters and numbers
let rresult = null;
console.clear();
console.log("\n");

// < 1 >  hypen combination -
testStr = "I am 9 chars";
testRgx = /[a-z0-9]/ig; // all letters and numbers
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult, "chars: ", rresult.length);
console.log("\n");

// < 2 >  negate chars you don't want ^
testStr = "1234aeiouyMaaaMeeeMiiiM ";
testRgx = /[^0-9^aeiouy]/ig; // will match on whitespace
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult, "  matches: ", rresult.length);
console.log("\n");

// < 3 >  at least once +
testStr = "abc aabc abab";
testRgx = /a+/ig; // must have 'a' at least 1 time to match
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult, "  matches: ", rresult.length);
console.log("\n");

// < 4 >  occurs none or many *
testStr = "The player scored a gooooal and won a gwagon";
testRgx = /goo*/ig;  // 2nd 'o' can occur >=0 times, 'go' must be there to match
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult, "  matches: ", rresult.length);
console.log("\n");

// < 5 >  greedy match (default)
// regex looks for longest match
testStr = "Titanic";
testRgx = /t[a-z]*i/ig;  // start with 't', contains no or some letters, ends with 'i'
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult, "  matches: ", rresult.length);
console.log("\n");

// < 6 >  lazy match ?
// regex looks for shortest match
testStr = "Titanic";
testRgx = /t[a-z]*?i/ig;  // start with 't', contains no or some letters [minimize], ends with 'i'
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult, "  matches: ", rresult.length);
console.log("\n");

// < 7 >  html tag
testStr = "<h1>How to make a submarine</h1>";
testRgx = /<.+?>/;
rresult = testStr.match(testRgx);
console.log(testStr);
console.log(testRgx);
console.log(rresult, "  matches: ", rresult.length);
testRgx = /<\/.+>/;
rresult = testStr.match(testRgx);
console.log(testRgx);
console.log(rresult, "  matches: ", rresult.length);
console.log("\n");

// < 8 >  beginning of string ^ (outside of a set[])
testStr = "Mike can be found";
testRgx = /^Mike/ig;  // out of char set [], ^ only matches beginning of string
console.log(testRgx);
console.log(testStr);
console.log("found 'Mike' ?  :  ", testRgx.test(testStr), "  ", testStr.match(testRgx));
testStr = "probably can't find Mike now";
console.log(testStr);
console.log("found 'Mike' ?  :  ", testRgx.test(testStr), "  ", testStr.match(testRgx));
console.log("\n");

// < 9 >  end of string $
testStr = "all drugs are bad";
testRgx = /bad$/ig;  // query must be at end of string to be found
console.log(testRgx);
console.log(testStr);
console.log("found 'bad' ?  :  ", testRgx.test(testStr), "  ", testStr.match(testRgx));
testStr = "if all drugs are bad, then stop using them";
console.log(testStr);
console.log("found 'bad' ?  :  ", testRgx.test(testStr), "  ", testStr.match(testRgx));
console.log("\n");

////////~~~~~~~~~END>  _8_regex_basic.js
