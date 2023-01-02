/*
    < 1 >  typeof
    < 2 >  prototypes for inheritance
    < 3 >  mixins are composition
    < 4 >  private scoped in constructor
    < 5 >  IIFE, immediatley invoked function expression
*/
console.clear();
console.log("\n");

// < 1 >  typeof
// js primitives (core) : Number, String, Boolean, Null, Undefined
// ES2020 : Symbol, BigInt
// + immutable 'Object'
console.log(typeof true);
console.log(typeof 1);
console.log(typeof "str");
console.log(typeof []); // arrays are treated as objects
console.log(typeof {});
console.log("\n");

// < 2 > prototypes for inheritance
function Animal(){}
Animal.prototype =
{
    constructor: Animal,
    eat: function(){console.log("eating");}
}
function Bird(){}
Bird.prototype = Object.create(Animal.prototype);  // Bird gets derived from Animal
let duck = new Bird("Daffy"); // instance of a duck, from Bird, includes Animal
duck.eat()
// overide with same name in child object
Bird.prototype.eat = function () {console.log("pecking");}
duck.eat()
console.log("\n");

// < 3 >  mixins are composition
let flyer = function(obj)
{
    obj.fly = function(){console.log("flying");}
}
let bird = 
{
    name:"Daffy",
    numLegs:2
}
let plane =
{
    model:"777",
    passangers:500
}
flyer(bird); bird.fly();
flyer(plane); plane.fly();
console.log("\n");

// < 4 >  private scoped in constructor
function Bank()
{
    let pword = "password";//private
    this.balance = 999999;//public
    this.get_pword = function(){return pword;} // priveldged accessor
} 
let patty = new Bank();
console.log(patty.balance);
console.log(patty.get_pword());
console.log("\n");

// < 5 >  IIFE, immediatley invoked function expression
(function(){console.log("iife");})() // annonymous, executes immidiately
console.log("\n");

////////~~~~~~~~~END>  _11_da_intro.js
