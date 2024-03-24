let s = "abcd";
let list = [1, 2, 3, 4, 5, 6, 7];
let t = {
    1:function(n:boolean, i:number = 10) {
        console.log("11111");
        if(n) {
            console.log("true" + i);
            return 1;
        } else {
            console.log("false" + i);
            return "a";
        }
    },
}
console.log(s);
console.log({
    1:1,
    2:2,
    3:3,
});
t[1](false);

function sum(...nums:number[]):number {
    let ret:number = 0;
    for(let i of nums) {
        ret += i;
    }
    return ret
}
console.log(sum(1,2,3,4,5,6,7,8))
