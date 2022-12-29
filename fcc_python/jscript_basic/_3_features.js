/*
    be careful with [var]
*/
console.log("\n");

// bad scope, var
function badscope()
{
    var i = 'function scope';
    if (true)
    {
        var i = "block scope"; // updates, gets overriden
        console.log("i in block:  ", i);
    }
    console.log("i in function:  ", i);
}
badscope();

// good scope, let
function goodscope()
{
    let i = 'function scope';
    if (true)
    {
        let i = "block scope"; // updates, gets overriden
        console.log("i in block:  ", i);
    }
    console.log("i in function:  ", i);
}
goodscope();
console.log("\n");

// const is good, like let, but some things are still mutable
// you can't use something declared const to point to something else (error results)
// also can't add new key/values to obj that is const
const arr = [1, 2, 3]
console.log(arr);
arr[0] = 9;
console.log(arr);
obj = {"money":1000, "cars":['pickup', 'mustang', 'suv'], "rate":30};
console.log(obj);
delete obj['money'];
obj['cars'][1] = 'lambo';
console.log(obj);
console.log("\n");

// freeze for safety
const MATH_STUFF = {"_PI":(22/7), "_e":2.71};
Object.freeze(MATH_STUFF);
try
{
    MATH_STUFF._PI = 3.14;
}
catch(ex)
{
    console.log(ex);
}
console.log("PI=", MATH_STUFF._PI);
console.log("\n");

// old-school annonymous function
const old_a_fun = function() {const myVar = "old_annonymous_function"; return myVar;}
console.log(old_a_fun());
console.log("\n");

// ES6 arrow syntax
const es6_fun = () => {const myVar= "es6_function"; return myVar;}
console.log(es6_fun());
console.log("\n");

// inline with argument, like a lambda
const doubler = (num) => num*2;
console.log(doubler(4));
const multiplier = (multc, multp) => multc*multp;
console.log(multiplier(3,5));
console.log("\n");

// default parameters
const greet = (name="Anonymous") => "hi " + name;
console.log(greet()); // takes default
console.log(greet("Karen")); // overides default
console.log("\n");

////////~~~~~~~~END>  _3_features.js
