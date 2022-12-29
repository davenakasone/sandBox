/*
    math helpers

    < 1 > basic export
    < 2 > default
*/

// < 1 > basic export
export const add = (x, y) => {return x + y;}
const addd = (x, y) => {return x + y;}
const subb = (x, y) => {return x - y;}
export {addd, subb}; // multiple exports

// < 2 > default, can't do: const, let, var
// it is a fall-back, only 1 can be a default
export default function addnums(x, y) {return x+y;}

////////~~~~~~~~END>  mathf.js