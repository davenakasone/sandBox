/*
    < 1 >  test (literal)
    < 2 >  pipe (OR)
    < 3 >  ignorecase (i-flag)
    < 4 >  match (one)
    < 5 >  match (all, g-flag)
    < 6 >  wild card .
    < 7 >  char set [abc]
    < 8 >  char range [a-f]
*/
console.clear();
console.log("\n");

// < 1 >  test (literal)  ..only returns true or false
// /regex/.test('string')
// quotes not required
let testStr = "the dog is blue";
let testRgx = /the/;
console.log(testStr);
console.log(testRgx);
console.log(testRgx.test(testStr));
console.log("\n");

// < 2 > pipe (OR)
testStr = "Mike has: dogs, cats, and birds";
testRgx = /dogs|monkeys/;
console.log(testStr);
console.log(testRgx);
console.log(testRgx.test(testStr));
testRgx = /cows|monkeys/;
console.log(testStr);
console.log(testRgx);
console.log(testRgx.test(testStr));
console.log("\n");

// < 3 > ignorecase (flag)
testStr = "COdE";
testRgx = /code/i;
console.log(testStr);
console.log(testRgx);
console.log(testRgx.test(testStr));
console.log("\n");

// < 4 >  match one
// 'string'.matche(/regex/)
testStr = "the big dog ate The big bird in tHe morning";
testRgx = /the/i;
console.log(testStr);
console.log(testRgx);
console.log(testStr.match(testRgx));
console.log("\n");

// < 5 >  match all
// finds all matches
// 'string'.matche(/regex/)
testStr = "the big dog ate The big bird in tHe morning";
testRgx = /the/ig; // 2 flags
console.log(testStr);
console.log(testRgx);
console.log(testStr.match(testRgx));
console.log("\n");

// < 6 >  wild card .
testStr = "hug bears, hum songs, huh";
testRgx = /hu./ig; // any char
console.log(testStr);
console.log(testRgx);
console.log(testStr.match(testRgx));
console.log("\n");

// < 7 >  char set [abc]
testStr = "big bug in a bag";
testRgx = /b[iua]g/g; // char set
console.log(testStr);
console.log(testRgx);
console.log(testStr.match(testRgx));
console.log("\n");

// < 8 >  char range [a-f]
testStr = "cat bat mat";
testRgx = /[a-e]at/g; // char range
console.log(testStr);
console.log(testRgx);
console.log(testStr.match(testRgx));
console.log("\n");