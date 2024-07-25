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
**Part 2:** Iterate through the grid to find numbers and check if there are any _ around it. Record the location of _ and the number. If the location of _ is already stored, then it means there was already a number associated with it. Multiply the stored number with the current number and add it to the sum. If the location of _ is not stored, then it means this is the first number we found around the _, store the location of _ and the current number.

## Day 4: Scratchcards

**Topics:** 1D Array Algorithm, Sorting <br>
**Difficulty:** 1/10 (part 1 naive solution), 2/10 (part 1 sorted list approach), 2/10 (part 2) <br>
**My solution and thoughts:** <br>
**Part 1:** This part can be simplified into the following problem: Find intersections between two arrays. <br>
Naive approach: For each item in list A, iterate through list B to see if it exists in list B <br>
Runtime: O(m \* n) <br>
Better approach: Sort lists A and B and search through them. <br>
Runtime: Sorting: mlogm + nlogn. Find Intersection: O(m + n). Overall: O(mlogm) (assume m > n) <br>
TODO: Is there a quicker solution? O(n)? <br>
**Part 2:** This part is straightforward. Just store the number of cards in an array as you go and add up at the end. Messed up indexing on the first try so I will rate it as a 2/10.

## Day 5: If You Give A Seed A Fertilizer

**Topics:** Integer Overflow, Range Splitting <br>
**Difficulty:** 4/10 (part 1) 7/10 (part 2) <br>
**Part 1:** At first I implemented maps associated with the given inputs, and then realized the ranges are too large so the map would be incredibly large so not possible. Then, I just went through all the inputs checked if the current number is in the range and calculated the destination without creating maps. Then, I realized the numbers were too large so I switched int to long long. <br>
The question itself is not hard but since I encountered two obstacles while solving it, so I rated this part as 4/10. <br>
TODO: can write functions to calculate the destination for each part to make the code look nicer <br>
**Part 2:** If we naively go through each seed in the range, the solution would run forever. Range splitting took me quite a while to debug so I gave it a 7/10.

## Day 6: Wait For It

**Topics:** String <br>
**Difficulty:** 1/10

## Day 7: Camel Cards

**Topics:** Custom Sorting, Logic <br>
**Difficulty:** 4/10 <br>
There are some edge cases in part 2 that took me a while to debug.

## Day 8: Haunted Wasteland

**Topics:** Very Simple Graph Search (just left and right nodes) <br>
**Difficulty:** 3/10 <br>
For part 2, brute force would result in a slow runtime. Need to do it smarter (calculate lcm).

## Day 9: Mirage Maintenance

**Topics:** Math <br>
**Difficulty:** 2/10 <br>
Find a pattern to do it smarter. <br>
Note that for polynomials of degree $k$, the $k$-th differences will be constant.

## Day 10: Pipe Maze <br>

**Topics:** Graph (DFS, cycle detection, cycle length calculation) <br>
**Difficulty:** 8/10 (Part 1) 10/10 (Part 2) (I'm bad at graph) <br>
For Part 1, use dfs to detect cycle and calculate the length of the cycle. <br>
For Part 2, I tried to mark the boundary points and then use flood fill algorithm to mark all the reachable tiles from boundary as visited. Finally, all the non-visited tiles will be the ones inside the cycle. Not sure why this is not working. <br>
Then, I searched up on reddit and found that you can use shoelace formula to calculate the area of the polygon and then use pick's theorem to calculate the number of integer coordinates lie inside the polygon. The implementation is easy but I've never heard of pick's theorem before so I will give it a 10/10.
