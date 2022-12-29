/*
    < 1 > template literal
    < 2 > object literal
    < 3 > funciton in obj
    < 4 > constructor funciton in obj "class"
    < 5 > proper getting and setting
*/
console.clear();
console.log("\n");

// < 1 > template literal
const person = 
{
    name: "Mike Jones",
    age: 30
};
const strlit = `name: ${person.name} age: ${person.age}`; // use back-ticks, not quotes
console.log(strlit);
console.log("\n");

// < 2 > object literal
const getMouseP = (x, y) => ({x, y}); // makes an obj for you
console.log(getMouseP(3,4));
console.log("\n");

// < 3 > funciton in obj
const perp = 
{
    name:"OJ",
    getName: function() {return `perpetrator: ${perp.name}`;} // old way
}
console.log(perp.getName());
const perpp = 
{
    name:"JLO",
    getName() {return `perpetrator: ${this.name}`;} // new way
}
console.log(perpp.getName());
const getter =
{
    val:1,
    getVal() {return this.val;},
    setVal(nVal) {this.val = nVal;},
    printv() {console.log(this.val);}
}
getter.printv();
getter.setVal(4);
getter.printv();
getter.setVal(8);
console.log(getter.getVal());
console.log("\n");

// < 4 > constructor funciton in obj, "class" UpperCammelCase
class Shuttle
{
    constructor(planet) {this.tplanet = planet;} // explicit constructor
    takeoff(){console.log("taking off");}
}
class Rocket
{
    launch(){console.log("rocket launched");}
}
const zeus = new Shuttle("Jupiter");
zeus.takeoff();
const hades = new Rocket();
hades.launch();
console.log("\n");

// < 5 > proper getting and setting
class Book
{
    constructor(author) {this._author = author;}
    get writer(){return this._author;} // getter doesn't let private var get touched
    set writer(updatedAuthor){this._author = updatedAuthor;} // same with setter
}
const novel = new Book('Mark Twain');
console.log(novel.writer);
novel.writer = 'Huck Finn';
console.log(novel.writer);
console.log("\n");


////////~~~~~~~~END>  _5_more_features.js
