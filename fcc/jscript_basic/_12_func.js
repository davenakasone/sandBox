/*
    functional programming:
    - isolated functions, no dependency on state
    - pure functions, inputs always give expected results
    - limited side effects (mutations to program state are controlled)
    - should be declarative, not imparative

    in callback, function is argument
    - higher order function accepts a function
    - returning or passed function is a 'lambda'
    - functions assigned something are class functions

    don't try to do something new if there is already a solution
    avoid mutations, don't change things
    be explicit (make the function take args)

    < 1 >  avoid direct changes
    < 2 >  deep copy args
    < 3 >  map(), with 1 arg
    < 4 >  filter(), with 1 arg
    < 5 >  slice(), with 2 arg
*/
console.clear();
console.log("\n");

// < 1 >  avoid direct changes
let g1var = 4;
function g1var_inc()
{
    let temp = g1var+1; // does not effect global
    return temp;
}
console.log(`gvar: ${g1var}  ,  ++: ${g1var_inc()}`);
//better:
function g1var_incc(to_inc)
{
    let temp = to_inc+1; // does not effect global
    return temp;
}
console.log(`gvar: ${g1var}  ,  ++: ${g1var_incc(g1var)}`);
console.log("\n");

// < 2 >  deep copy args
let g2var = [1, 2, 3, 4, 5, 6];
function didx(arr, idx)
{
    let tarr = [...arr]; // deep
    tarr.splice(idx, 1);
    return tarr;
}
console.log(`gvar: ${g2var}  ,  ret arr: ${didx(g2var, 3)}`);
console.log("\n");

// < 3 >  map(), with 1 arg
let g3users = [{name:"Ada", age:70}, {name:"C", age:60}, {name:"Joliet", age:7}];
const g3names = g3users.map(user => user.name); // brings name property without effecting array
console.log(`gvar: ${g3users}\nmap arr: ${g3names}`);
console.log("\n");

// < 4 >  filter(), with 1 arg
const g4names = g3users.filter(user => user.age>20); // brings name property without effecting array, if condition met
console.log(`gvar: ${g3users.length}\nfilter arr: ${g4names.length}`);
console.log("\n");

// < 5 >  slice(), with 2 arg  
// !!! use instead of splice() to prevent mutating
let g5 = g2var.slice(3,5); // non-inclusive
console.log(`gvar: ${g2var}  ,  slice arr: ${g5}`);
console.log("\n");

// < 6 > concat(), does not mutate
let g6a = [9, 8, 7, 6, 5]; // no change
let g6b = [4, 3, 2, 1, 0]; // no change
let g6c = g6a.concat(g6b); // save change
console.log(`const: ${g6a}  ,  const: ${g6b}  ,  changed: ${g6c}`);
console.log("\n");

// < 7 > reduce(), basic method






////////~~~~~~~~~END>  _12_func.js
