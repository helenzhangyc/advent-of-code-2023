# advent-of-code-2023

## Day 1: Trebuchet?!

**Topics:** String manipulation <br>
**Difficulty:** 1/10

## Day 2: Cube Conundrum

**Topics:** String manipulation, Simple math <br>
**Difficulty:** 1/10

## Day 3: Gear Ratios
**Topics:** 2D Array, Indexing <br>
**Difficulty:** 2/10 <br>
**My solution:** <br>
**Part 1:** Iterate through the grid to find numbers. If found, check around the number to see if there are any symbols. If so, add the number to the sum and return the sum at the end. <br>
**Part 2:** Iterate through the grid to find numbers and check if there are any * around it. Record the location of * and the number. If the location of * is already stored, then it means there was already a number associated with it. Multiply the stored number with the current number and add it to the sum. If the location of * is not stored, then it means this is the first number we found around the *, store the location of * and the current number.

## Day 4: Scratchcards
**Topics:** 1D Array Algorithm, Sorting <br>
**Difficulty:** 1/10 (part 1 naive solution), 2/10 (part 1 sorted list approach), 2/10 (part 2) <br>
**My solution and thoughts:** <br>
**Part 1:** This part can be simplified into the following problem: Find intersections between two arrays. <br>
Naive approach: For each item in list A, iterate through list B to see if it exists in list B <br>
Runtime: O(m * n) <br>
Better approach: Sort lists A and B and search through them. <br>
Runtime: Sorting: mlogm + nlogn. Find Intersection: O(m + n). Overall: O(mlogm) (assume m > n) <br>
TODO: Is there a quicker solution? O(n)? <br>
**Part 2:** This part is straightforward. Just store the number of cards in an array as you go and add up at the end. Messed up indexing on the first try so I will rate it as a 2/10.


