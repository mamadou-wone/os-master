const sortArray = (arr) => {
    return arr.sort((a, b) => a - b);
}

const merge = (left, right) => {
    let result = [];
    while (left.length && right.length) {
        if (left[0] < right[0]) {
            result.push(left.shift());
        } else {
            result.push(right.shift());
        }
    }
    return result.concat(left, right);
}

const mergeSort = (arr) => {
    if (arr.length < 2) {
        return arr;
    }
    let mid = Math.floor(arr.length / 2);
    let left = mergeSort(arr.slice(0, mid));
    let right = mergeSort(arr.slice(mid));
    return merge(left, right);
}

const arr = [5, 41, 1, -35, 68, 0]

let s = mergeSort(arr);

// Loop through the array and print each element
for (let i = 0; i < s.length; i++) {
    console.log(s[i]);
}