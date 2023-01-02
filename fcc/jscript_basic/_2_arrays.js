/*
    34:%

*/

function testf(){console.log("\nfunction works\n");}
testf();

function printsum(a,b){console.log(a, "+", b, " = ", a+b, "\n");}
printsum(1,2);

function valret(num){return num*2;}
console.log("3 * 2 = ", valret(3), "\n");

// local takes priority over global, scope as usual
let gVar = 9;
console.log("gVar=", gVar);
function gconfict(){let gVar = 2; console.log("gVar=", gVar); return gVar;}
console.log("gVar=", gconfict(), "\n");

// no return defaults to unf
function noret(){gVar++;}
console.log("noret()= ", noret(),"  ,  gVar= ", gVar, "\n");

// strict equaility (no type concersion ===)
function stricteq(num,str)
{
    if (num === str) {console.log(num, "===", str);}
    if (num == str){console.log(num, "==", str);}
    if (num != str) {console.log(num, "!=", str);}
    if (num !== str) {console.log(num, "!==", str);}
    return;
}
stricteq(3, '3');
stricteq(5, 4+1);
stricteq(1, '2');
stricteq(1, 2);
console.log("\n");

// arrays are 0-index, basically the same
// const will not make array immutable
const myarr = [1, 2, 3];
console.log(myarr);
myarr[0] = 9;
console.log(myarr);
console.log("\n");

// arrays are abusive+blaspmeous in js (mix types, different size dimensions, ect)
// most arrays have some capabilities
console.log(myarr);
// push(), append element to end of array
myarr.push(7);
console.log(myarr);
myarr.push([8, 9]);
// pop(), remove last element
console.log(myarr);
myarr.pop();
console.log(myarr);
myarr.pop();
// shift(), remove first element
console.log(myarr);
myarr.shift()
console.log(myarr);
myarr.shift()
console.log(myarr);
// unshift(), add to front
myarr.unshift(2)
console.log(myarr);
myarr.unshift(1);
console.log(myarr);
console.log("\n");

// typeof
console.log("typeof 3  ", typeof 3);
console.log("typeof '3'  ", typeof '3');
console.log("\n");

// swtich stmt
function swdemo(char)
{
    switch(char)
    {
        case 'a' : console.log(char, "--> A"); break;
        case 'b' : console.log(char, "--> B"); break;
        case 'c' : console.log(char, "--> C"); break;
        default : console.log(char, "--> Z"); break;
    };
};
swdemo("a");
swdemo("b");
swdemo("c");
swdemo("d");
console.log("\n");

// objects, don't rely on type casting, use good names
const obj = 
{
    "name": "mike",
    "friends":["kevin", 'karen', 'sam'],
    "networth":-900,
    "salary":20000
};
obj.age = 89; // add by dot
obj['living'] = true; // add by bracket
console.log(obj["name"]);//bracket reference
console.log(obj.salary);//dot reference
console.log(obj["age"]);//bracket
console.log(obj.living);//dot
console.log("\n");


////////~~~~~~~~END>  _2_arrays.js
