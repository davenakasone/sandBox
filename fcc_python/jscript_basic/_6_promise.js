/*
    js promises

    < 1 > promise
*/
console.clear();
console.log("\n");

// < 1 > promise
// you will do something, it is a constructor
// 3-state: pending, fulfilled, rejected  (need a way to complete)
// use when there is something that takes an unknown amount of time (asynchronous)
/*
    const myP = new Promise((resolve, reject) => {});  // empty-stuck

    const myP = new Promise((resolve, reject) => 
    {
        if (condition){resolve("fullfilled");}
        else {reject("rejected");}
    });
    myP.then(result => {});
*/

const makeServerRequest = new Promise((resolve, reject) =>
{
    let respone = true; // just to stimulate
    if(respone)
    {
        resolve("got data");
    }
    else
    {
        reject("no data");
    }
});

makeServerRequest.then(result => console.log(result)); // for resolved
makeServerRequest.catch(error => console.log(error)); // for rejected

console.log("\n");


////////~~~~~~~~~END>  _6_promise.js
