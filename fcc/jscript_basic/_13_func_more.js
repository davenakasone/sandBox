/*
    arity is number of arguments function needs as input
    currying means reduce arity N to 1
    good for chaining together function calls and simplifying

    < 1 >  split(), use char or regex (no mutations)
    < 2 >  join(), no mutate
    < 3 >  every(), just boolean query
    < 4 >  some(), just boolean query
    < 5 >  curry a function chain
    < 6 >  short-had curry chain
    < 7 >  partial application, null
*/
console.clear();
console.log("\n");

// < 1 >  split(), use char or regex (no mutations)
let g1a = "java is bad, javascript is better";
let g1b = "how9is3the8thug9life?";
let g1_space = g1a.split(" ");
let g1_digit = g1b.split(/\d/);
console.log(`${g1a}  -->  ${g1_space}`);
console.log(`${g1b}  -->  ${g1_digit}`);
console.log("\n");

// < 2 >  join(), no mutate
let g2 = ['c++', 'is', 'a', 'good', 'language'];
let g2s = g2.join(" ");
console.log(`${g2}`);
console.log(`${g2s}`);
console.log("\n");

// < 3 >  every(), just boolean query
let g3a = [9, 98, 97, 6, 5];
let g3b = [1, 2, 3, 4, 5];
console.log(`${g3a}  (x<10) ?  ${g3a.every(x=>x<10)}`);
console.log(`${g3b}  (x<10) ?  ${g3b.every(x=>x<10)}`);
console.log("\n");

// < 4 >  some(), just boolean query
let g4a = [9, 98, 97, 6, 5];
let g4b = [88, 2, 3, 4, 5];
console.log(`${g4a}  (x>90) ?  ${g3a.some(x=>x>90)}`);
console.log(`${g4b}  (x>90) ?  ${g3b.every(x=>x>90)}`);
console.log("\n");

// < 5 >  curry a function chain
function noCurry(x, y) {return x + y;}
function curry(x)
{
    return function(y){return x+y;}
}
let a = 1;
let b = 2;
console.log(`${a} + ${b} = ${curry(a)(b)}`);
console.log(`${a} + ${b} = ${noCurry(a, b)}`);
console.log("\n");

// < 6 >  short-had curry chain
let c = 2;
let d = 3;
const g6curry = x => y => x+y;
console.log(`${c} + ${d} = ${g6curry(c)(d)}`);
console.log("\n");

// < 7 >  partial application, null
function add(a, b, c) {return a + b + c;}  
let add5and10 = add.bind(null, 5, 10);  // Bind the values 5 and 10 to the first and second arguments
console.log("5 + 10 + 3 = ", add5and10(3));
console.log("5 + 10 + 7 = ", add5and10(7));
console.log("\n");

// < 8 >  partial application, this
function makestr(greet, name, slander)
{
    let temp = name.toString();
    console.log(`${greet} ${temp}, ${slander}`);
}
const test = makestr.bind(null, "Hi", this, "you are bad");
test("Jim");
console.log("\n");


////////~~~~~~~~~END>  _13_func_more.js
