/*
    fcc, 0:34%

    datatypes:
        1) undefined
        2) null
        3) boolean
        4) string
        5) symbol
        6) bigint
        7) number
        8) object
*/

for (var i = 0; i < 10; i++)
{
    console.log(i);
};
console.log("\n");

// var lets you overide a variable
var myName = "Mike";
console.log(myName);
var myName = "Ralph";
console.log(myName);
console.log("\n");

// try let instead (it will raise)
let yourName = "Ann";
console.log(yourName);
//let yourName = "Beth"; ERROR
console.log(yourName);
console.log("\n");

// const is like let, make all caps (read-only var)
const BITS_IN_BYTE = 8;
console.log(BITS_IN_BYTE);
//BITS_IN_BYTE = 9; ERROR
console.log(BITS_IN_BYTE);
console.log("\n");

// same increment decrement as C, C++
let ii = 3;
console.log(ii);
ii++;
console.log(ii);
ii--;
console.log(ii);
console.log("\n");

// compund assigment is the same
ii = 9;
console.log(ii);
ii += 3;
console.log(ii);
ii -= 8;
console.log(ii);
console.log("\n");

// single == double as long as you start and stop with the same
// escaping is as usual
var my_str = "escapces work like \"C\"";
console.log(my_str);
console.log("\n");

// strings can be manipulated with operators
// but once assigned, they are immutable (can reassign though)
my_str = "start" + " end"
console.log(my_str);
my_str += " +";
console.log(my_str);
console.log("\n");

// strings have a length propery
let anystr = "red";
console.log("str:", anystr,"  length:", anystr.length);
for (i = 0; i < anystr.length; i++) // failure
{
    console.log(toString(anystr.charAt(ii)));
    console.log(anystr[ii]);
};
for (let val of anystr) // for of, using itterable
{
    console.log(val);
};
//same thing
//let astr = [...anystr].reduce(function(val){console.log(val)}); // spread operator + reduce()
//let astr = Array.from(anystr); // longer way
let ast = [...anystr];
for (var x = 0; x < ast.length; x++)
{
    console.log(ast[x]);
};
console.log("\n");


console.log("\n");

////////~~~~~~~~END>  _1_intro.js
