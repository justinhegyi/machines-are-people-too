# machines-are-people-too
machine learning capstone: random decision forests
these trees are actually doubly random - they select a random subset of the data with replacement, and also select a random subset of the attributes to build the tree out of. This is because I noticed that I was basically getting basically the exact same tree as my ID3 over and over if my dataset was large enough.

TO RUN:
run the code from jmh361.cpp. To test other data sets for now you just have to type them in. I kept some records of the testing in Records.txt to compare the performance of my ID3 implementation and my forest. I didn't compare it to the other classifiers that I wrote for this class because my ID3 was the best of the bunch, but I'd like to in the future. 

Goals for the future:
-Maintain the Makefile 
-compare to other classifiers
