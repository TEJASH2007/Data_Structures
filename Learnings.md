<h1>1 : Truth about the prefix sum</h1>
-> if the array contains all the negative or positive elements then the prefix sum always decrease or increase <br>
-> But if the array contains positive and negative both elements then the prefix sum of array may increase or decrease but not 
  monotonic

<h1> To count the number of the subarrays for the range  : </h1>
 ->  [l , r]  is (r - l + 1)   where l is the fixed starting point 
 ->  [l , r]   i belongs to [l , r]    where is the fixed points for every subarray then ( i - l + 1 )*( r - i + 1);
 
