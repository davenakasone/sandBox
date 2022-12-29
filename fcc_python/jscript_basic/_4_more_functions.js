/*

*/
console.clear();
console.log("\n");

// variable length parameters "rest parameter"
function kwargs(...args)
{
    return "arguments: " + args.length;
}
console.log(kwargs(0, 1))
console.log(kwargs("str", null, [1,2,3], {"k":3}));
console.log("\n");

// use the rest parameter
const summer = (...argz) => 
{
    let rsum = 0;
    for (const arg of argz)
    {
        rsum += arg;
    }
    return rsum;
}
console.log(summer(1,2,3));
console.log(summer(1,2,3,4));
const isummer = (...argz) => {return argz.reduce((a,b) => a+b, 0); }
console.log(isummer(1,2,3));
console.log("\n");

// more spread operator
var arr = [6, 89, 3, 5];
console.log("Max(", arr, ") = ", Math.max.apply(null, arr)); // no spread
console.log("Max(", arr, ") = ", Math.max(...arr)); // spread
let arrr = [...arr]; // use the spread operator
console.log(arr, "  ==  ", arrr);
console.log("\n");

// destructing assignment, obj
const obj = {"money":400, "temperature":98.6, "lat":36.435, "long":54.532};
console.log(obj);
const {money, temperature} = obj; // deconstruct the object, take only values you want
console.log("{ ", money, " , ", temperature, " }");
const {"lat": latt, "long": longg} = obj; // take key to new variable name
console.log("{ ", latt, " , ", longg, " }");
console.log("\n");

// deconstruct nested obj
const FORECAST =
{
    yesterday: {low: 61, high: 75},
    today: {low: 64, high: 77},
    tomorrow: {low: 68, high: 80}
};
const {tomorrow:{low, high}} = FORECAST;
console.log("tomorrow: { low: ", low, ", high: ", high, " }");
const {today:{low: lowToday}, today:{high: highToday}} = FORECAST; // different var names
console.log("today: { low: ", lowToday, ", high: ", highToday, " }");
console.log("\n");

// deconstruct array
const darr = [1, 2, 3, 4, 5, 6]; 
let [a, b] = darr;  // just take first 2 elements
console.log(darr);
console.log("[a, b] -> ", "[ ", a, ", ", b, " ]");
let [_a, _b] = [b, a];
console.log("[_a, _b] -> ", "[ ", _a, ", ", _b, " ]");
let [aa, bb, , , cc] = darr;
console.log("[a, b, , , c] -> ", "[ ", aa, ", ", bb, ", ", cc, " ]");
console.log("\n");

// destruct assigment and use with rest parameter
const drarr = [1, 2, 3, 4, 5];
const [x, y, ...rarr] = drarr; // deconstruct part
console.log(drarr);
console.log("[ x, y] -> ", "[ ", x, ", ", y, " ]");
console.log(rarr);
console.log("\n");

// destruct and pass obj
const PROFILE = {name:"Mike", age:20, nation:"UK", city:"London"};
console.log(PROFILE);
const update = (prof) => 
{
    const {name, age, nation, city} = prof;
    console.log("{ name:", name, ", age:", age, ", nation:", nation, ", city:", city, " }")
}
update(PROFILE);
const updatee = ({name, age, nation, city}) => 
{
    console.log("{name:", name, ", age:", age, ", nation:", nation, ", city:", city, "}")
}
updatee(PROFILE);
console.log("\n");


////////~~~~~~~~END>  _4_more_functions.js
